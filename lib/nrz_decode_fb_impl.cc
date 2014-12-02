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
#include "nrz_decode_fb_impl.h"

namespace gr {
  namespace viterbi {

    nrz_decode_fb::sptr
    nrz_decode_fb::make(int set0)
    {
      return gnuradio::get_initial_sptr
        (new nrz_decode_fb_impl(set0));
    }

    /*
     * The private constructor
     */
    nrz_decode_fb_impl::nrz_decode_fb_impl(int set0)
      : gr::sync_block("nrz_decode_fb",
              gr::io_signature::make(1,1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(char))), d_set0(set0)
    {
		std::cout<<"NRZ DSET"<< d_set0 <<std::endl;
}

    /*
     * Our virtual destructor.
     */
    nrz_decode_fb_impl::~nrz_decode_fb_impl()
    {
    }

    int
    nrz_decode_fb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        char *out = (char *) output_items[0];


	if(d_set0 < 0){
		for(int j=0;j<noutput_items;j++){
		if(in[j]<0)
		out[j]=0;
		else
		out[j]=1; 
		//std::cout<<(int)out[j]<<std::endl;
		}
		}
	else{
		for(int j=0;j<noutput_items;j++){
		if(in[j]>0)
		out[j]=0;
		else
		out[j]=1;
		//std::cout<<(int)out[j]<<std::endl;
		}
		}


	//for(int j=0;j<noutput_items;j++)
	//std::cout<<j<<"\t"<<(int)out[j]<<d_set0<<std::endl;
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

