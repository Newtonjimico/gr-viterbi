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
#include "addfirstN_bb_impl.h"

namespace gr {
  namespace viterbi {

    addfirstN_bb::sptr
    addfirstN_bb::make(int N)
    {
      return gnuradio::get_initial_sptr
        (new addfirstN_bb_impl(N));
    }

    /*
     * The private constructor
     */
    addfirstN_bb_impl::addfirstN_bb_impl(int N)
      : gr::block("addfirstN_bb",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1,1, sizeof(char))), d_N(N)
    {
	set_output_multiple(d_N);
	}

    /*
     * Our virtual destructor.
     */
    addfirstN_bb_impl::~addfirstN_bb_impl()
    {
    }

    void
    addfirstN_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    addfirstN_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];
	static char first=0;
	if(first==0){
		first=1;
		for(int j=0;j<d_N;j++)
		out[j]=0;
		consume_each(0);
		return d_N;
		}	
       	else{
		for(int j=0;j<noutput_items;j++)
		*out++=*in++;
		
        consume_each (noutput_items);
        return noutput_items;
	}
    }

  } /* namespace viterbi */
} /* namespace gr */

