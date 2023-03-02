/* libFLAC - Free Lossless Audio Codec library
 * Copyright (C) 2000-2009  Josh Coalson
 * Copyright (C) 2011-2022  Xiph.Org Foundation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the Xiph.org Foundation nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "private/cpu.h"

#ifndef FLAC__NO_ASM
#if (defined FLAC__CPU_IA32 || defined FLAC__CPU_X86_64) && FLAC__HAS_X86INTRIN
#include "private/stream_encoder.h"
#include "private/macros.h"
#include "private/bitmath.h"
#ifdef FLAC__AVX2_SUPPORTED

#include <stdlib.h>    /* for abs() */
#include <string.h>    /* for memcpy() */
#include <immintrin.h> /* AVX2 */
#include "FLAC/assert.h"

FLAC__SSE_TARGET("avx2")
void FLAC__precompute_partition_info_sums_intrin_avx2(const FLAC__int32 residual[], FLAC__uint64 abs_residual_partition_sums[], uint32_t residual_samples, uint32_t predictor_order, uint32_t min_partition_order, uint32_t 
		max_partition_order, uint32_t bps)
{
	const uint32_t default_partition_samples = (residual_samples + predictor_order) >> max_partition_order;
	uint32_t partitions = 1u << max_partition_order;

	FLAC__ASSERT(default_partition_samples > predictor_order);

	/* first do max_partition_order */
	{
		const uint32_t threshold = 32 - FLAC__bitmath_ilog2(default_partition_samples);
		uint32_t partition, residual_sample, end = (uint32_t)(-(int32_t)predictor_order);

		if(bps + FLAC__MAX_EXTRA_RESIDUAL_BPS < threshold) {
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m128i sum128;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-7; residual_sample+=8) {
					__m256i res256 = _mm256_abs_epi32(_mm256_loadu_si256((const __m256i*)(const void*)(residual+residual_sample)));
					sum256 = _mm256_add_epi32(sum256, res256);
				}

				sum128 = _mm_add_epi32(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i res128 = _mm_abs_epi32(_mm_loadu_si128((const __m128i*)(const void*)(residual+residual_sample)));
					sum128 = _mm_add_epi32(sum128, res128);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i res128 = _mm_abs_epi32(_mm_cvtsi32_si128(residual[residual_sample]));
					sum128 = _mm_add_epi32(sum128, res128);
				}

				sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(1,0,3,2)));
				sum128 = _mm_add_epi32(sum128, _mm_shufflelo_epi16(sum128, _MM_SHUFFLE(1,0,3,2)));
				abs_residual_partition_sums[partition] = (FLAC__uint32)_mm_cvtsi128_si32(sum128);
/* workaround for MSVC bugs (at least versions 2015 and 2017 are affected) */
#if (defined _MSC_VER) && (defined FLAC__CPU_X86_64)
				abs_residual_partition_sums[partition] &= 0xFFFFFFFF; /**/
#endif
			}
		}
		else { /* have to pessimistically use 64 bits for accumulator */
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m128i sum128;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i res128 = _mm_abs_epi32(_mm_loadu_si128((const __m128i*)(const void*)(residual+residual_sample)));
					__m256i res256 = _mm256_cvtepu32_epi64(res128);
					sum256 = _mm256_add_epi64(sum256, res256);
				}

				sum128 = _mm_add_epi64(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-1; residual_sample+=2) {
					__m128i res128 = _mm_abs_epi32(_mm_loadl_epi64((const __m128i*)(const void*)(residual+residual_sample)));
					res128 = _mm_cvtepu32_epi64(res128);
					sum128 = _mm_add_epi64(sum128, res128);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i res128 = _mm_abs_epi32(_mm_cvtsi32_si128(residual[residual_sample]));
					sum128 = _mm_add_epi64(sum128, res128);
				}

				sum128 = _mm_add_epi64(sum128, _mm_srli_si128(sum128, 8));
				_mm_storel_epi64((__m128i*)(void*)(abs_residual_partition_sums+partition), sum128);
			}
		}
	}

	/* now merge partitions for lower orders */
	{
		uint32_t from_partition = 0, to_partition = partitions;
		int partition_order;
		for(partition_order = (int)max_partition_order - 1; partition_order >= (int)min_partition_order; partition_order--) {
			uint32_t i;
			partitions >>= 1;
			for(i = 0; i < partitions; i++) {
				abs_residual_partition_sums[to_partition++] =
					abs_residual_partition_sums[from_partition  ] +
					abs_residual_partition_sums[from_partition+1];
				from_partition += 2;
			}
		}
	}
	_mm256_zeroupper();
}

