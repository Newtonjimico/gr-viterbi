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

#ifndef INCLUDED_VITERBI_GMSKMOD_BC_IMPL_H
#define INCLUDED_VITERBI_GMSKMOD_BC_IMPL_H

#include <viterbi/gmskmod_bc.h>
#include "func.cc"
#include <vector>
namespace gr {
  namespace viterbi {

    class gmskmod_bc_impl : public gmskmod_bc
    {
     private:
	int d_L;
	int d_M;
	float d_bt;
	float d_an[4];
		std::vector<float> d_taps;
     public:
      gmskmod_bc_impl(int L, int M, float BT);
      ~gmskmod_bc_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_GMSKMOD_BC_IMPL_H */
