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

#ifndef INCLUDED_VITERBI_CONVDEC_IMPL_H
#define INCLUDED_VITERBI_CONVDEC_IMPL_H

#include <viterbi/convdec.h>
#ifndef fcci
#define fcci
#include "functions_cc.h"
#include "functions_cc.c"
#endif

namespace gr {
  namespace viterbi {

    class convdec_impl : public convdec
    {
     private:
      // Nothing to declare in this block.
	int d_M;
	int d_N;
	trellis  d_t;
	vitstatecd **d_all;
	vitbmsps *d_bmsps;

     public:
      convdec_impl(int N, int M, int g1,int g2);
      ~convdec_impl();

	void set_d_all(trellis t, int N){
		d_all= new vitstatecd*[t.numStates];
		for(int j=0;j<t.numStates;j++)
			d_all[j]=new vitstatecd[N];
		};


	void set_d_bmsps(trellis t){
		d_bmsps=new vitbmsps[t.numStates];
		};

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);


      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_CONVDEC_IMPL_H */