FLAC__SSE_TARGET("avx2")
void FLAC__precompute_partition_info_sums_and_escapes_intrin_avx2(const FLAC__int32 residual[], FLAC__uint64 abs_residual_partition_sums[],
		uint32_t raw_bits_per_partition[], uint32_t residual_samples, uint32_t predictor_order, uint32_t min_partition_order, uint32_t max_partition_order, uint32_t bps)
{
	const uint32_t default_partition_samples = (residual_samples + predictor_order) >> max_partition_order;
	uint32_t partitions = 1u << max_partition_order;

	FLAC__ASSERT(default_partition_samples > predictor_order);

	/* first do max_partition_order */
	{
		const uint32_t threshold = 32 - FLAC__bitmath_ilog2(default_partition_samples);
		uint32_t partition, residual_sample, end = (uint32_t)(-(int32_t)predictor_order);

		if(bps + FLAC__MAX_EXTRA_RESIDUAL_BPS < threshold) {
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m256i rmax256 = _mm256_setzero_si256();
				__m128i sum128, rmax128;
				FLAC__uint32 rmax;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-7; residual_sample+=8) {
					__m256i load = _mm256_loadu_si256((const __m256i*)(const void*)(residual+residual_sample));
					__m256i res256 = _mm256_abs_epi32(load);
					__m256i mask = _mm256_srai_epi32(load,31);
					sum256 = _mm256_add_epi32(sum256, res256);
					rmax256 = _mm256_or_si256(rmax256,_mm256_xor_si256(load,mask));
				}

				sum128  = _mm_add_epi32(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));
				rmax128 = _mm_or_si128(_mm256_extracti128_si256(rmax256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i load = _mm_loadu_si128((const __m128i*)(const void*)(residual+residual_sample));
					__m128i res128 = _mm_abs_epi32(load);
					__m128i mask = _mm_srai_epi32(load,31);
					sum128 = _mm_add_epi32(sum128, res128);
					rmax128 = _mm_or_si128(rmax128,_mm_xor_si128(load,mask));
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i load =_mm_cvtsi32_si128(residual[residual_sample]);
					__m128i res128 = _mm_abs_epi32(load);
					__m128i mask = _mm_srai_epi32(load,31);
					sum128 = _mm_add_epi32(sum128, res128);
					rmax128 = _mm_or_si128(rmax128,_mm_xor_si128(load,mask));
				}

				sum128 = _mm_add_epi32(sum128, _mm_shuffle_epi32(sum128, _MM_SHUFFLE(1,0,3,2)));
				sum128 = _mm_add_epi32(sum128, _mm_shufflelo_epi16(sum128, _MM_SHUFFLE(1,0,3,2)));
				rmax128 = _mm_or_si128(rmax128, _mm_shuffle_epi32(rmax128, _MM_SHUFFLE(1,0,3,2)));
				rmax128 = _mm_or_si128(rmax128, _mm_shufflelo_epi16(rmax128, _MM_SHUFFLE(1,0,3,2)));
				abs_residual_partition_sums[partition] = (FLAC__uint32)_mm_cvtsi128_si32(sum128);
				rmax = (FLAC__uint32)_mm_cvtsi128_si32(rmax128);

				/* now we know all residual values are in the range [-rmax-1,rmax] */
				raw_bits_per_partition[partition] = rmax? FLAC__bitmath_ilog2(rmax) + 2 : 1;

/* workaround for MSVC bugs (at least versions 2015 and 2017 are affected) */
#if (defined _MSC_VER) && (defined FLAC__CPU_X86_64)
				abs_residual_partition_sums[partition] &= 0xFFFFFFFF; /**/
				raw_bits_per_partition[partition] &= 0xFFFFFFFF; /**/
#endif
			}
		}
		else { /* have to pessimistically use 64 bits for accumulator */
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m128i sum128, rmax128 = _mm_setzero_si128();
				FLAC__uint32 rmax;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i load =_mm_loadu_si128((const __m128i*)(const void*)(residual+residual_sample));
					__m128i res128 = _mm_abs_epi32(load);
					__m256i res256 = _mm256_cvtepu32_epi64(res128);
					__m128i mask = _mm_srai_epi32(load,31);
					sum256 = _mm256_add_epi64(sum256, res256);
					rmax128 = _mm_or_si128(rmax128,_mm_xor_si128(load,mask));
				}

				sum128 = _mm_add_epi64(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-1; residual_sample+=2) {
					__m128i load =_mm_loadl_epi64((const __m128i*)(const void*)(residual+residual_sample));
					__m128i res128 = _mm_abs_epi32(load);
					__m128i mask = _mm_srai_epi32(load,31);
					res128 = _mm_cvtepu32_epi64(res128);
					sum128 = _mm_add_epi64(sum128, res128);
					rmax128 = _mm_or_si128(rmax128,_mm_xor_si128(load,mask));
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i load =_mm_cvtsi32_si128(residual[residual_sample]);
					__m128i res128 = _mm_abs_epi32(load);
					__m128i mask = _mm_srai_epi32(load,31);
					sum128 = _mm_add_epi64(sum128, res128);
					rmax128 = _mm_or_si128(rmax128,_mm_xor_si128(load,mask));
				}

				sum128 = _mm_add_epi64(sum128, _mm_srli_si128(sum128, 8));
				_mm_storel_epi64((__m128i*)(void*)(abs_residual_partition_sums+partition), sum128);

				rmax128 = _mm_or_si128(rmax128, _mm_shuffle_epi32(rmax128, _MM_SHUFFLE(1,0,3,2)));
				rmax128 = _mm_or_si128(rmax128, _mm_shufflelo_epi16(rmax128, _MM_SHUFFLE(1,0,3,2)));
				rmax = (FLAC__uint32)_mm_cvtsi128_si32(rmax128);

				/* now we know all residual values are in the range [-rmax-1,rmax] */
				raw_bits_per_partition[partition] = rmax? FLAC__bitmath_ilog2(rmax) + 2 : 1;
			}
		}
	}

	/* now merge partitions for lower orders */
	{
		uint32_t from_partition = 0, to_partition = partitions;
		int partition_order;
		for(partition_order = (int)max_partition_order - 1; partition_order >= (int)min_partition_order; partition_order--) {
			uint32_t i;
			partitions >>= 1;
			for(i = 0; i < partitions; i++) {
				abs_residual_partition_sums[to_partition] =
					abs_residual_partition_sums[from_partition  ] +
					abs_residual_partition_sums[from_partition+1];
				raw_bits_per_partition[to_partition++] = flac_max(
					raw_bits_per_partition[from_partition],
					raw_bits_per_partition[from_partition+1]);
				from_partition += 2;
			}
		}
	}
	_mm256_zeroupper();
}


