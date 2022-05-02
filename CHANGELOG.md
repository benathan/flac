# Changelog

## FLAC 1.3.4 (20-Feb-2022)

This release mostly fixes (security related) bugs. When building with MSVC, using CMake is preferred, see the README under "Building with CMake" for more information. Building with MSVC using solution files is deprecated and these files will be removed in the future.

* General:
	* Fix 12 decoder bugs found by oss-fuzz, including CVE-2020-0499 (erikd, Martijn van Beurden)
	* Fix encoder bug CVE-2021-0561 (NeelkamalSemwal)
	* Integrate oss-fuzzers (erikd, Guido Vranken)
	* Seeking fixes (NeelkamalSemwal, Robert Kausch)
	* Various fixes and improvements (Andrei Astafev, Rosen Penev, Håkan Kvist, oreo639, erikd, Tamás Zahola, Ulrik Mikaelsson, Tyler Dunn, tmkk)
* FLAC format:
	* (none)
* Ogg FLAC format:
	* (none)
* flac:
	* Various fixes and improvements (Andrei Astafev, Martijn van Beurden)
* metaflac:
	* (none)
* build system:
	* CMake improvements (evpobr, Vitaliy Kirsanov, erikd, Ozkan Sezer, Tyler Dunn, tg-m DeadSix27, ericLemanissier, Chocobo1).
	* Fixes for MinGW and MSVC (Ozkan Sezer).
	* Fix for clang (Ozkan Sezer)
	* Fix for PowerPC (Peter Seiderer, Thomas BERNARD)
	* Fix for FreeBSD PowerPC (pkubaj).
* testing/validation:
	* Add Windows target to CI, improve logging (Ralph Giles)
	* CI improvements (Ralph Giles, Ewout ter Hoeven)
* documentation:
	* Doxygen fixes (Tyler Dunn)
	* Fix typos (Tim Gates, maxz)
* interface changes:
	* libFLAC:
		* (none)
	* libFLAC++:
		* (none)

## FLAC 1.3.3 (4-Augs-2019)
* General:
	* Fix CPU detection (Janne Hyvärinen).
	* Switch from unsigned types to uint32_t (erikd).
	* CppCheck fixes (erikd).
	* Improve SIMD decoding of 24 bit files (lvqcl).
	* POWER* amnd POWER9 improvements (Anton Blanchard).
	* More tests.
* FLAC format:
	* (none)
* Ogg FLAC format:
	* (none)
* flac:
	* When converting to WAV, use WAVEFORMATEXTENSIBLE when bits per second is not 8 or 16 (erikd).
	* Fix --output-prefix with input-files in sub-directories (orbea).
* metaflac:
	* (none)
* plugins:
	* (none)
* build system:
	* Cmake support (Vitaliy Kirsanov, evpobr).
	* Visual Studio updates (Janne Hyvärinen).
	* Fix for MSVC when UNICODE is enabled (lvqcl).
	* Fix for OpenBSD/i386 (Christian Weisgerber).
* documentation:
	* (none)
* libraries
	* (none)
* interface changes:
	* libFLAC:
		* (none)
	* libFLAC++:
		* (none)

## FLAC 1.3.2 (01-Jan-2017)

* General:
	* Fix undefined behaviour using GCC/Clang UBSAN (erikd).
	* General hardening via fuzz testing with AFL (erikd and others).
	* General code improvements (lvqcl, erikd and others).
	* Add FLAC in MP4 specification docs (Ralph Giles).
	* MSVS build cleanups (lvqcl).
	* Fix some cppcheck warnings (erikd).
	* Assume all currently used OSes support SSE2.
* FLAC format:
	* (none)
* Ogg FLAC format:
	* (none)
* flac:
	* Fix potential infinite loop on flac-to-flac conversion (erikd).
	* Add  WAVEFORMATEXTENSIBLE to WAV (as needed) when decoding (lvqcl).
	* Only write vorbis-comments if they are non-empty.
	* Error out if decoding RAW with bits != (8|16|24).
* metaflac:
	* Add --scan-replay-gain option.
* plugins:
	* (none)
* build system:
	* Fixes for MSVC and Makefile.lite build systems.
* documentation:
	* (none)
* libraries:
	* CPU detection cleanup and fixes (Julian Calaby, erikd and lvqcl).
	* Fix two stream decoder bugs (Max Kellermann).
	* Fix a NULL dereference bug (on a malformed file).
	* Changed the LPC order guess for a slight compression improvement, particularly for classical music (Martijn van Beurden).
	* Improved encoding speed on older Intel CPUs.
	* Fixed a seeking bug when decoding certain files (Miroslav Lichvar).
	* Put an upper bound (32768) on the number of seek points.
	* Fix potential memory leaks.
	* Support 64bit brword/bwword allowing FLAC__BYTES_PER_WORD to be set to 8 (disabled by default).
	* Fix an out-of-bounds heap read.
	* Win32: Only use large buffers when writing to disk.
* interface changes:
	* libFLAC:
		* (none)
	* libFLAC++:
		* (none)


## FLAC 1.3.1 (25-Nov-2014)

* General:
	* Improved decoding efficiency of all bit depths but especially so for 24 bits for IA32 architecture (lvqcl and Miroslav Lichvar).
	* Faster encoding using SSE and AVX (lvqcl).
	* Fixed bartlett, bartlett_hann and triangle functions.
	* New apodization functions partial_tukey and punchout_tukey for improved compression (Martijn van Beurden).
	* Retuned compression presets to incorporate new apodization functions (Martijn van Beurden).
	* Fix -Wcast-align warnings on armhf architecture (Erik de Castro Lopo).
* FLAC format:
	* (none)
* Ogg FLAC format:
	* (none)
* flac:
	* Help output documentation improvements.
	* I/O buffering improvements on Windows to reduce disk fragmentation when writing files.
	* Only write vorbis-comments if they are non-empty.
* metaflac:
	* (none)
* plugins:
	* Fix symbol visibility in XMMS plugin.
* build system:
	* Many fixes and improvements across all the build systems.
* documentation:
	* Document new apodization windows.
* libraries:
	* Fix CVE-2014-9028 (heap write overflow) and CVE-2014-8962 (heap read overflow) (Erik de Castro Lopo).
* interface changes:
	* libFLAC:
		* (none)
	* libFLAC++:
		* (none)


## FLAC 1.3.0 (26-May-2013)

* General:
	* Move development to Xiph.org git repository.
	* The `--sector-align` option of `flac` has been deprecated and may not exist in future versions. `shntool` provides similar functionality.
	* Support for the RF64 and Wave64 formats in `flac` (see below).
	* Better handling of cuesheets with non-CD-DA sample rates.
	* The `--ignore-chunk-sizes` option has been added to the `flac` command line tool.
* FLAC format:
	* (none)
* Ogg FLAC format:
	* (none)
