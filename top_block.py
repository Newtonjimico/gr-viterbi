#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Sat Nov 29 22:02:54 2014
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
from scipy import sqrt, log10, power
import numpy
import viterbi

class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.dssize = dssize = 40
        self.schsize = schsize = dssize
        self.samp_rate = samp_rate = 50000000
        self.rows = rows = 30
        self.nslot = nslot = 21
        self.g2 = g2 = 113
        self.g1 = g1 = 91
        self.fcchsize = fcchsize = 80
        self.ebno = ebno = 8
        self.ds_size = ds_size = 30
        self.cols = cols = 60
        self.cc_len = cc_len = 900
        self.ConstK = ConstK = 7
        self.BT = BT = 0.3

        ##################################################
        # Blocks
        ##################################################
        self.viterbi_zeropad_bb_0 = viterbi.zeropad_bb(cc_len-ConstK+1, ConstK-1)
        self.viterbi_sync_cc_0 = viterbi.sync_cc(nslot,fcchsize,schsize,dssize)
        self.viterbi_nrz_encoder_0 = viterbi.nrz_encoder(True, 1)
        self.viterbi_nrz_decode_fb_0 = viterbi.nrz_decode_fb(-1)
        self.viterbi_interleave_ff_0_0 = viterbi.interleave_ff(cols, rows)
        self.viterbi_interleave_ff_0 = viterbi.interleave_ff(rows, cols)
        self.viterbi_gmskmod_bc_0 = viterbi.gmskmod_bc(1, 3, BT)
        self.viterbi_framer_bb_0 = viterbi.framer_bb(nslot,fcchsize, schsize, dssize)
        self.viterbi_dropfirstN_ff_0 = viterbi.dropfirstN_ff((dssize-2)*nslot)
        self.viterbi_demod_cf_0 = viterbi.demod_cf(nslot,fcchsize,schsize,dssize)
        self.viterbi_convenc_bf_0 = viterbi.convenc_bf(ConstK, g1, g2)
        self.viterbi_convdec_0 = viterbi.convdec(cc_len-ConstK+1, ConstK, g1, g2)
        self.viterbi_bercount_b_0 = viterbi.bercount_b("/home/jayram/Desktop/ber_k7z.dat", True, ebno, 20000000)
        self.viterbi_awgn_cc_0 = viterbi.awgn_cc(sqrt(power(10, - (ebno-3)/10.0)), 47)
        self.viterbi_addfirstN_bb_0 = viterbi.addfirstN_bb(nslot*(dssize-2))
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((-1, ))
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, cc_len*1000)), True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.viterbi_interleave_ff_0_0, 0), (self.viterbi_convdec_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.viterbi_interleave_ff_0_0, 0))
        self.connect((self.viterbi_convenc_bf_0, 0), (self.viterbi_interleave_ff_0, 0))
        self.connect((self.viterbi_nrz_encoder_0, 0), (self.viterbi_gmskmod_bc_0, 0))
        self.connect((self.viterbi_interleave_ff_0, 0), (self.viterbi_nrz_decode_fb_0, 0))
        self.connect((self.viterbi_gmskmod_bc_0, 0), (self.viterbi_awgn_cc_0, 0))
        self.connect((self.viterbi_framer_bb_0, 0), (self.viterbi_nrz_encoder_0, 0))
        self.connect((self.viterbi_awgn_cc_0, 0), (self.viterbi_sync_cc_0, 0))
        self.connect((self.viterbi_sync_cc_0, 0), (self.viterbi_demod_cf_0, 0))
        self.connect((self.viterbi_zeropad_bb_0, 0), (self.viterbi_convenc_bf_0, 0))
        self.connect((self.viterbi_convdec_0, 0), (self.viterbi_bercount_b_0, 1))
        self.connect((self.analog_random_source_x_0, 0), (self.viterbi_zeropad_bb_0, 0))
        self.connect((self.viterbi_demod_cf_0, 0), (self.viterbi_dropfirstN_ff_0, 0))
        self.connect((self.viterbi_dropfirstN_ff_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.viterbi_bercount_b_0, 0))
        self.connect((self.viterbi_nrz_decode_fb_0, 0), (self.viterbi_addfirstN_bb_0, 0))
        self.connect((self.viterbi_addfirstN_bb_0, 0), (self.viterbi_framer_bb_0, 0))


# QT sink close method reimplementation

    def get_dssize(self):
        return self.dssize

    def set_dssize(self, dssize):
        self.dssize = dssize
        self.set_schsize(self.dssize)

    def get_schsize(self):
        return self.schsize

    def set_schsize(self, schsize):
        self.schsize = schsize

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_rows(self):
        return self.rows

    def set_rows(self, rows):
        self.rows = rows

    def get_nslot(self):
        return self.nslot

    def set_nslot(self, nslot):
        self.nslot = nslot

    def get_g2(self):
        return self.g2

    def set_g2(self, g2):
        self.g2 = g2

    def get_g1(self):
        return self.g1

    def set_g1(self, g1):
        self.g1 = g1

    def get_fcchsize(self):
        return self.fcchsize

    def set_fcchsize(self, fcchsize):
        self.fcchsize = fcchsize

    def get_ebno(self):
        return self.ebno

    def set_ebno(self, ebno):
        self.ebno = ebno

    def get_ds_size(self):
        return self.ds_size

    def set_ds_size(self, ds_size):
        self.ds_size = ds_size

    def get_cols(self):
        return self.cols

    def set_cols(self, cols):
        self.cols = cols

    def get_cc_len(self):
        return self.cc_len

    def set_cc_len(self, cc_len):
        self.cc_len = cc_len

    def get_ConstK(self):
        return self.ConstK

    def set_ConstK(self, ConstK):
        self.ConstK = ConstK

    def get_BT(self):
        return self.BT

    def set_BT(self, BT):
        self.BT = BT

if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.start()
    raw_input('Press Enter to quit: ')
    tb.stop()
    tb.wait()

