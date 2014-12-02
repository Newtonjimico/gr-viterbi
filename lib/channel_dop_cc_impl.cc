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
#include <gnuradio/expj.h>
#include<math.h>
#include "channel_dop_cc_impl.h"

namespace gr {
  namespace viterbi {

    channel_dop_cc::sptr
    channel_dop_cc::make(long tot_bits)
    {
      return gnuradio::get_initial_sptr
        (new channel_dop_cc_impl(tot_bits));
    }

    
    channel_dop_cc_impl::channel_dop_cc_impl(long tot_bits)
      : gr::sync_block("channel_dop_cc",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(gr_complex)))
    {
    d_bit_number=0; //Initialising the bit count to 0.
    d_tot_bits_per_pass=tot_bits;
    }

  
    channel_dop_cc_impl::~channel_dop_cc_impl()
    {
    }
    
   double 	
   channel_dop_cc_impl::doppler_calculator(long bit_number)
   {
	/*This function calculates and returns the estimated Doppler in
	Hz. Doppler S-curve is approximated by the Logistic Function, appropriately
	shifted and scaled, to generate Doppler of +/- 10 kHz over 10 minutes.*/

	/*The argument bit_number is the number of the bit relative to
	  the entire pass.*/
	  
	  double t,shifted_logistic,dopp;

	  //Calculating corresponding time (in minutes.)
	  //This is done because the S-curve was approximated as
	  //a function of time (and no bits.)
	  t=((double)bit_number/19200)/60; //in minutes
	  double half_time; //Time for half pass (required for shifting the logistic function)
	  half_time=d_tot_bits_per_pass/19200/2/60; //in minutes
	  shifted_logistic=1/(1+exp(-t+half_time));  //Time shifted Logistic Function
	  dopp=(-shifted_logistic+0.5)*20e3; //Scaling appropriately
	  return dopp;
    }
    
    
    
    
    int
    channel_dop_cc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];
	  
	  double dopp;
	  gr_complex exponential;
	  
        for(int i=0;i<noutput_items;i++)
        {
        	dopp=doppler_calculator(d_bit_number);
        	exponential=gr_expj(dopp);
        	out[i]=in[i]*exponential;
        	d_bit_number++;
        }	

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