#if 0
	int partition_order;
	uint32_t from_partition, to_partition = 0;
	const uint32_t blocksize = residual_samples + predictor_order;

	/* first do max_partition_order */
	{
		FLAC__int32 end = -(FLAC__int32)(predictor_order);
		FLAC__uint32 rmax;
		uint32_t partition, residual_sample;
		const uint32_t partitions = 1u << max_partition_order;
		const uint32_t default_partition_samples = blocksize >> max_partition_order;
		partition_order = (int)max_partition_order;


		FLAC__ASSERT(default_partition_samples > predictor_order);

		for(partition = residual_sample = 0; partition < partitions; partition++) {
			__m256i rmax_vector = _mm256_setzero_si256();
			FLAC__int32 remainder[8] = {0};
			FLAC__int32 rmax_array[8];
			end += default_partition_samples;

			for( ; (int)residual_sample < (int)end-7; residual_sample+=8) {
				__m256i load = _mm256_loadu_si256((const __m256i*)(const void*)(residual+residual_sample));
				__m256i mask = _mm256_srai_epi32(load,31);
				rmax_vector = _mm256_or_si256(rmax_vector,_mm256_xor_si256(load,mask));
			}

			memcpy(&remainder, residual+residual_sample, end-residual_sample);

			{
				__m256i load = _mm256_loadu_si256((const __m256i*)(const void*)(&remainder));
				__m256i mask = _mm256_srai_epi32(load,31);
				rmax_vector = _mm256_or_si256(rmax_vector,_mm256_xor_si256(load,mask));
			}

			_mm256_storeu_si256((__m256i*)(void*)(rmax_array),rmax_vector);
			rmax = rmax_array[0] | rmax_array[1] | rmax_array[2] | rmax_array[3] | rmax_array[4] | rmax_array[5] | rmax_array[6] | rmax_array[7];

			/* now we know all residual values are in the range [-rmax-1,rmax] */
			raw_bits_per_partition[partition] = rmax? FLAC__bitmath_ilog2(rmax) + 2 : 1;
		}
		to_partition = partitions;
	}

	/* now merge partitions for lower orders */
	for(from_partition = 0, --partition_order; partition_order >= (int)min_partition_order; partition_order--) {
		uint32_t m;
		uint32_t i;
		const uint32_t partitions = 1u << partition_order;
		for(i = 0; i < partitions; i++) {
			m = raw_bits_per_partition[from_partition];
			from_partition++;
			raw_bits_per_partition[to_partition] = flac_max(m, raw_bits_per_partition[from_partition]);
			from_partition++;
			to_partition++;
		}
	}
}
#endif /* 0 */

#endif /* FLAC__AVX2_SUPPORTED */
#endif /* (FLAC__CPU_IA32 || FLAC__CPU_X86_64) && FLAC__HAS_X86INTRIN */
#endif /* FLAC__NO_ASM */
