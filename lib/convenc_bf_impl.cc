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
#include "convenc_bf_impl.h"
#include <stdio.h>
namespace gr {
  namespace viterbi {

    convenc_bf::sptr
    convenc_bf::make(int K, int g1, int g2)
    {
      return gnuradio::get_initial_sptr
        (new convenc_bf_impl(K, g1, g2));
    }

    /*
     * The private constructor
     */
    convenc_bf_impl::convenc_bf_impl(int K, int g1, int g2)
      : gr::sync_interpolator("convenc_bf",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(float)),2), d_K(K)
    {
	set_trellis(&d_t,K,g1,g2,1);	
	}

    /*
     * Our virtual destructor.
     */
    convenc_bf_impl::~convenc_bf_impl()
    {
    }

    int
    convenc_bf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        float *out = (float *) output_items[0];

static char state=0;

for(unsigned int j=0;j<noutput_items/2;j++){
	if(in[j]==0){
		
		out[j<<1]=d_t.noutputg1[0][state];
		out[(j<<1)+1]=d_t.noutputg2[0][state];		
		//printf("state %d\t j=%d\tin=%d\t%d%d\n",state,j, in[j], out[j<<1],out[(j<<1) +1]);
		state=state>>1;
		}
	else{	
		out[j<<1]=d_t.noutputg1[1][state];
		out[(j<<1)+1]=d_t.noutputg2[1][state];
		//printf("state %d\t j=%d\tin=%d\t%d%d\n",state,j, in[j], out[j<<1],out[(j<<1) +1]);
		state= (state | d_t.numStates) >>1; 
		}       
	//printf("\n%d in %d\tout %1.0f%1.0f",j,in[j], out[j<<1], out[(j<<1)+1]);
					
	}
	//printf("convenc no=%d\n", noutput_items);
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

