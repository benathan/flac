#!/bin/sh -e

#  FLAC - Free Lossless Audio Codec
#  Copyright (C) 2012-2022  Xiph.Org Foundation
#
#  This file is part the FLAC project.  FLAC is comprised of several
#  components distributed under different licenses.  The codec libraries
#  are distributed under Xiph.Org's BSD-like license (see the file
#  COPYING.Xiph in this distribution).  All other programs, libraries, and
#  plugins are distributed under the GPL (see COPYING.GPL).  The documentation
#  is distributed under the Gnu FDL (see COPYING.FDL).  Each file in the
#  FLAC distribution contains at the top the terms under which it may be
#  distributed.
#
#  Since this particular file is relevant to all components of FLAC,
#  it may be distributed under the Xiph.Org license, which is the least
#  restrictive of those mentioned above.  See the file COPYING.Xiph in this
#  distribution.

. ./common.sh

PATH="$(pwd)/../src/flac:$PATH"
PATH=../src/test_streams:$PATH
PATH=../objs/$BUILD/bin:$PATH


echo "Generating streams..."
if [ ! -f wacky1.wav ] ; then
        test_streams || die "ERROR: missing files"
fi
