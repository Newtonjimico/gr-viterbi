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
#include "hist_test_impl.h"

namespace gr {
  namespace viterbi {

    hist_test::sptr
    hist_test::make(int L)
    {
      return gnuradio::get_initial_sptr
        (new hist_test_impl(L));
    }

    /*
     * The private constructor
     */
    hist_test_impl::hist_test_impl(int L)
      : gr::sync_block("hist_test",
              gr::io_signature::make(1,1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float))),d_L(L)
    {
	set_history(d_L);	
	}

    /*
     * Our virtual destructor.
     */
    hist_test_impl::~hist_test_impl()
    {
    }

    int
    hist_test_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
	in+=(d_L-1);
	for(int j=0;j<noutput_items;j++)
	{
	out[j]=in[j];
	std::cout<<"\n"<<(float)out[j]<<"\t"<<j;//(int)in[j-d_L+1];
		}
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

