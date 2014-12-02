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

#ifndef INCLUDED_VITERBI_ADDGSMTR26_BB_IMPL_H
#define INCLUDED_VITERBI_ADDGSMTR26_BB_IMPL_H

#include <viterbi/addgsmtr26_bb.h>

namespace gr {
  namespace viterbi {

    class addgsmtr26_bb_impl : public addgsmtr26_bb
    {
     private:
	char d_gsmtr[26];
     public:
	void set_gsmtr26(){
d_gsmtr[0]=0;
d_gsmtr[1]=0;
d_gsmtr[2]=1;
d_gsmtr[3]=0;
d_gsmtr[4]=0;
d_gsmtr[5]=1;
d_gsmtr[6]=0;
d_gsmtr[7]=1;
d_gsmtr[8]=1;
d_gsmtr[9]=1;
d_gsmtr[10]=0;
d_gsmtr[11]=0;
d_gsmtr[12]=0;
d_gsmtr[13]=0;
d_gsmtr[14]=1;
d_gsmtr[15]=0;
d_gsmtr[16]=0;
d_gsmtr[17]=0;
d_gsmtr[18]=1;
d_gsmtr[19]=0;
d_gsmtr[20]=0;
d_gsmtr[21]=1;
d_gsmtr[22]=0;
d_gsmtr[23]=1;
d_gsmtr[24]=1;
d_gsmtr[25]=1;
	};
      addgsmtr26_bb_impl();
      ~addgsmtr26_bb_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_ADDGSMTR26_BB_IMPL_H */

