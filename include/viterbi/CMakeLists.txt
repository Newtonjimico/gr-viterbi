# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    vitsova.h
    convdec.h
    interleave_ff.h
    convenc_bf.h
    zeropad_bb.h
    bercount_b.h
    awgn_cc.h
    gmskmod_bc.h
    nrz_encoder.h
    gmskmf_cf.h
    addgsmtr26_bb.h
    dropfirstN_ff.h
    nrz_decode_fb.h
    hist_test.h
    framer_bb.h
    demod_cf.h
    sync_cc.h
    dropfirstN_bb.h
    addfirstN_bb.h
    channel_dop_cc.h
    doubleS_channel_dop_cc.h DESTINATION include/viterbi
)
