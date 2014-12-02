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

#ifndef INCLUDED_VITERBI_GMSKMF_CF_IMPL_H
#define INCLUDED_VITERBI_GMSKMF_CF_IMPL_H
#include <complex>
#include <viterbi/gmskmf_cf.h>

namespace gr {
  namespace viterbi {

    class gmskmf_cf_impl : public gmskmf_cf
    {
     private:
      float d_bt;
	float d_xk[3];
	gr_complex derot[4];
	gr_complex mf[3];
	bool d_pam;
     public:
      gmskmf_cf_impl(float bt,bool pam);
      ~gmskmf_cf_impl();
	void set_derot(){
	derot[0]=1.0;
	derot[1]=-1j;
	derot[2]=-1.0;
	derot[3]=1j;
	};

	void set_mf(){
			if(d_pam){
				if((int)(d_bt*10)==3){   // Matched to first pam pulse with BT
					mf[0]=-0.260458407488668;
					mf[1]=0.926799404603163*1j;
					mf[2]=0.260458407488668;std::cout<<"\nPAM MF BT-0.3"<<std::endl;}
				else if((int)(d_bt*10)==5){
					mf[0]=-0.163026493803897;
					mf[1]=0.972675747513467*1j;
					mf[2]=0.163026493803897;std::cout<<"\nPAM MF BT-0.5"<<std::endl;}
				else{
					mf[0]=0;
					mf[1]=1j;
					mf[2]=0;  std::cout<<"\nGMSK MF BT-1K"<<std::endl; }	
				}
			else{
				if((int)(d_bt*10)==3){   // Matched to first pam pulse with BT
					mf[0]=-0.261765386310982;
					mf[1]= 0.926432104385888*1j;
					mf[2]=0.260355185120174 ;std::cout<<"\nGMSK MF BT-0.3"<<std::endl;}

				else if((int)(d_bt*10)==5){
					mf[0]=-0.163030351041787; 
					mf[1]=0.972675101016451*1j;
					mf[2]=0.163026385446983;std::cout<<"\nGMSK MF BT-0.5"<<std::endl;}
				else{
					mf[0]=0;
					mf[1]=1j;
					mf[2]=0;  std::cout<<"\nGMSK MF BT-1K"<<std::endl; }
				}
	};// end set_mf	
	
      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_GMSKMF_CF_IMPL_H */

