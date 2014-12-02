/* -*- c++ -*- */

#define VITERBI_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "viterbi_swig_doc.i"

%{
#include "viterbi/vitsova.h"
#include "viterbi/convdec.h"
#include "viterbi/interleave_ff.h"
#include "viterbi/convenc_bf.h"
#include "viterbi/zeropad_bb.h"
#include "viterbi/bercount_b.h"
#include "viterbi/awgn_cc.h"
#include "viterbi/gmskmod_bc.h"
#include "viterbi/nrz_encoder.h"
#include "viterbi/gmskmf_cf.h"
#include "viterbi/addgsmtr26_bb.h"
#include "viterbi/dropfirstN_ff.h"
#include "viterbi/nrz_decode_fb.h"
#include "viterbi/hist_test.h"
#include "viterbi/framer_bb.h"
#include "viterbi/demod_cf.h"
#include "viterbi/sync_cc.h"
#include "viterbi/dropfirstN_bb.h"
#include "viterbi/addfirstN_bb.h"
#include "viterbi/channel_dop_cc.h"
#include "viterbi/doubleS_channel_dop_cc.h"
%}


%include "viterbi/vitsova.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, vitsova);
%include "viterbi/convdec.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, convdec);
%include "viterbi/interleave_ff.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, interleave_ff);

%include "viterbi/convenc_bf.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, convenc_bf);
%include "viterbi/zeropad_bb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, zeropad_bb);

%include "viterbi/bercount_b.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, bercount_b);
%include "viterbi/awgn_cc.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, awgn_cc);
%include "viterbi/gmskmod_bc.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, gmskmod_bc);
%include "viterbi/nrz_encoder.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, nrz_encoder);
%include "viterbi/gmskmf_cf.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, gmskmf_cf);
%include "viterbi/addgsmtr26_bb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, addgsmtr26_bb);
%include "viterbi/dropfirstN_ff.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, dropfirstN_ff);
%include "viterbi/nrz_decode_fb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, nrz_decode_fb);
%include "viterbi/hist_test.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, hist_test);
%include "viterbi/framer_bb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, framer_bb);
%include "viterbi/demod_cf.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, demod_cf);
%include "viterbi/sync_cc.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, sync_cc);
%include "viterbi/dropfirstN_bb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, dropfirstN_bb);
%include "viterbi/addfirstN_bb.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, addfirstN_bb);
%include "viterbi/channel_dop_cc.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, channel_dop_cc);

%include "viterbi/doubleS_channel_dop_cc.h"
GR_SWIG_BLOCK_MAGIC2(viterbi, doubleS_channel_dop_cc);
