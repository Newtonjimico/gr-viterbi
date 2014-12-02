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

#ifndef INCLUDED_VITERBI_VITSOVA_IMPL_H
#define INCLUDED_VITERBI_VITSOVA_IMPL_H

#include <viterbi/vitsova.h>
#include "functions.h"
namespace gr {
  namespace viterbi {

    class vitsova_impl : public vitsova
    {
     private:
      // Nothing to declare in this block.
     int d_N;
     const int const_N;
     float d_xk[3];
     float *sk;
     vitstate **d_all;		
// Not required in future	
	float d_bt;
	bool d_pam;
		
     public:
      vitsova_impl(int N, float BT, bool pam);
      ~vitsova_impl();
    // void set_sksize(int l){
	//sk= new float[l];	
	//};
     void set_d_allsize(){
	d_all=new vitstate*[4];
	for(int j=0;j<4;j++)
	d_all[j]=new vitstate[d_N+2]; //it should be d_N+2
	};


// Not required in future set_d_xk()


	void set_d_xk(){
			if(d_pam){
				if((int)(d_bt*10)==3){   // Matched to first pam pulse with BT
					d_xk[0]=0.994582383926362;
					d_xk[1]=- 0.483709259734129*0; //0 is 1j
					d_xk[2]=-0.0681519756110497;std::cout<<"\nPAM CIR ACF BT-0.3"<<std::endl;}
				else if((int)(d_bt*10)==5){
					d_xk[0]=0.999253349850080;
					d_xk[1]=- 0.317147269101309*0; //0 is 1j
					d_xk[2]=-0.0265782488484953;std::cout<<"\nPAM CIR ACF BT-0.5"<<std::endl;}
				else{
					d_xk[0]=1.0;
					d_xk[1]=0.0;
					d_xk[2]=0.0;  std::cout<<"\nGMSK CIR ACF BT-1K"<<std::endl; }	
				}
			else{
				if((int)(d_bt*10)==3){   // Matched to first pam pulse with BT
					d_xk[0]=0.994634300435843;
					d_xk[1]=-0.482785393968771*0; //0 is 1j
					d_xk[2]=-0.0678385820315331;std::cout<<"\nGMSK CIR ACF BT-0.3"<<std::endl;}

				else if((int)(d_bt*10)==5){
					d_xk[0]=0.999253385164867; 
					d_xk[1]=-0.317143833450410*0; //0 is 1j
					d_xk[2]=-0.0265776376819921; std::cout<<"\nGMSK CIR ACF BT-0.5"<<std::endl;}
				else{
					d_xk[0]=1.0;
					d_xk[1]=0.0;
					d_xk[2]=0.0;  std::cout<<"\nGMSK CIR ACF BT-1K"<<std::endl; }
				}
	};// end set_d_xk	










      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_VITSOVA_IMPL_H */

