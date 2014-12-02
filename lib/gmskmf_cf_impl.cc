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
#include "gmskmf_cf_impl.h"

namespace gr {
  namespace viterbi {

    gmskmf_cf::sptr
    gmskmf_cf::make(float bt, bool pam)
    {
      return gnuradio::get_initial_sptr
        (new gmskmf_cf_impl(bt, pam));
    }

    /*
     * The private constructor
     */
    gmskmf_cf_impl::gmskmf_cf_impl(float bt, bool pam)
      : gr::sync_block("gmskmf_cf",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(float))), d_bt(bt), d_pam(pam)
    {
	set_derot();	
	set_history(3);
	set_output_multiple(4);
	set_mf();
	}

    /*
     * Our virtual destructor.
     */
    gmskmf_cf_impl::~gmskmf_cf_impl()
    {
    }

    int
    gmskmf_cf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
       float *out = (float *) output_items[0];
	static gr_complex in1=0,in2=0;
	double temp=0;
	in+=2;
	for(int j=0; j<noutput_items;j++){
		out[j]=std::real( in[j]*derot[(j+2)%4]*mf[0]+in[j-1]*derot[(j+1)%4]*mf[1]+in[j-2]*derot[j%4]*mf[2]);
		//std::cout<<"o/p\t"<<out[j]<<"\t"<<j<<"\t\t"<<in[j]<<std::endl;
				}
		/*for(int j=0; j<noutput_items;j++){
		out[j]=std::real( in[j]*derot[j%4]*mf[0]+in1*derot[(j+3)%4]*mf[1]+in2*derot[(j+2)%4]*mf[2]);
		in2=in1;
		in1=in[j];
		//std::cout<<"o/p\t"<<out[j]<<"\t"<<j<<"\t\t"<<in[j]<<"\t"<<noutput_items<<std::endl;
		}*/
	



        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

