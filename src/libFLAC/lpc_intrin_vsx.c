/* libFLAC - Free Lossless Audio Codec library
 * Copyright (C) 2000-2009  Josh Coalson
 * Copyright (C) 2011-2016  Xiph.Org Foundation
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

#ifndef FLAC__INTEGER_ONLY_LIBRARY
#ifndef FLAC__NO_ASM
#if defined(FLAC__CPU_PPC64) && defined(FLAC__USE_VSX)

#include "private/cpu.h"
#include "private/lpc.h"
#include "FLAC/assert.h"
#include "FLAC/format.h"

#include <altivec.h>

#ifdef FLAC__HAS_TARGET_POWER8
__attribute__((target("cpu=power8")))
void FLAC__lpc_compute_autocorrelation_intrin_power8_vsx_lag_16(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 16); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
		autoc[8] += data[i] * data[i+8];
		autoc[9] += data[i] * data[i+9];
		autoc[10] += data[i] * data[i+10];
		autoc[11] += data[i] * data[i+11];
		autoc[12] += data[i] * data[i+12];
		autoc[13] += data[i] * data[i+13];
		autoc[14] += data[i] * data[i+14];
		autoc[15] += data[i] * data[i+15];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power8")))
void FLAC__lpc_compute_autocorrelation_intrin_power8_vsx_lag_12(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 12); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
		autoc[8] += data[i] * data[i+8];
		autoc[9] += data[i] * data[i+9];
		autoc[10] += data[i] * data[i+10];
		autoc[11] += data[i] * data[i+11];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power8")))
void FLAC__lpc_compute_autocorrelation_intrin_power8_vsx_lag_8(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 8); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power8")))
void FLAC__lpc_compute_autocorrelation_intrin_power8_vsx_lag_4(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 4); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}
#endif /* FLAC__HAS_TARGET_POWER8 */

#ifdef FLAC__HAS_TARGET_POWER9
__attribute__((target("cpu=power9")))
void FLAC__lpc_compute_autocorrelation_intrin_power9_vsx_lag_16(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 16); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
		autoc[8] += data[i] * data[i+8];
		autoc[9] += data[i] * data[i+9];
		autoc[10] += data[i] * data[i+10];
		autoc[11] += data[i] * data[i+11];
		autoc[12] += data[i] * data[i+12];
		autoc[13] += data[i] * data[i+13];
		autoc[14] += data[i] * data[i+14];
		autoc[15] += data[i] * data[i+15];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power9")))
void FLAC__lpc_compute_autocorrelation_intrin_power9_vsx_lag_12(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 12); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
		autoc[8] += data[i] * data[i+8];
		autoc[9] += data[i] * data[i+9];
		autoc[10] += data[i] * data[i+10];
		autoc[11] += data[i] * data[i+11];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power9")))
void FLAC__lpc_compute_autocorrelation_intrin_power9_vsx_lag_8(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 8); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
		autoc[4] += data[i] * data[i+4];
		autoc[5] += data[i] * data[i+5];
		autoc[6] += data[i] * data[i+6];
		autoc[7] += data[i] * data[i+7];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}

__attribute__((target("cpu=power9")))
void FLAC__lpc_compute_autocorrelation_intrin_power9_vsx_lag_4(const FLAC__real data[], uint32_t data_len, uint32_t lag, double autoc[])
{
	long i;

	(void)lag;

	for (i = 0; i < (long)(data_len - 4); i++) {
		autoc[0] += data[i] * data[i];
		autoc[1] += data[i] * data[i+1];
		autoc[2] += data[i] * data[i+2];
		autoc[3] += data[i] * data[i+3];
	}
	for (; i < (long)data_len; i++) {
		uint32_t coeff;

		FLAC__real d = data[i];
		for (coeff = 0; coeff < data_len - i; coeff++)
			autoc[coeff] += d * data[i+coeff];
	}
}
#endif /* FLAC__HAS_TARGET_POWER9 */

#endif /* FLAC__CPU_PPC64 && FLAC__USE_VSX */
#endif /* FLAC__NO_ASM */
#endif /* FLAC__INTEGER_ONLY_LIBRARY */