* flac:
	* Added support for encoding from and decoding to the RF64 format, and a new corresponding option `--force-rf64-format`.  ([SF #1762502](http://sourceforge.net/p/flac/feature-requests/78/)). `--keep-foreign-metadata` is also supported.
	* Added support for encoding from and decoding to the Sony Wave64 format, and a new corresponding option `--force-wave64-format`. ([SF #1769582](http://sourceforge.net/p/flac/feature-requests/79/)). `--keep-foreign-metadata` is also supported.
	* Added new options `--preserve-modtime` and `--no-preserve-modtime` to specify whether or not output files should copy the timestamp and permissions from their input files.  The default is `--preserve-modtime` as in previous versions.  ([SF #1805428](http://sourceforge.net/p/flac/feature-requests/85/)).
	* Allow MM:SS:FF and MM:SS.SS time formats in non-CD-DA cuesheets.  ([SF #1947353](http://sourceforge.net/p/flac/feature-requests/95/), [SF #2182432](http://sourceforge.net/p/flac/bugs/338/))
	* The `--sector-align` option of `flac` has been deprecated and may not exist in future versions. `shntool` provides similar functionality. ([SF #1805946](http://sourceforge.net/p/flac/feature-requests/86/))
	* Improved error message when user attempts to decode a non-FLAC file ([SF #2222789](http://sourceforge.net/p/flac/bugs/341/)).
	* Fix bug where `flac` was disallowing use of `--replay-gain` when encoding from stdin ([SF #1840124](http://sourceforge.net/p/flac/bugs/313/)).
	* Fix bug with fractional seconds on some locales ([SF #1815517](http://sourceforge.net/p/flac/bugs/309/), [SF #1858012](http://sourceforge.net/p/flac/bugs/321/)).
	* Read and write appropriate channel masks for 6.1 and 7.1 surround input WAV files. Documentation was also updated.
	* Correct Wave64 GUIDs.
	* Support 56kHz to 192kHz gain analysis (patch from Earl Chew)
	* Add ability to handle unicode filenames on Windows (large set of patches from Janne Hyvärinen)
* metaflac:
	* Allow MM:SS:FF and MM:SS.SS time formats in non-CD-DA cuesheets. ([SF #1947353](http://sourceforge.net/p/flac/feature-requests/95/), [SF #2182432](http://sourceforge.net/p/flac/bugs/338/))
* plugins:
	* Minor updates for XMMS plugin.
	* Winamp2 plugin was dropped because Nullsoft has provided native FLAC support since 2006.
* build system:
	* Fixes for autotools (including <a href="http://sourceforge.net/p/flac/patches/28/">SF #1859664</a>).
	* Fixes for MinGW (including <a href="http://sourceforge.net/p/flac/bugs/">SF #2000973</a>, <a href="http://sourceforge.net/p/flac/bugs/">SF #2209829</a>).
	* Fixes for gcc (including <a href="http://sourceforge.net/p/flac/bugs/">SF #1834168</a>, <a href="http://sourceforge.net/p/flac/bugs/334/">SF #2002481</a>).
	* Fixes for Sun Studio/Forte (<a href="http://sourceforge.net/p/flac/patches/22/">SF #1701960</a>).
	* Fixes for windows builds (including <a href="http://sourceforge.net/p/flac/bugs/257/">SF #1676822</a>, <a href="http://sourceforge.net/p/flac/feature-requests/73/">SF #1756624</a>, <a href="http://sourceforge.net/p/flac/bugs/307/">SF #1809863</a>, <a href="http://sourceforge.net/p/flac/feature-requests/">SF #1911149</a>).
	* Fixes for FreeBSD and OpenBSD.
	* Compile with GNU gcc _FORTIFY_SOURCE=2 and stack protection where those features are detected.
	* Enable a bunch of GCC compiler warnings and fix code that generates warnings.
* documentation:
	* Document `--ignore-chunk-sizes` and `--apply-replaygain-which-is-not-lossless` option for `flac`.
* libraries:
	* libFLAC encoder was defaulting to level 0 compression instead of 5 (<a href="http://sourceforge.net/p/flac/bugs/310/">SF #1816825</a>).
	* Fix bug in bitreader handling of read callback returning a short count (<a href="http://sourceforge.net/p/flac/bugs/345/">SF #2490454</a>).
	* Improve decoder's ability to distinguish between a FLAC sync code and an MPEG one (<a href="http://sourceforge.net/p/flac/bugs/346/">SF #2491433</a>).
* Interface changes:
	* libFLAC:
		* <b>Added</b> FLAC__format_blocksize_is_subset()
	* libFLAC++:
		* Add a number of convenience methods.

## FLAC 1.2.1 (17-Sep-2007)

* General:
	* With the new `--keep-foreign-metadata` in `flac`, non-audio RIFF and AIFF chunks can be stored in FLAC files and recreated when decoding.  This allows, among other, things support for archiving BWF files and other WAVE files from editing tools that preserves all the metadata. 
* FLAC format:
	* Specified 2 new APPLICATION metadata blocks for storing WAVE and AIFF chunks (for use with `--keep-foreign-metadata` in `flac`).
	* The lead-out track number for non-CDDA cuesheets now must be 255.
* Ogg FLAC format:
	* This is not a format change, but changed default extension for Ogg FLAC from .ogg to .oga, according to new Xiph <a href="http://wiki.xiph.org/index.php/MIME_Types_and_File_Extensions">specification</a> (<a href="http://sourceforge.net/p/flac/bugs/283/">SF #1762492</a>).
* flac:
	* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_no_utf8_convert">--no-utf8-convert</a></span> which works like it does in `metaflac` (<a href="http://sourceforge.net/p/flac/feature-requests/35/">SF #973740</a>).
	* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_keep_foreign_metadata">--keep-foreign-metadata</a></span> which can save/restore RIFF and AIFF chunks to/from FLAC files (<a href="http://sourceforge.net/p/flac/feature-requests/9/">SF #363478</a>).
	* Changed default extension for Ogg FLAC from .ogg to .oga, according to new Xiph <a href="http://wiki.xiph.org/index.php/MIME_Types_and_File_Extensions">specification</a> (<a href="http://sourceforge.net/p/flac/bugs/283/">SF #1762492</a>).
	* Fixed bug where using <span class="argument">--replay-gain</span> without any padding option caused only a small PADDING block to be created (<a href="http://sourceforge.net/p/flac/bugs/282/">SF #1760790</a>).
	* Fixed bug where encoding from stdin on Windows could fail if WAVE/AIFF contained unknown chunks (<a href="http://sourceforge.net/p/flac/bugs/290/">SF #1776803</a>).
	* Fixed bug where importing non-CDDA cuesheets would cause an invalid lead-out track number (<a href="http://sourceforge.net/p/flac/bugs/286/">SF #1764105</a>).
* metaflac:
	* Changed default extension for Ogg FLAC from .ogg to .oga, according to new Xiph <a href="http://wiki.xiph.org/index.php/MIME_Types_and_File_Extensions">specification</a> (<a href="http://sourceforge.net/p/flac/bugs/283/">SF #1762492</a>).
	* Fixed bug where importing non-CDDA cuesheets would cause an invalid lead-out track number (<a href="http://sourceforge.net/p/flac/bugs/286/">SF #1764105</a>).
* plugins:
	* (none)
* build system:
	* New configure option <span class="argument">--disable-cpplibs</span> to prevent building libFLAC++ (<a href="http://sourceforge.net/p/flac/patches/23/">SF #1723295</a>).
	* Fixed bug compiling `flac` without Ogg support (<a href="http://sourceforge.net/p/flac/bugs/281/">SF #1760786</a>).
	* Fixed bug where sometimes an existing installation of flac could interfere with the build process (<a href="http://sourceforge.net/p/flac/bugs/285/">SF #1763690</a>).
	* OS X fixes (<a href="http://sourceforge.net/p/flac/patches/25/">SF #1786225</a>).
	* MinGW fixes (<a href="http://sourceforge.net/p/flac/bugs/264/">SF #1684879</a>).
	* Solaris 10 fixes (<a href="http://sourceforge.net/p/flac/bugs/294/">SF #1783225</a> <a href="http://sourceforge.net/p/flac/bugs/295/">SF #1783630</a>).
	* OS/2 fixes (<a href="http://sourceforge.net/p/flac/bugs/287/">SF #1771378</a> <a href="http://sourceforge.net/p/flac/bugs/174/">SF #1229495</a>).
	* automake-1.10 fixes (<a href="http://sourceforge.net/p/flac/bugs/300/">SF #1791361</a> <a href="http://sourceforge.net/p/flac/bugs/302/">SF #1792179</a>).
* documentation:
	* Added new <a href="documentation_tools_flac.html#tutorial">tutorial</a> section for `flac`.
	* Added <a href="documentation_example_code.html">example code</a> section for using libFLAC/libFLAC++.
* libraries:
	* libFLAC: Fixed very rare seek bug (<a href="http://sourceforge.net/p/flac/bugs/263/">SF #1684049</a>).
	* libFLAC: Fixed seek bug with Ogg FLAC and small streams (<a href="http://sourceforge.net/p/flac/bugs/301/">SF #1792172</a>).
	* libFLAC: 64-bit fixes (<a href="http://sourceforge.net/p/flac/bugs/299/">SF #1790872</a>).
	* libFLAC: Fix assembler code to be position independent.
	* libFLAC: Optimization of a number of inner loop functions.
	* Added support for encoding the residual coding method introduced in libFLAC 1.2.0 (RESIDUAL_CODING_METHOD_PARTITIONED_RICE2) which will  encode 24-bit files more efficiently.
* interface changes:
	* libFLAC:
		* <b>Added</b> FLAC__metadata_simple_iterator_is_last()
		* <b>Added</b> FLAC__metadata_simple_iterator_get_block_offset()
		* <b>Added</b> FLAC__metadata_simple_iterator_get_block_length()
		* <b>Added</b> FLAC__metadata_simple_iterator_get_application_id()
	* 	libFLAC++:
		* <b>Added</b> FLAC::Metadata::SimpleIterator::is_last()
		* <b>Added</b> FLAC::Metadata::SimpleIterator::get_block_offset()
		* <b>Added</b> FLAC::Metadata::SimpleIterator::get_block_length()
		* <b>Added</b> FLAC::Metadata::SimpleIterator::get_application_id()

## FLAC 1.2.0 (23-Jul-2007)

		<br />

		<ul>
			* 
				General:
				<ul>
					* Small encoding speedups for all modes.
				</ul>
			
			* 
				FLAC format:
				<ul>
					* One of the reserved bits in the FLAC frame header has been assigned for future use; make sure to refer to the <a href="api/group__porting__1__1__4__to__1__2__0.html">porting guide</a> if you parse FLAC streams manually.
				</ul>
			
			* 
				Ogg FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				flac:
				<ul>
					* Added runtime detection of SSE OS support for most operating systems.
					* Added a new undocumented option <span class="argument">--ignore-chunk-sizes</span> for ignoring the size of the 'data' chunk (WAVE) or 'SSND' chunk (AIFF).  Can be used to encode files with bogus data sizes (e.g. with WAV files piped from foobar2000 to flac.exe as an external encoder).  <b>Use with caution</b>: all subsequent data is treated as audio, so the data/SSND chunk must be the last or the following data/tags will be treated as audio and encoded.
				</ul>
			
			* 
				metaflac:
				<ul>
					* (none)
				</ul>
			
			* 
				plugins:
				<ul>
					* (none)
				</ul>
			
			* 
				build system:
				<ul>
					* Added solution and project files for building with VC++ 2005.
				</ul>
			
			* 
				libraries:
				<ul>
					* Added runtime detection of SSE OS support for most operating systems.
					* Fixed bug where invalid seek tables could cause some seeks to fail.
					* Added support for decoding the new residual coding method (RESIDUAL_CODING_METHOD_PARTITIONED_RICE2).
				</ul>
			
			* 
				Interface changes (see also the <a href="api/group__porting__1__1__4__to__1__2__0.html">porting guide</a> for specific instructions on porting to FLAC 1.2.0):
				<ul>
					* 
						libFLAC:
						<ul>
							* <b>Added</b> FLAC__format_sample_rate_is_subset()
						</ul>
					
					* 
						libFLAC++:
						<ul>
							* <b>Added</b> FLAC::Decoder::Stream::get_decode_position()
						</ul>
					
				</ul>
			
		</ul>

## FLAC 1.1.4 (13-Feb-2007)

		<ul>
			* 
				General:
				<ul>
					* Improved compression with no change to format or decrease in speed.
					* Encoding and decoding speedups for all modes.  Encoding at -8 is twice as fast.
				</ul>
			
			* 
				FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				Ogg FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				flac:
				<ul>
					* Improved compression with no change to format or decrease in speed.
					* Encoding and decoding speedups for all modes.  Encoding at -8 is twice as fast.
					* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_warnings_as_errors">-w,--warnings-as-errors</a></span> for treating all warnings as errors.
					* Allow <span class="argument"><a href="documentation_tools_flac.html#flac_options_picture">--picture</a></span> option to take only a filename, and have all other attributes extracted from the file itself.
					* Fixed a bug that caused suboptimal default compression settings in some locales (<a href="http://sourceforge.net/p/flac/bugs/237/">SF #1608883</a>).
					* Fixed a bug where FLAC-to-FLAC transcoding of a corrupted FLAC file would truncate the transcoded file at the first error (<a href="http://sourceforge.net/p/flac/bugs/241/">SF #1615019</a>).
					* Fixed a bug where using <span class="argument"><a href="documentation_tools_flac.html#flac_options_decode_through_errors">-F</a></span> with FLAC-to-FLAC transcoding of a corrupted FLAC would have no effect (<a href="http://sourceforge.net/p/flac/bugs/242/">SF #1615391</a>).
					* Fixed a bug where new PICTURE metadata blocks specified with <span class="argument"><a href="documentation_tools_flac.html#flac_options_picture">--picture</a></span> would not be transferred during FLAC-to-FLAC transcoding (<a href="http://sourceforge.net/p/flac/bugs/246/">SF #1627993</a>).
				</ul>
			
			* 
				metaflac:
				<ul>
					* Allow <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_import_picture_from">--import-picture-from</a></span> option to take only a filename, and have all other attributes extracted from the file itself.
				</ul>
			
			* 
				plugins:
				<ul>
					* Fixed a bug in the XMMS plugin where Ctrl-3 (file info) would cause a crash if the file did not exist (<a href="http://sourceforge.net/p/flac/patches/20/">SF #1634941</a>).
				</ul>
			
			* 
				build system:
				<ul>
					* Fixed a makefile linkage bug with libogg (<a href="http://sourceforge.net/p/flac/bugs/239/">SF #1611414</a>).
					* Added pkg-config files for libFLAC and libFLAC++ (<a href="http://sourceforge.net/p/flac/patches/21/">SF #1647881</a>).
					* Added <span class="argument">--disable-ogg</span> option for building without Ogg support even if libogg is installed (<a href="http://sourceforge.net/p/flac/bugs/165/">SF #1196996</a>).
				</ul>
			
			* 
				libraries:
				<ul>
					* Completely rewritten bitbuffer which uses native machine word size instead of bytes for dramatic speed improvements.  The speedup should be most dramatic on CPUs with slower byte manipulation capability and big-endian machines.
					* Much faster Rice partition size estimation which greatly speeds encoding in higher modes.
					* Increased compression for all modes.
					* Reduced memory requirements for encoder and decoder.
					* Fixed a bug with default apodization settings that were erroneous in some locales (<a href="http://sourceforge.net/p/flac/bugs/237/">SF #1608883</a>).
				</ul>
			
			* 
				Interface changes:
				<ul>
					* 
						libFLAC:
						<ul>
							* (behavior only) FLAC__stream_encoder_set_metadata() now makes a copy of the "metadata" array of pointers (but still not copies of the objects themselves) so the client does not need to maintain its copy of the array after the call.
						</ul>
					
					* 
						libFLAC++:
						<ul>
							* (none)
						</ul>
					
				</ul>
			
		</ul>

## FLAC 1.1.3 (27-Nov-2006)

		<ul>
			* 
				General:
				<ul>
					* Improved compression with no impact on format or decoding speed.
					* Much better recovery for corrupted files
					* Better multichannel support
					* Large file (&gt;2GB) support everywhere
					* `flac` now supports FLAC and Ogg FLAC as input to the encoder (e.g. can re-encode FLAC to FLAC) and preserve all the metadata like tags, etc.
					* New <span class="code"><a href="format.html#def_PICTURE">PICTURE</a></span> metadata block for storing things like cover art, new <span class="argument"><a href="documentation_tools_flac.html#flac_options_picture">--picture</a></span> option to `flac` and <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_import_picture_from">--import-picture-from</a></span> option to `metaflac` for importing pictures, new <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_export_picture_to">--export-picture-to</a></span> option to `metaflac` for exporting pictures, and metadata API <a href="api/group__flac__metadata__level0.html#ga3">additions</a> for searching for suitable pictures based on type, size and color constraints.
					* Support for new <tt>REPLAYGAIN_REFERENCE_LOUDNESS</tt> tag.
					* Fixed a bug in Ogg FLAC encoding where metadata was not being updated properly.  Existing Ogg FLAC files should be recoded to fix up the metadata, e.g. <span class="command">flac -Vf -S 10s --ogg file.ogg</span>
					* In the developer libraries, the interface has been simplfied by merging the three decoding layers into a single class; ditto for the encoders.  Also, libOggFLAC has been merged into libFLAC and libOggFLAC++ has been merged into libFLAC++ so there is a single API supporting both native FLAC and Ogg FLAC.
				</ul>
			
			* 
				FLAC format:
				<ul>
					* New <span class="code"><a href="format.html#def_PICTURE">PICTURE</a></span> metadata block for storing things like cover art.
					* Speaker assignments and channel orders for 3-6 channels (see <a href="format.html#frame_header">frame header</a>).
					* Further restrictions on the <a href="format.html#subset">FLAC subset</a> when the sample rate is &lt;=48kHz; in this case the maximum LPC order is now 12 and maximum blocksize is 4608.  This is to further limit the processing and memory requirements for hardware implementations while not measurably affecting compression.
				</ul>
			
			* 
				Ogg FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				flac:
				<ul>
					* Improved the <span class="argument"><a href="documentation_tools_flac.html#flac_options_decode_through_errors">-F</a></span> option to allow decoding of FLAC files whose metadata is corrupted, and other kinds of severe corruption.
					* Encoder can now take FLAC and Ogg FLAC as input.  The output FLAC file will have all the same metadata as the original unless overridden with options on the command line.
					* Encoder can now take WAVEFORMATEXTENSIBLE WAVE files as input; decoder will output WAVEFORMATEXTENSIBLE WAVE files when necessary to conform to the latest Microsoft specifications.
					* Now properly supports AIFF and WAVEFORMATEXTENSIBLE multichannel input, performing necessary channel reordering both for encoding and decoding.  WAVEFORMATEXTENSIBLE channel mask is also saved to a tag on encoding and restored on decoding for situations when there is no natural mapping to FLAC channel assignments.
					* Expanded support for "odd" sample resolutions to WAVE and AIFF input; all resolutions from 4 to 24 bits-per-sample now supported for all input types.
					* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_tag_from_file">--tag-from-file</a></span> for setting a tag from file (e.g. for importing a cuesheet as a tag).
					* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_picture">--picture</a></span> for adding pictures.
					* Added a new option <span class="argument"><a href="documentation_tools_flac.html#flac_options_apodization">--apodization</a></span> for specifying the window function(s) to be used in LPC analysis.
					* Added support for encoding from non-compressed AIFF-C (<a href="http://sourceforge.net/p/flac/bugs/143/">SF #1090933</a>).
					* Importing of non-CDDA-compliant cuesheets now only issues a warning, not an error (see <a href="http://www.hydrogenaud.io/forums/index.php?showtopic=31282">here</a>).
					* MD5 comparison failures on decoding are now an error instead of a warning and will also return a non-zero exit code (<a href="http://sourceforge.net/p/flac/bugs/221/">SF #1493725</a>).
					* The default padding size is now 8K, or 64K if the input audio stream is more than 20 minutes long.
					* Fixed a bug in cuesheet parsing where it would return an error if the last line of the cuesheet did not end with a newline.
					* Fixed a bug that caused a crash when <span class="argument">-a</span> and <span class="argument">-t</span> were used together (<a href="http://sourceforge.net/p/flac/bugs/173/">SF #1229481</a>).
					* Fixed a bug with --sector-align where appended samples were not always totally silent (<a href="http://sourceforge.net/p/flac/bugs/179/">SF #1237707</a>).
					* Fixed bugs with --sector-align and raw input files.
					* Fixed a bug printing out unknown AIFF subchunk names (<a href="http://sourceforge.net/p/flac/bugs/186/">SF #1267476</a>).
					* Fixed a bug where WAVE files with "data" subchunks of size 0 where accepted (<a href="http://sourceforge.net/p/flac/bugs/190/">SF #1293830</a>).
					* Fixed a bug where sync error at end-of-stream of truncated files was not being caught (<a href="http://sourceforge.net/p/flac/bugs/183/">SF #1244071</a>).
					* Fixed a problem with filename parsing if file does not have extension but also has a . in the path (<a href="http://sourceforge.net/p/flac/bugs/159/">SF #1161916</a>).
					* Fixed a problem with fractional-second parsing for <span class="argument">--skip</span>/<span class="argument">--until</span> in some locales (<a href="http://sourceforge.net/p/flac/bugs/125/">SF #1031043</a>).
					* Increase progress report rate when -p and -e are used together (<a href="http://sourceforge.net/p/flac/bugs/229/">SF #1580122</a>).
				</ul>
			
			* 
				metaflac:
				<ul>
					* Added support for read-only operations on Ogg FLAC files.
					* Added a new option <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_set_tag_from_file">--set-tag-from-file</a></span> for setting a tag from file (e.g. for importing a cuesheet as a tag).
					* Added a new option <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_import_picture_from">--import-picture-from</a></span> for importing pictures.
					* Added a new option <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_export_picture_to">--export-picture-to</a></span> for exporting pictures.
					* Added shorthand operation <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_remove_replay_gain">--remove-replay-gain</a></span> for removing ReplayGain tags.
					* <span class="argument"><a href="documentation_tools_metaflac.html#metaflac_shorthand_export_cuesheet_to">--export-cuesheet-to</a></span> now properly specifies the FLAC file name (<a href="http://sourceforge.net/p/flac/feature-requests/46/">SF #1272825</a>).
					* Importing of non-CDDA-compliant cuesheets now issues a warning.
					* Removed the following deprecated tag editing options; you should use the new option names shown instead:
						<ul>
							* Removed <span class="argument">--show-vc-vendor</span>; use <span class="argument">--show-vendor-tag</span>
							* Removed <span class="argument">--show-vc-field</span>; use <span class="argument">--show-tag</span>
							* Removed <span class="argument">--remove-vc-all</span>; use <span class="argument">--remove-all-tags</span>
							* Removed <span class="argument">--remove-vc-field</span>; use <span class="argument">--remove-tag</span>
							* Removed <span class="argument">--remove-vc-firstfield</span>; use <span class="argument">--remove-first-tag</span>
							* Removed <span class="argument">--set-vc-field</span>; use <span class="argument">--set-tag</span>
							* Removed <span class="argument">--import-vc-from</span>; use <span class="argument">--import-tags-from</span>
							* Removed <span class="argument">--export-vc-to</span>; use <span class="argument">--export-tags-to</span>
						</ul>
					
					* Disallow multiple input FLAC files when --import-tags-from=- is used (<a href="http://sourceforge.net/p/flac/bugs/141/">SF #1082577</a>).
				</ul>
			
			* 
				plugins:
				<ul>
					* When ReplayGain is on, if tags for the preferred kind of gain (album/track) are not in a stream, the other kind will be used.
					* Added ReplayGain info to file info box in XMMS plugin
					* Fixed UTF-8 decoder to disallow non-shortest-form and surrogate sequences (see <a href="http://www.unicode.org/versions/corrigendum1.html">here</a>).
				</ul>
			
			* 
				build system:
				<ul>
					* Added support for building on OS/2 with EMX (<a href="http://sourceforge.net/p/flac/bugs/174/">SF #1229495</a>)
					* Added support for building with Borland C++ (<a href="http://sourceforge.net/p/flac/patches/17/">SF #1599018</a>)
					* Added a <span class="argument">--disable-xmms-plugin</span> option to <span class="command">configure</span> to prevent building the XMMS plugin (<a href="http://sourceforge.net/p/flac/feature-requests/33/">SF #930494</a>).
					* Added a <span class="argument">--disable-doxygen-docs</span> option to <span class="command">configure</span> for disabling Doxygen-based API doc generation (<a href="http://sourceforge.net/p/flac/patches/12/">SF #1365935</a>).
					* Added a <span class="argument">--disable-thorough-tests</span> option to <span class="command">configure</span> to do the basic library, stream, and tool tests in a reasonable time (<a href="http://sourceforge.net/p/flac/feature-requests/40/">SF #1077948</a>).
					* Added large file support with <span class="argument">AC_SYS_LARGEFILE</span>; use <span class="argument">--disable-largefile</span> with <span class="command">configure</span> to disable.
				</ul>
			
			* 
				libraries:
				<ul>
					* Merged libOggFLAC into libFLAC; both formats are now supported through the same API.
					* Merged libOggFLAC++ into libFLAC++; both formats are now supported through the same API.
					* libFLAC and libFLAC++: Simplified encoder setup with new <span class="argument">FLAC__stream_encoder_set_compression_level()</span> function.
					* libFLAC: Improved compression with no impact on FLAC format or decoding time by adding a windowing stage before LPC analysis.
					* libFLAC: Fixed a bug where missing STREAMINFO fields (min/max framesize, total samples, MD5 sum) and seek point offsets were not getting rewritten back to Ogg FLAC file (<a href="http://sourceforge.net/p/flac/bugs/197/">SF #1338969</a>).
					* libFLAC: Fixed a bug in cuesheet parsing where it would return an error if the last line of the cuesheet did not end with a newline.
					* libFLAC: Fixed UTF-8 decoder to disallow non-shortest-form and surrogate sequences (see <a href="http://www.unicode.org/versions/corrigendum1.html">here</a>).
					* libFLAC: Fixed a bug in the return value for <span class="argument">FLAC__stream_decoder_set_metadata_respond_application()</span> and <span class="argument">FLAC__stream_decoder_set_metadata_ignore_application()</span> when there was a memory allocation error (<a href="http://sourceforge.net/p/flac/bugs/176/">SF #1235005</a>).
				</ul>
			
			* 
				Interface changes (see also the <a href="api/group__porting__1__1__2__to__1__1__3.html">porting guide</a> for specific instructions on porting to FLAC 1.1.3):
				<ul>
					* 
						all libraries;
						<ul>
							* Merged libOggFLAC into libFLAC; both formats are now supported through the same API.
							* Merged libOggFLAC++ into libFLAC++; both formats are now supported through the same API.
							* Merged seekable stream decoder and file decoder into the stream decoder.
							* Merged seekable stream encoder and file encoder into the stream encoder.
							* Added #defines for the API version number to make porting easier; see <tt>include/lib*FLAC*/export.h</tt>.
						</ul>
					
					* 
						libFLAC:
						<ul>
							* <b>Added</b> FLAC__stream_encoder_set_apodization()
							* <b>Added</b> FLAC__stream_encoder_set_compression_level()
							* <b>Added</b> FLAC__metadata_object_cuesheet_calculate_cddb_id()
							* <b>Added</b> FLAC__metadata_get_cuesheet()
							* <b>Added</b> FLAC__metadata_get_picture()
							* <b>Added</b> FLAC__metadata_chain_read_ogg() and FLAC__metadata_chain_read_ogg_with_callbacks()
							* <b>Changed</b> FLAC__stream_encoder_finish() now returns a FLAC__bool to signal a verify failure, or error processing last frame or updating metadata.
							* <b>Changed</b> FLAC__StreamDecoderState: removed state FLAC__STREAM_DECODER_UNPARSEABLE_STREAM
							* <b>Changed</b> FLAC__StreamDecoderErrorStatus: new error code FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM
							* The above two changes mean that when the decoder encounters what it thinks are unparseable frames from a future decoder, instead of returning a fatal error with the FLAC__STREAM_DECODER_UNPARSEABLE_STREAM state, it just calls the error callback with FLAC__STREAM_DECODER_ERROR_STATUS_UNPARSEABLE_STREAM and leaves the behavior up to the application.
						</ul>
					
					* 
						libFLAC++:
						<ul>
							* <b>Added</b> FLAC::Metadata::Picture
							* <b>Added</b> FLAC::Encoder::Stream::set_apodization()
							* <b>Added</b> FLAC::Encoder::Stream::set_compression_level()
							* <b>Added</b> FLAC::Metadata::CueSheet::calculate_cddb_id()
							* <b>Added</b> FLAC::Metadata::get_cuesheet()
							* <b>Added</b> FLAC::Metadata::get_picture()
							* <b>Changed</b> FLAC::Metadata::Chain::read() to accept a flag denoting Ogg FLAC input
							* <b>Changed</b> FLAC::Decoder::Stream::finish() now returns a bool to signal an MD5 failure like FLAC__stream_decoder_finish() does.
							* <b>Changed</b> FLAC::Encoder::Stream::finish() now returns a bool to signal a verify failure, or error processing last frame or updating metadata.
						</ul>
					
					* 
						libOggFLAC:
						<ul>
							* Merged into libFLAC.
						</ul>
					
					* 
						libOggFLAC++:
						<ul>
							* Merged into libFLAC++.
						</ul>
					
				</ul>
			
		</ul>

## FLAC 1.1.2 (05-Feb-2005)

		<ul>
			* 
				General:
				<ul>
					* Sped up decoding by a few percent overall.
					* Sped up encoding when not using LPC (i.e. when using `flac` options <span class="argument">-0</span>, <span class="argument">-1</span>, <span class="argument">-2</span>, or <span class="argument">-l 0</span>).
					* Fixed a decoding bug that could cause sync errors with some ID3v1-tagged FLAC files.
					* Added <a href="documentation_tools_metaflac.html#metaflac">HTML documentation for metaflac</a>.
				</ul>
			
			* 
				FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				Ogg FLAC format:
				<ul>
					* (none)
				</ul>
			
			* 
				flac:
				<ul>
					* New option <span class="argument"><a href="documentation_tools_flac.html#flac_options_input_size">--input-size</a></span> to manually specify the input size when encoding raw samples from stdin.
				</ul>
			
			* 
				metaflac:
				<ul>
					* (none)
				</ul>
			
			* 
				plugins:
				<ul>
					* Added support for HTTP streaming in XMMS plugin.  <b>NOTE</b>: there is a bug in the XMMS mpg123 plugin that hijacks FLAC streams; to fix it you will need to add the '.flac' extension to the list of exceptions in <span class="code">Input/mpg123/mpg123.c:is_our_file()</span> in the XMMS sources and recompile.
				</ul>
			
			* 
				build system:
				<ul>
					* (none)
				</ul>
			
			* 
				libraries:
				<ul>
					* libFLAC: Sped up Rice block decoding in the bitbuffer, resulting in decoding speed gains of a few percent.
					* libFLAC: Sped up encoding when not using LPC (i.e. <span class="code">max_lpc_order == 0</span>).
					* libFLAC: Trailing NUL characters maintained on Vorbis comment entries so they can be treated like C strings.
					* libFLAC: More FLAC tag (i.e. Vorbis comment) validation.
					* libFLAC: Fixed a bug in the logic that determines the frame or sample number in a frame header; the bug could cause sync errors with some ID3v1-tagged FLAC files.
					* libFLAC, libOggFLAC: Can now be compiled to use only integer instructions, including encoding.  The decoder is almost completely integer anyway but there were a couple places that needed a fixed-point replacement.  There is no fixed-point version of LPC analysis yet, so if libFLAC is compiled integer-only, the encoder will behave as if the max LPC order is 0 (i.e. used fixed predictors only).  LPC decoding is supported in all cases as it always was integer-only.
				</ul>
			
			* 
				Interface changes:
				<ul>
					* 
						libFLAC:
						<ul>
							* <b>Changed:</b> Metadata object interface now maintains a trailing NUL on Vorbis comment entries for convenience.
							* <b>Changed:</b> Metadata object interface now validates all Vorbis comment entries on input and returns false if an entry does not conform to the Vorbis comment spec.
							* <b>Added</b> FLAC__format_vorbiscomment_entry_name_is_legal()
							* <b>Added</b> FLAC__format_vorbiscomment_entry_value_is_legal()
							* <b>Added</b> FLAC__format_vorbiscomment_entry_is_legal()
							* <b>Added</b> FLAC__metadata_object_vorbiscomment_entry_from_name_value_pair()
							* <b>Added</b> FLAC__metadata_object_vorbiscomment_entry_to_name_value_pair()
							* <b>Changed</b> the signature of FLAC__metadata_object_vorbiscomment_entry_matches(): the first argument is now <span class="code">FLAC__StreamMetadata_VorbisComment_Entry entry</span> (was <span class="code">const FLAC__StreamMetadata_VorbisComment_Entry *entry</span>), i.e. <span class="code">entry</span> is now pass-by-value.
						</ul>
					
					* 
						libFLAC++:
						<ul>
							* <b>Changed:</b> Metadata object interface now maintains a trailing NUL on Vorbis comment values for convenience.
							* <b>Changed:</b> Metadata object interface now validates all Vorbis comment entries on input and returns false if an entry does not conform to the Vorbis comment spec.
							* <b>Changed:</b> All Metadata objects' operator=() methods now return a reference to themselves.
							* <b>Added</b> methods to FLAC::Metadata::VorbisComment::Entry for setting comment values from null-terminated strings:
								<ul>
									* Entry(const char *field)
									* Entry(const char *field_name, const char *field_value)
									* bool set_field(const char *field)
									* bool set_field_value(const char *field_value)
								</ul>
							
							* <b>Changed</b> the signature of FLAC::Metadata::VorbisComment::get_vendor_string() and FLAC::Metadata::VorbisComment::set_vendor_string() to use a UTF-8, NUL-terminated string <span class="code">const FLAC__byte *</span> for the vendor string instead of <span class="code">FLAC::Metadata::VorbisComment::Entry</span>.
							* <b>Added</b> FLAC::Metadata::*::assign() to all Metadata objects.
							* <b>Added</b> bool FLAC::Metadata::get_tags(const char *filename, VorbisComment &amp;tags)
						</ul>
					
					* 
						libOggFLAC:
						<ul>
							* (none)
						</ul>
					
					* 
						libOggFLAC++:
						<ul>
							* (none)
						</ul>
					
				</ul>
			
		</ul>

## FLAC 1.1.1 (01-Oct-2004)

		<ul>
			* 
				General:
				<ul>
					* Ogg FLAC seeking now works
					* New optimizations almost double the decoding speed on PowerPC (e.g. Mac G4/G5)
					* A native OS X release thanks to updated Project Builder and autotools files
				</ul>
			
			* 
				FLAC format:
				<ul>
					* Made invalid the metadata block type 127 so that audio frames can always be distinguished from metadata by seeing 0xff as the first byte.  (This was also required for the Ogg FLAC mapping.)
				</ul>
			
			* 
				Ogg FLAC format:
				<ul>
					* First official FLAC-&gt;Ogg bitstream mapping standardized (see new <a href="ogg_mapping.html">FLAC-to-Ogg mapping specification</a>).  See the documentation for the <span class="argument"><a href="documentation_tools_flac.html#flac_options_ogg">--ogg</a></span> switch about having to re-encode older Ogg FLAC files.
				</ul>
			
			* 
				flac:
				<ul>
					* Print an error when output file already exists instead of automatically overwriting.
					* New option <span class="argument"><a href="documentation_tools_flac.html#flac_options_force">-f</a></span> (<span class="argument"><a href="documentation_tools_flac.html#flac_options_force">--force</a></span>) to force overwriting if the output file already exists.
					* New option <span class="argument"><a href="documentation_tools_flac.html#flac_options_cue">--cue</a></span> to select a specific section to decode using cuesheet track/index points.
					* New option <span class="argument"><a href="documentation_tools_flac.html#flac_options_totally_silent">--totally-silent</a></span> to suppress all output.
					* New (but undocumented) option <span class="argument">--apply-replaygain-which-is-not-lossless</span> which applies ReplayGain to the decoded output.  See <a href="http://www.hydrogenaud.io/forums/index.php?showtopic=17293&amp;st=11">this thread</a> for usage and caveats.
					* When encoding to Ogg FLAC, use a random serial number (instead of 0 as was done before) when a serial number is not specified.
					* When encoding multiple Ogg FLAC streams, <span class="argument">--serial-number</span> or random serial number sets the first number, which is then incremented for subsequent streams (before, the same serial number was used for all streams).
					* Decoder no longer exits with an error when writing to stdout and the pipe is broken.
					* Better explanation of common error messages.
					* Default extension when writing AIFF files is .aif (before, it was .aiff).
					* Write more common representation of SANE numbers in AIFF files.
					* Bug fix: calculating ReplayGain on 48kHz streams.
					* Bug fix: check for supported block alignments in WAVE files.
					* Bug fix: "offset" field in AIFF SSND chunk properly handled.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/77/">#679166</a>: flac doesn't respect RIFF subchunk padding byte.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/90/">#828391</a>: --add-replay-gain segfaults.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/96/">#851155</a>: Can't seek to position in flac file.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/97/">#851756</a>: flac --skip --until reads entire file.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/100/">#877122</a>: problem parsing cuesheet with CATALOG entry.
					* Bug fix: <a href="http://sourceforge.net/p/flac/bugs/104/">#896057</a>: parsing ISRC number from cuesheet.
				</ul>
			
			* 
				metaflac:
				<ul>
					* Renamed the tag editing options as follows (the <span class="argument">...-vc-...</span> options still work but are deprecated):
						<ul>
							* <span class="argument">--show-vc-vendor</span> becomes <span class="argument">--show-vendor-tag</span>
							* <span class="argument">--show-vc-field</span> becomes <span class="argument">--show-tag</span>
							* <span class="argument">--remove-vc-all</span> becomes <span class="argument">--remove-all-tags</span>
							* <span class="argument">--remove-vc-field</span> becomes <span class="argument">--remove-tag</span>
							* <span class="argument">--remove-vc-firstfield</span> becomes <span class="argument">--remove-first-tag</span>
							* <span class="argument">--set-vc-field</span> becomes <span class="argument">--set-tag</span>
							* <span class="argument">--import-vc-from</span> becomes <span class="argument">--import-tags-from</span>
							* <span class="argument">--export-vc-to</span> becomes <span class="argument">--export-tags-to</span>
						</ul>
					
					* Better explanation of common error messages.
					* Bug fix: calculating ReplayGain on 48kHz streams.
					* Bug fix: incorrect numbers when printing seek points.
				</ul>
			
			* 
				plugins:
				<ul>
					* Speed optimization in ReplayGain synthesis.
					* Speed optimization in XMMS playback.
					* Support for big-endian architectures in XMMS plugin.
					* Removed support for ID3 tags.
					* Bug fix: make hard limiter default to off in XMMS plugin.
					* Bug fix: stream length calculation bug in XMMS plugin, debian bug #200435
					* Bug fix: small memory leak in XMMS plugin.
				</ul>
			
			* 
				build system:
				<ul>
					* <span class="code">ordinals.h</span> is now static, not a build-generated file anymore.
				</ul>
			
			* 
				libraries:
				<ul>
					* libFLAC: PPC+Altivec optimizations of some decoder routines.
					* libFLAC: Make stream encoder encode the blocksize and sample rate in the frame header if at all possible (not in STREAMINFO), even if subset encoding was not requested.
					* libFLAC: Bug fix: fixed seek routine where infinite loop could happen when seeking past end of stream.
					* libFLAC, libFLAC++: added methods to skip single frames, useful for quickly finding frame boundaries (see interface changes below).
					* libOggFLAC, libOggFLAC++: New seekable-stream and file encoder and decoder APIs to match native FLAC APIs (see interface changes below).
				</ul>
			
			* 
				Interface changes:
				<ul>
					* 
						libFLAC:
						<ul>
							* <b>Added</b> FLAC__metadata_get_tags()
							* <b>Added</b> callback-based versions of metadata editing functions:
								<ul>
									* FLAC__metadata_chain_read_with_callbacks()
									* FLAC__metadata_chain_write_with_callbacks()
									* FLAC__metadata_chain_write_with_callbacks_and_tempfile()
									* FLAC__metadata_chain_check_if_tempfile_needed()
								</ul>
							
							* <b>Added</b> decoder functions for skipping single frames, also useful for quickly finding frame boundaries:
								<ul>
									* FLAC__stream_decoder_skip_single_frame()
									* FLAC__seekable_stream_decoder_skip_single_frame()
									* FLAC__file_decoder_skip_single_frame()
								</ul>
							
							* <b>Added</b> new required tell callback on seekable stream encoder:
								<ul>
									* FLAC__SeekableStreamEncoderTellStatus and FLAC__SeekableStreamEncoderTellStatusString[]
									* FLAC__SeekableStreamEncoderTellCallback
									* FLAC__seekable_stream_encoder_set_tell_callback()
								</ul>
							
							* <b>Changed</b> FLAC__SeekableStreamEncoderState by adding FLAC__SEEKABLE_STREAM_ENCODER_TELL_ERROR
							* <b>Changed</b> Tell callback is now required to initialize seekable stream encoder
							* <b>Deleted</b> erroneous and unimplemented FLAC__file_decoder_process_remaining_frames()
						</ul>
					
					* 
						libFLAC++:
						<ul>
							* <b>Added</b> FLAC::Metadata::get_tags()
							* <b>Added</b> decoder functions for skipping single frames, also useful for quickly finding frame boundaries:
								<ul>
									* FLAC::Decoder::Stream::skip_single_frame()
									* FLAC::Decoder::SeekableStream::skip_single_frame()
									* FLAC::Decoder::File::skip_single_frame()
								</ul>
							
							* <b>Added</b> encoder functions for setting metadata:
								<ul>
									* FLAC::Encoder::Stream::set_metadata(FLAC::Metadata::Prototype **metadata, unsigned num_blocks)
									* FLAC::Encoder::SeekableStream::set_metadata(FLAC::Metadata::Prototype **metadata, unsigned num_blocks)
									* FLAC::Encoder::File::set_metadata(FLAC::Metadata::Prototype **metadata, unsigned num_blocks)
								</ul>
							
							* <b>Added</b> new required tell callback on seekable stream encoder:
								<ul>
									* pure virtual FLAC::Encoder::SeekableStream::tell_callback()
								</ul>
							
							* <b>Changed</b> Tell callback is now required to initialize seekable stream encoder
							* <b>Deleted</b> the following methods:
								<ul>
									* FLAC::Decoder::Stream::State::resolved_as_cstring()
									* FLAC::Encoder::Stream::State::resolved_as_cstring()
								</ul>
							
						</ul>
					
					* 
						libOggFLAC:
						<ul>
							* <b>Added</b> OggFLAC__SeekableStreamDecoder interface
							* <b>Added</b> OggFLAC__FileDecoder interface
							* <b>Added</b> OggFLAC__SeekableStreamEncoder interface
							* <b>Added</b> OggFLAC__FileEncoder interface
							* <b>Added</b> OggFLAC__stream_decoder_get_resolved_state_string()
							* <b>Added</b> OggFLAC__stream_encoder_get_resolved_state_string()
							* <b>Added</b> OggFLAC__stream_encoder_set_metadata_callback()
							* <b>Changed</b> OggFLAC__StreamDecoderState by adding OggFLAC__STREAM_DECODER_END_OF_STREAM
						</ul>
					
					* 
						libOggFLAC++:
						<ul>
							* <b>Added</b> OggFLAC::Decoder::SeekableStream interface
							* <b>Added</b> OggFLAC::Decoder::File interface
							* <b>Added</b> OggFLAC::Encoder::SeekableStream interface
							* <b>Added</b> OggFLAC::Encoder::File interface
							* <b>Added</b> OggFLAC::Decoder::Stream::get_resolved_state_string()
							* <b>Added</b> OggFLAC::Encoder::Stream::get_resolved_state_string()
							* <b>Added</b> pure virtual OggFLAC::Encoder::Stream::metadata_callback()
						</ul>
					
				</ul>
			
		</ul>

## FLAC 1.1.0 (26-Jan-2003)

* General:
	* All code is now <a href="http://valgrind.org/">Valgrind</a>-clean!
	* New <a href="format.html#def_CUESHEET">CUESHEET</a> metadata block for storing CD TOC and index point information.  Now a CD can be completely backed up to a single FLAC file for archival.
	* <a href="http://www.replaygain.org/">ReplayGain</a> support.
	* Better compression of 24-bit files.
	* More complete AIFF support.
	* 3DNow! optimizations enabled by default.
	* Complete MSVC build system with .dsp projects for everything, which can build both static libs and DLLs, and in debug or release mode, all in the same source tree.
* `flac`:
	* Can now decode FLAC to AIFF; new <span class="argument">--force-aiff-format</span> option.
	* New <span class="argument">--cuesheet</span> option for reading and storing a cuesheet when encoding a whole CD.  Automatically creates seek points for track and index points unless <span class="argument">--no-cued-seekpoints</span> is used.
	* New <span class="argument">--replay-gain</span> option for calculating ReplayGain values and storing them as tags.
	* New <span class="argument">--until</span> option complements <span class="argument">--skip</span> to stop decoding at a specified point in the stream.
	* <span class="argument">--skip</span> and <span class="argument">--until</span> now also accept mm:ss.ss format.
	* New <span class="argument">-S #s</span> flavor to specify seekpoints every '#' number of seconds.
	* `flac` now defaults to <span class="argument">-S 10s</span> instead of <span class="argument">-S 100x</span> for the seek table.
	* `flac` now adds a 4k PADDING block by default (turn off with <span class="argument">--no-padding</span>).
	* Fixed a bug with --skip and AIFF-to-FLAC encoding.
	* Fixed a bug where decoding a FLAC file whose total_samples==0 in the STREAMINFO would corrupt the WAVE header.
* `metaflac`:
	* New <span class="argument">--import-cuesheet-from</span> option for reading and storing a cuesheet to a FLAC-encoded CD.  Automatically creates seek points for track and index points unless <span class="argument">--no-cued-seekpoints</span> is used.
	* New <span class="argument">--export-cuesheet-to</span> option for writing a cuesheet from a FLAC file for use with CD authoring software.
	* New <span class="argument">--add-replay-gain</span> option for calculating ReplayGain values and storing them as tags.
	* New <span class="argument">--add-seekpoint</span> option to add seekpoints to an existing FLAC file.  Includes new <span class="argument">--add-seekpoint=#s</span> flavor to add seekpoints every '#' number of seconds.
* XMMS plugin:
	* Configurable sample resolution conversion with dither.
	* ReplayGain support with customizable noise shaping, pre-amp, and optional hard limiter.
	* New Vorbis comment editor.
	* File info now works.
	* Bitrate now shows the smoothed instantaneous bitrate.
	* Uses the ARTIST tag if there is no PERFORMER tag.
* Winamp2 plugin:
	* Configurable sample resolution conversion with dither.
	* ReplayGain support with customizable noise shaping, pre-amp, and optional hard limiter.
	* File info now works.
	* Uses the ARTIST tag if there is no PERFORMER tag.
* Libraries (developers take note!):
	* All code and tests are instrumented for Valgrind.  All tests run Valgrind-clean, meaning no memory leaks or buffer over/under-runs.
	* Separate 64-bit datapath through the filter in `libFLAC` for better compression of &gt;16 bps files.
	* <span class="code">FLAC__metadata_object_new(FLAC__METADATA_TYPE_VORBIS_COMMENT)</span> now sets the vendor string.
	* The documentation on the usage of <span class="code">FLAC::Iterator::get_block()</span> in `libFLAC++` has an important correction.  If you use this class make sure to read <a href="api/group__flacpp__metadata__level2.html">this</a>.

## FLAC 1.0.4 (24-Sep-2002)

Plugins:

* Support for Vorbis comments, ID3 v1 and v2 tags.
* Configurable title formatting and charset conversion in XMMS plugin.
* Support for 8- and 24-bit FLAC files.  There is a compile-time option for raw 24-bit output or 24bps-to-16bps linear dithering (the default).

`flac`:

* Improved option parser (now uses getopt).
* AIFF input support (thanks to Brady Patterson).
* Small decoder speedup.
* <span class="argument">--sector-align</span> now supported for raw input files.
* New -T, --tag options for adding Vorbis comments while encoding.
* New --serial-number option for use with --ogg.
* Automatically writes vendor string in Vorbis comments.
* Drastically reduced memory requirements.
* Fixed bug where extra fmt/data chunks that were supposed to be skipped were not getting skipped.
* Fixed bug in granulepos setting for Ogg FLAC streams.
* Fixed memory leak when encoding multiple files with -V.

`metaflac`:

* UTF-8 support in Vorbis comments.
* Fixed [bug #606796](http://sourceforge.net/p/flac/bugs/54/) where `metaflac` was failing on read-only files.
* New --import-vc-from and --export-vc-to commands for importing/exporting Vorbis comments from/to a file.  For example, the following can be used to copy tags back and forth:
```
metaflac --export-vc-to=- --no-utf8-convert file.flac | vorbiscomment --raw -w file.ogg<br />
vorbiscomment --raw -l file.ogg | metaflac --import-vc-from=- --no-utf8-convert file.flac<br />
```

Libraries:

* All APIs now meticulously documented via Doxygen.
* New `libOggFLAC` and `libOggFLAC++` libraries.  These wrap around `libFLAC` to provide encoding and decoding of Ogg FLAC streams, providing interfaces similar to the ones of the native FLAC libraries.  These are also documented via Doxygen.
* New FLAC__SeekableStreamEncoder and FLAC__FileEncoder in `libFLAC` simplify common encoding tasks.
* New verify mode in all encoders.
* FLAC__stream_encoder_finish() now resets the defaults just like the stream decoders.
* Drastically reduced memory requirements of encoders and decoders.
* Encoder now automatically writes vendor string in VORBIS_COMMENT block.
* Encoding speedup of fixed predictors and MD5 speedup for 16bps mono/stereo signals on x86 (thanks to Miroslav Lichvar).
* Fixed bug in metadata interface where a bps in STREAMINFO > 16 was incorrectly parsed.
* Fixed bug where aborting stream decoder could cause infinite loop.
* Behavior change: simplified decoder *_process() commands.
* Behavior change: calling FLAC__stream_encoder_init() calls write callback once for "fLaC" signature and once for each metadata block.
* Behavior change: deprecated do_escape_coding and rice_parameter_search_distance in encoder.


## FLAC 1.0.3 (03-Jul-2002)

New features:

* 24-bit input support restored in `flac`.
* Decoder speedup in `libFLAC`, which is directly passed on to the command-line decoder and plugins.
* New `-F` option to `flac` to continue decoding in spite of errors.
* Correctly set granulepos in Ogg packets so seeking Ogg FLAC streams will be easier.
* New VORBIS_COMMENT metadata block for tagging with Vorbis-style comments.
* Vastly improved `metaflac`, now with many editing and tagging options.
* Partial id3v1 support in Winamp plugins.
* Updated Winamp 3 plugin.
* Note: new semantics for -P option in `flac`.
* Note: removed -R option in `flac`.

New library features:

* Previously mentioned decoder speedup in `libFLAC`.
* New metadata interface to `libFLAC` for manipulating metadata in FLAC files.
* New `libFLAC++` API, an object wrapper around `libFLAC`.
* New VORBIS_COMMENT metadata block for tagging with Vorbis-style comments.
* Customizable metadata filtering by type in decoders.
* Stream encoder can take an arbitrary list of metadata blocks, instead of just one SEEKTABLE and/or PADDING block.

Bugs fixed:

* Fixed bug with using pipes under Windows.
* Fixed several bugs in the plugins and made them more robust in general.
* Fixed bug in `flac` where decoding to WAVE of a FLAC file with 0 for total_samples in the STREAMINFO block yielded a WAVE chunk of 0 size.
* Fixed bug in Ogg packet numbering.


## FLAC 1.0.2 (03-Dec-2001)

This release is only to fix a bug that was causing some of the plugins to crash sporadically.  It can also affect `libFLAC` users that reuse one file decoder instance for multiple files


## FLAC 1.0.1 (14-Nov-2001)

New features for users:

* Support for Ogg-FLAC, i.e. `flac` can now read and write FLAC streams using Ogg as the transport layer.
* New Winamp 3 plugin based on the Wasabi Beta 1 SDK.
* New utilities for adding FLAC support to the Monkey's Audio GUI (see how).
* Mac OS X support.  The download area now contains an OS X binary release.
* Mingw32 support.
* Better handling of MS-specific 'fmt' chunks in WAVE files.

New features for developers:

* Added a SeekableStreamDecoder layer between StreamDecoder and FileDecoder.  This makes it easier to use libFLAC in situations where files have been abstracted away.  See the latest documentation for more.  The interface for the StreamDecoder and FileDecoder remain the same and are still binary-compatible with libFLAC 1.0.
* Drastically reduced the stack requirements of the encoder.

Bug fixes:

* Fixed a serious bug with `flac` and raw input where the encoder was trying to rewind when it shouldn't, which would add 12 junk samples to the encoded file.  This was not present in WAVE encoding.
* Fixed a minor bug in `libFLAC` with setting the file name to stdin on a file decoder.
* Fixed a minor bug in `libFLAC` where multiple calls to setting the file name on a file decoder caused leaked memory.
* Fixed a minor bug in `metaflac`, now correctly skips an id3v2 tag if present.
* Fixed a minor bug in `metaflac`, now correctly skips long metadata blocks.


## FLAC 1.0 (20-Jul-2001)

It's finally here.  There are a few new features but mostly it is minor bug fixes since 0.10:

* New '--sector-align' option to `flac` which aligns a group of encoded files on CD audio sector boundaries.
* New '--output-prefix' option to `flac` to allow the user to prepend a prefix to all output filenames (useful, for example, for encoding/decoding to a different directory).
* Better WAVE autodetection (doesn't rely on ungetc() anymore).
* Cleaner one-line encoding/decoding stats.
* Changes to the libFLAC interface and type names to make binary compatibility easier to maintain in the future.
* New '--sse-os' option to 'configure' to enable faster SSE-based routines.
* Another (hopefully last) fix to the Winamp 2 plugin.
* Slightly improved Rice parameter estimation.
* Bug fixes for some very rare corner cases when encoding.


## FLAC 0.10 (07-Jun-2001)

This is probably the final beta.  There have been many improvements in the last two months:

* Both the encoder and decoder have been significantly sped up.  Aside from C improvements, the code base now has an assembly infrastructure that allows assembly routines for different architectures to be easily integrated.  Many key routines have now have faster IA-32 implementations (thanks to Miroslav).
* A new metadata block <a href="format.html#def_SEEKTABLE">SEEKTABLE</a> has been defined to hold an arbitrary number of seek points, which speeds up seeking within a stream.
* `flac` now has a command-line usage similar to 'gzip'; make sure to see the latest <a href="documentation.html">documentation</a> for the new usage.  It also attempts to preserve the input file's timestamp and permissions.
* The -# options in `flac` have been tweaked to yield the best compression-to-encode-time ratios.  The new default is -5.
* `flac` can now usually autodetect WAVE files when encoding so that -fw is usually not needed when encoding from stdin.
* The WAVE reader in `flac` now just ignores (with a warning) unsupported sub-chunks instead of aborting with an error.
* Added an option '--delete-input-file' to `flac` which automatically deletes the input after a successful encode/decode.
* Added an option '-o' to `flac` to force the output file name (the old usage of "flac - outputfilename" is no longer supported).
* Changed the XMMS plugin to send smaller chunks of samples (now 512) so that visualization is not slow.
* Fixed a bug in the stream decoder where the decoded samples counter got corrupted after a seek.


## FLAC 0.9 (31-Mar-2001)

* FLAC's sync code has been lengthened to 14 bits from 9 bits.  This should enable a faster and more robust synchronization mechanism.
* Two reserved bits were added to the frame header.
* A CRC-16 was added to the FLAC frame footer, and the decoder now does frame integrity checking based on the CRC.
* The format now includes a new subframe field to indicate when a subblock has one or more 0 LSBs for all samples.  This increases compression on some kinds of data.
* Added two options to the analysis mode, one for including the residual signal in the analysis file, and one for generating gnuplot files of each subframe's residual distribution with some statistics.  See the latest documentation.
* XMMS plugin now supports 8-bit files.
* Fixed a bug in the Winamp2 plugin where the audio sounded garbled.
* Fixed a bug in the Winamp2 plugin where Winamp would hang sporadically at the end of a track (c.f. [bug #231197](http://sourceforge.net/projects/flac/&amp;atid=113478)).


## FLAC 0.8 (05-Mar-2001)

FLAC is very close to being ready for an official release.  The only known problems left are with the Winamp plugins, which should be fixed soon, and pipes with MSVC.

* Created a new utility called `metaflac`.  It is a metadata editor for .flac files.  Right now it just lists the contents of the metadata blocks but eventually it will allow update/insertion/deletion.
* Added two new metadata blocks: PADDING which has an obvious function, and APPLICATION, which is meant to be open to third party applications.  See the latest format docs for more info, or the new id registration page.
* Added a `-P` option to `flac` to reserve a PADDING block when encoding.
* Added support for 24-bit files to `flac` (the FLAC format always supported it).
* Started the Winamp3 plugin.
* Greatly expanded the test suite, adding more streams (24-bit streams, noise streams, non-audio streams, more patterns) and more option combinations to the encoder.  The test suite runs about 30 streams and over 5000 encodings now.
* Fixed a bug in `libFLAC` that happened when using an exhaustive LPC coefficient quantization search with 8 bps input.
* Fixed a bug in `libFLAC` where the error estimation in the fixed predictor could overflow.
* Fixed a bug in `libFLAC` where LPC was attempted even when the autocorrelation coefficients implied it wouldn't help.
* Reworked the LPC coefficient quantizer, which also fixed another bug that might occur in rare cases.
* Really fixed the '-V overflow' bug (c.f. [bug #231976](http://sourceforge.net/p/flac/bugs/5/)).
* Fixed a bug in `flac` related to the decode buffer sizing.


## FLAC 0.7 (12-Feb-2001)
Changes:
* Fixed a bug that happened when both -fr and --seek were used at the same time.
* Fixed a bug with -p (c.f. [bug #230992](http://sourceforge.net/p/flac/bugs/1/)).
* Fixed a bug that happened when using large (>32K) blocksizes and -V (c.f. [bug #231976](http://sourceforge.net/p/flac/bugs/5/)).
* Fixed a bug where encoder was double-closing a file.
* Expanded the test suite.
* Added more optimization flags for gcc, which should speed up flac.


## FLAC 0.6 (28-Jan-2001)

The encoder is now much faster.  The -m option has been sped up by 4x and -r improved, meaning that in the default compression mode (-6), encoding should be at least 3 times faster.  Other changes:
* Some bugs related to `flac` and pipes were fixed
* A "loose mid-side" (`-M`) option to the encoder has been added, which adaptively switches between independent and mid-side coding, instead of the exhaustive search that `-m` does.
* An analyze mode (<span class="argument">-a</span>) has been added to `flac`.  This is useful mainly for developers; currently it will dump info about each frame and subframe to a file.  It's a text file in a format that can be easily processed by scripts; a separate analysis program is in the works.
* The source now has an autoconf/libtool-based build system.  This should allow the source to build "out-of-the-box" on many more platforms.


## FLAC 0.5 (15-Jan-2001)
This is the first beta version of FLAC.  Being beta, there will be no changes to the format that will break older streams, unless a serious bug involving the format is found.  What this means is that, barring such a bug, streams created with 0.5 will be decodable by future versions.  This version also includes some new features:
* An MD5 signature of the unencoded audio is computed during encoding, and stored in the Encoding metadata block in the stream header.  When decoding, `flac` will now compute the MD5 signature of the decoded data and compare it against the signature in the stream header.
* A test mode (`-t`) has been added to `flac`.  It works like decode mode but doesn't write an output file.


## FLAC 0.4 (23-Dec-2000)
This version fixes a bug in the constant subframe detection.  More importantly, a verify option (-V) has been added to `flac` that verifies the encoding process.  With this option turned on, `flac` will create a parallel decoder while encoding to make sure that the encoded output decodes to exactly match the original input.  In this way, any unknown bug in the encoder will be caught and `flac` will abort with an error message.

