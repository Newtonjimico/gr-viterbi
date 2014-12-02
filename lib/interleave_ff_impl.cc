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
#include "interleave_ff_impl.h"
#include<stdio.h>
namespace gr {
  namespace viterbi {

    interleave_ff::sptr
    interleave_ff::make(int r,int c)
    {
      return gnuradio::get_initial_sptr
        (new interleave_ff_impl(r, c));
    }

    /*
     * The private constructor
     */
    interleave_ff_impl::interleave_ff_impl(int r,int c)
      : gr::sync_block("interleave_ff",
              gr::io_signature::make(1,1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float))), d_r(r), d_c(c)
    {
	set_output_multiple(d_r*d_c);
	printf("rows x cols= %d\n", d_r*d_c);
	}

    /*
     * Our virtual destructor.
     */
    interleave_ff_impl::~interleave_ff_impl()
    {
    }

    int
    interleave_ff_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
       float *out = (float *) output_items[0];

	for(int j=0;j<noutput_items/(d_r*d_c);j++)
		for(int r=0;r<d_r;r++)
			for(int c=0;c<d_c;c++)
			out[d_r*c+r + j*d_r*d_c]=in[d_c*r+c + j*d_r*d_c];

	//for(int j=0;j<noutput_items;j++)	
	//printf("interleaver no=%d\n", noutput_items);
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

