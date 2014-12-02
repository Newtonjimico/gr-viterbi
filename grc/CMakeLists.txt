# Copyright 2011 Free Software Foundation, Inc.
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
install(FILES
    viterbi_vitsova.xml
    viterbi_convdec.xml
    viterbi_interleave_ff.xml
    viterbi_convenc_bf.xml
    viterbi_zeropad_bb.xml
    viterbi_bercount_b.xml
    viterbi_awgn_cc.xml
    viterbi_gmskmod_bc.xml
    viterbi_nrz_encoder.xml
    viterbi_gmskmf_cf.xml
    viterbi_addgsmtr26_bb.xml
    viterbi_dropfirstN_ff.xml
    viterbi_nrz_decode_fb.xml
    viterbi_hist_test.xml
    viterbi_framer_bb.xml
    viterbi_demod_cf.xml
    viterbi_sync_cc.xml
    viterbi_dropfirstN_bb.xml
    viterbi_addfirstN_bb.xml
    viterbi_channel_dop_cc.xml
    viterbi_doubleS_channel_dop_cc.xml DESTINATION share/gnuradio/grc/blocks
)
