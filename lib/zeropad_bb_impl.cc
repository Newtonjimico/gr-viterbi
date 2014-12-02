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
#include "zeropad_bb_impl.h"
#include<stdio.h>
namespace gr {
  namespace viterbi {

    zeropad_bb::sptr
    zeropad_bb::make(int L,int M)
    {
      return gnuradio::get_initial_sptr
        (new zeropad_bb_impl(L, M));
    }

    /*
     * The private constructor
     */
    zeropad_bb_impl::zeropad_bb_impl(int L,int M)
      : gr::block("zeropad_bb",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1,1, sizeof(char))), d_M(M), d_L(L)
    {
	set_output_multiple(L+M);	
	}

    /*
     * Our virtual destructor.
     */
    zeropad_bb_impl::~zeropad_bb_impl()
    {
    }

    void
    zeropad_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
       ninput_items_required[0] = noutput_items-d_M*noutput_items/(d_L+d_M);
    }

    int
    zeropad_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];
	int l=0;
	for(int m=0;m<noutput_items/(d_M+d_L);m++){
		for(int j=0;j<d_L;j++)
		out[j+m*(d_L+d_M)]=in[l++];

		for(int k=0;k<d_M;k++)
		out[k+d_L+m*(d_L+d_M)]=0;
	}
      // printf("out %d\tin %d", noutput_items, (int)ninput_items[0]);
        consume_each (noutput_items-d_M*noutput_items/(d_L+d_M));
	//printf("zeropad no=%d\n", noutput_items);     
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

