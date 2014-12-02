/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "convdec_impl.h"

namespace gr {
  namespace viterbi {

    convdec::sptr
    convdec::make(int N, int M, int g1,int g2)
    {
      return gnuradio::get_initial_sptr
        (new convdec_impl(N, M, g1, g2));
    }

    /*
     * The private constructor
     */
    convdec_impl::convdec_impl(int N, int M, int g1,int g2)
      : gr::block("convdec",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(char))), d_M(M), d_N(N)
    {
	//set_outputmultiple(d_N);
	set_trellis(&d_t,M,g1,g2,1);
	set_d_all(d_t, N+M-1);
	set_d_bmsps(d_t);
	printf("num states=%d\t", d_t.numStates);
	printf("constr length=%d\n", d_t.K);
	set_output_multiple(d_N);
//	d_bmsps[d_t.numStates-1].sp=100.0;
//	d_all[d_t.numStates-1][N].tracepath=100.0;
//        printf("\t%3.1f\t%d\t", d_bmsps[3].sp, d_all[d_t.numStates-1][N].tracepath);
	}

    /*
     * Our virtual destructor.
     */
    convdec_impl::~convdec_impl()
    {
    }

    void
    convdec_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
       ninput_items_required[0] = 2*(noutput_items+d_M-1);
    }

    int
    convdec_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
       char *out = (char*) output_items[0];
	int F=noutput_items/d_N;
       for(int j=0; j<F;j++){
	convdecode(&in[j*2*(d_N+d_M-1)], &out[j*d_N], d_N, &d_t, d_all, d_bmsps);
//	printf("\noutputs %d %d", noutput_items,j);
				}
	//for(int j=0;j<d_N;j++)
	//printf("\nout %d %d",j, out[j]);
        consume_each (2*(d_N+d_M-1)*F);
	//printf("no ccd %d\n", noutput_items);
        // Tell runtime system how many output items we produced.
        return d_N*F;
    }

  } /* namespace viterbi */
} /* namespace gr */

