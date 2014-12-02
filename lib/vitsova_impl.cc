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
#include "vitsova_impl.h"
#include "functions.c"
namespace gr {
  namespace viterbi {

    vitsova::sptr
    vitsova::make(int N, float BT, bool pam)
    {
      return gnuradio::get_initial_sptr
        (new vitsova_impl(N, BT, pam));
    }

    /*
     * The private constructor
     */
    vitsova_impl::vitsova_impl(int N, float BT, bool pam)
      : gr::block("vitsova",
              gr::io_signature::make(1,1, sizeof(float)),
              gr::io_signature::make(1,1, sizeof(float))),d_N(N),const_N(N), d_bt(BT), d_pam(pam)
    {
	set_output_multiple(d_N);
	set_d_xk();
	//float ck[N];
	//ck[0]=3.0;
	//sk=&ck[0];
	//set_sksize(N);
	set_d_allsize();
	//sk[3]=2.0;
	//d_all[3][30].delta=5.0;
	/*
	vitstate s1[const_N];
	vitstate s2[const_N];
	vitstate s3[const_N];
	vitstate s0[const_N];
	d_all=(vitstate **)malloc(4*sizeof(vitstate*));
	//if all<1
	//exit(0);
	
	d_all[0]=&s0[0];
	d_all[1]=&s1[0];
	d_all[2]=&s2[0];
	d_all[3]=&s3[0];*/
	}

    /*
     * Our virtual destructor.
     */
    vitsova_impl::~vitsova_impl()
    {
    }

    void
    vitsova_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = (noutput_items/d_N)*(d_N+2);// noutput_items+2;
    }

    int
    vitsova_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float*) output_items[0];	
	//*
	for(int j=0;j<noutput_items/d_N;j++)
        vitmlsesova(&in[j*(d_N+2)],&out[j*d_N], d_N, d_xk, d_all);
	//std::cout<<noutput_items<<"\t"<<(int)ninput_items[0]<<std::endl;
	//for(int j=0;j<d_N;j++)
	//out[j]=d_all[3][30].delta*in[j];
  	consume_each ((noutput_items/d_N)*(d_N+2));
        return noutput_items; //*/
	
	//vitmlsesova(in,out, d_N, d_xk, d_all);
	//consume_each(d_N+2);
	//return d_N;


    }

  } /* namespace viterbi */
} /* namespace gr */





