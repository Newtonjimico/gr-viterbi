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
#include <stdio.h>
#include <gnuradio/io_signature.h>
#include "nrz_encoder_impl.h"

namespace gr {
  namespace viterbi {

    nrz_encoder::sptr
    nrz_encoder::make(bool diff, int a)
    {
      return gnuradio::get_initial_sptr
        (new nrz_encoder_impl(diff, a));
    }

    /*
     * The private constructor
     */
    nrz_encoder_impl::nrz_encoder_impl(bool diff, int a)
      : gr::sync_block("nrz_encoder",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))), d_bool(diff), d_a(a)
    {
	//if(d_bool)
//	set_history(1);
	
}

    /*
     * Our virtual destructor.
     */
    nrz_encoder_impl::~nrz_encoder_impl()
    {
    }

    int
    nrz_encoder_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];
	if(d_bool){ 
		static char previn=0;
		for(int j=0;j<noutput_items;j++){
			out[j]=1- (((in[j]+previn)<<1)&2);
			previn=in[j];
			}
		}
	else
	for(int j=0;j<noutput_items;j++)
		out[j]=d_a*(1-(in[j]<<1));
	//printf("encoder CALLED\n");
	//for(int j=0;j<noutput_items;j++)
	//printf("\t\t\tin=%d\tou=%d\t%d\t\tno=%d\n", in[j], out[j],(int) d_bool, noutput_items);
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

