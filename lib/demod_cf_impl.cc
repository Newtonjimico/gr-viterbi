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
#include "demod_cf_impl.h"
#include "functions1.c"
//#define nds 32
namespace gr {
  namespace viterbi {

    demod_cf::sptr
    demod_cf::make(int nslot,int fcchsize,int schsize,int dssize)
    {
      return gnuradio::get_initial_sptr
        (new demod_cf_impl(nslot, fcchsize,schsize,dssize));
    }

    /*
     * The private constructor
     */
    demod_cf_impl::demod_cf_impl(int nslot,int fcchsize,int schsize,int dssize)
      : gr::block("demod_cf",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(float))), d_nslot(nslot),d_fcchsize(fcchsize),d_schsize(schsize),d_dssize(dssize), d_datapframe((dssize-2)*nslot)
    {
	initialize();  // framesize-fcchsize
	set_output_multiple(d_datapframe);
	
	std::cout<<"demodomultiple"<<d_datapframe<<std::endl;
}

    /*
     * Our virtual destructor.
     */
    demod_cf_impl::~demod_cf_impl()
    {
    }

    void
    demod_cf_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
ninput_items_required[0] = noutput_items/d_datapframe*d_framemfcchsize;
    }

    int
    demod_cf_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        float *out = (float *) output_items[0];
	//std::cout<<"demodnout"<<noutput_items<<std::endl;
	for(int j=0;j<noutput_items/d_datapframe;j++){
		cir_est(&in[j*d_framemfcchsize]);// cir using sch
		//for(int m=0;m<32;m++)
		//std::cout<<in[m]<<std::endl;
		for(int k=0;k<d_nslot;k++){
			matchfilterit(&in[k*d_dssize+d_schsize+j*d_framemfcchsize]);
			vitmlsesova(&d_mfzk[0],&out[k*d_N+j*(d_nslot*d_N)], d_N, d_xk, d_all);
			cir_estcore(&out[k*d_N+j*(d_nslot*d_N)],&in[k*d_dssize+d_schsize+j*d_framemfcchsize]);
			//for(int i=0;i<30;i++){
				//out[i+j*d_datapframe+k*30]=imag(in[i+j*d_framemfcchsize+(k+1)*32]);
			//	std::cout<<out[i+k*d_N+j*(d_nslot*d_N)]<<std::endl;
			//}
		//matchfilter_it();
		//vitmlsesova(&in[j*(d_N+2)],&out[j*d_N], d_N, d_xk, d_all);
		
		}
	
	}
	

	
        consume_each (noutput_items/d_datapframe*d_framemfcchsize);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

