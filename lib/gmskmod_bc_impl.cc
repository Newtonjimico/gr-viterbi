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
#include "gmskmod_bc_impl.h"
#include <complex>
#define PIBY2 1.5707963267948966

namespace gr {
  namespace viterbi {

    gmskmod_bc::sptr
    gmskmod_bc::make(int L, int M, float BT)
    {
      return gnuradio::get_initial_sptr
        (new gmskmod_bc_impl(L, M, BT));
    }

    /*
     * The private constructor
     */
    gmskmod_bc_impl::gmskmod_bc_impl(int L, int M, float BT)
      : gr::sync_interpolator("gmskmod_bc",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1,1, sizeof(gr_complex)), L), d_L(L),d_M(M),d_bt(BT)
    {
d_taps=phasepulse(d_L, d_M, d_bt);
set_history(d_M);
set_output_multiple(d_L);

	//for(int j=0;j<d_L*d_M;j++)
	//      printf("d_taps=%f\t%d\n", d_taps[j],d_L);
}

    /*
     * Our virtual destructor.
     */
    gmskmod_bc_impl::~gmskmod_bc_impl()
    {
    }

    int
    gmskmod_bc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];
  

	in+=(d_M-1);  // in[M]= a(n) and in[0]=a(n-(M-1))
  	  	double temp=0; static char oldestin=0;
	static	double prevph=0;
	double curph=0;
	for (int i = 0; i < noutput_items/d_L; i++){
		curph=prevph+PIBY2*oldestin; oldestin=in[i-(d_M-1)];// helped me
		for(int l=0;l<d_L;l++){
			for(int m=0;m<d_M;m++)
			temp+=d_taps[m*d_L+l]*in[i-m];
			if (curph>TWOPI)
		curph=curph-TWOPI;				
			else if(curph<TWOPI)
		curph=curph+TWOPI;			
			out[i*d_L+l]=gr_expj(PIBY2*temp+curph);
			temp=0; prevph=curph;
			//std::cout<<"\n"<<i*d_L+l<<"\t"<<"\t"<<out[i*d_L+l];
			}
		

		}

//for(int j=0;j<noutput_items;j++)
//std::cout<<"IN\t"<<(int)in[j/d_L]<<"OUT\t"<<out[j]<<std::endl;
//std::cout<<"gmskmod nout:"<<noutput_items<<std::endl;	
	return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

