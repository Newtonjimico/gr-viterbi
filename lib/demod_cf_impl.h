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

#ifndef INCLUDED_VITERBI_DEMOD_CF_IMPL_H
#define INCLUDED_VITERBI_DEMOD_CF_IMPL_H

#include <viterbi/demod_cf.h>
#include "functions.h"
namespace gr {
  namespace viterbi {

    class demod_cf_impl : public demod_cf
    {
     private:
      	int d_nslot;
	int d_N;
	int d_framesize;
	int d_dssize;
	int d_fcchsize;
	int d_schsize;
	int d_framemfcchsize;
      	int d_datapframe;
      	gr_complex d_cir[3];
	gr_complex drot[4];
	gr_complex* drin;
     	float d_xk[3];
	float *d_mfzk;//d_mfzk[32];
	vitstate **d_all;
	
//	LSE estimator variables
	int d_a[3][3];
	gr_complex d_b[3];
	gr_complex d_h[3];
	int A11,A12,A21,A22,C2; 
	gr_complex B1,B2,D2;
	float *d_sch;
	char *d_xin;
	char d_lag1, d_lag2;
	float d_alpha;
	
     public:
      demod_cf_impl(int nslot,int fcchsize,int schsize,int dssize);
      ~demod_cf_impl();
//1

//3
	void initialize(){
	d_framesize=d_fcchsize+d_schsize+d_dssize*d_nslot;
	d_framemfcchsize= d_framesize-d_fcchsize;
	d_mfzk=new float[d_dssize];	
	d_xin= new char[d_dssize];
	d_sch= new float[d_schsize];
	d_N=d_dssize-2;
	set_sch();
	set_d_allsize();
	std::cout<<"\tsch"<<d_schsize<<"\tfcch"<<d_fcchsize<<"\tds"<<d_dssize<<"\td_N"<<d_N
		<<"\tframe"<<d_framesize<<std::endl;
	};

//4	
	void set_drot(){
	drot[0]=1.0;
	drot[1]=-1j*1.0;
	drot[2]=-1.0;
	drot[3]=1j*1.0;	
	};

//
     void set_d_allsize(){
	d_all=new vitstate*[4];
	for(int j=0;j<4;j++)
	d_all[j]=new vitstate[d_dssize]; //it should be d_N+2 wher d_N is number of channel coded bits per data slot
	};

//   
    void matchfilterit(const gr_complex *in){ 
	for(int j=2;j<d_dssize;j++)
	d_mfzk[j-2]=-real(in[j]*conj(d_h[2])+in[j-1]*conj(d_h[1])+in[j-2]*conj(d_h[0]) );
	
	d_mfzk[d_N]=-real(in[d_N+1]*conj(d_h[1])+in[d_N]*conj(d_h[0]) );
	d_mfzk[d_N+1]=-real(in[d_N+1]*conj(d_h[0]));
	//d_mfzk[30]=-real(in[31]*conj(d_h[1])+in[30]*conj(d_h[0]) ); above two lines for dssize=32
	//d_mfzk[31]=-real(in[31]*conj(d_h[0]));
	};

      void set_sch(){
		d_sch[0]=0;
		d_sch[1]=0;
		d_sch[2]=0;
		d_sch[3]=0;
		d_sch[4]=1;
		d_sch[5]=0;
		d_sch[6]=1;
		d_sch[7]=0;
		d_sch[8]=0;
		d_sch[9]=0;
		d_sch[10]=1;
		d_sch[11]=1;
		d_sch[12]=1;
		d_sch[13]=1;
		d_sch[14]=1;
		d_sch[15]=1;
		d_sch[16]=0;
		d_sch[17]=1;
		d_sch[18]=0;
		d_sch[19]=0;
		d_sch[20]=0;
		d_sch[21]=1;
		d_sch[22]=1;
		d_sch[23]=0;
		d_sch[24]=1;
		d_sch[25]=0;
		d_sch[26]=1;
		d_sch[27]=1;
		d_sch[28]=0;
		d_sch[29]=1;
		d_sch[30]=0;
		d_sch[31]=0;
		for(int j=32;j<d_schsize;j++)
		d_sch[j]=0;
 		set_nrzsch();
};


	void set_nrzsch(){
		for(int j=0;j<d_schsize;j++)
		d_sch[j]= 1-2*d_sch[j];
				
	};


//


void cir_est(const gr_complex *in){
	cir_estcore(&d_sch[0], in);
	};


void cir_estcore(float *xbin, const gr_complex *in) 
{
	/*N is the size of r. Length of xbin array will be N but only first N-2 
	elements will be filled. The last two are 0s.*/
	
	//Ensuring that the last two elements are zero. 
	for(int i=0;i<d_N;i++)
		d_xin[i]=(xbin[i]>0)?1:-1;
	d_xin[d_N]= 1;
	d_xin[d_N+1]= 1;  // +1 for bit 0, -1 for bit 1
	/***********

	Calculating A matrix = X^H*X
	**********/
	//for(int i=0;i<32;i++)
	//std::cout<<"sch:"<<(int)d_xin[i]<<std::endl;
	/*Calculates autocorrelation at lag 1 and 2 of an 
	integer array 'x' of length 32. */
	d_lag1=0.0;
	d_lag2=0.0;
	for(int i=1;i<d_dssize;i++)
		d_lag1+=d_xin[i]*d_xin[i-1];
	for(int i=2;i<d_dssize;i++)
		d_lag2+=d_xin[i]*d_xin[i-2]; 

	
	d_a[0][0]=d_dssize;//If elements are in NRZ form, then diag elements=N.
	d_a[0][1]=d_xin[0]+d_lag1;
	d_a[0][2]=d_xin[0]+d_xin[1]+d_lag2;
	d_a[1][0]=d_a[0][1];
	d_a[1][1]=d_dssize;//diag element
	//A[1][2]=1-xnrz[0]+xcorrlag_ii(xnrz,N-1,1);
	d_a[1][2]=1+d_a[0][1]-d_xin[d_N+1]*d_xin[d_N]; //Optimised version of above
	d_a[2][0]=d_a[0][2];
	d_a[2][1]=d_a[1][2];
	d_a[2][2]=d_dssize;//diag element
	
	//for(int r=0;r<3;r++){
	//	std::cout<<std::endl;
	//	for(int c=0;c<3;c++)
	//	std::cout<<d_a[r][c]<<"\t";
	//	}
	
	/*The approach is to combine three possible for loops into one.
	From i=2 onwards, it can be combined.
	This means that i=0 and i=1 elements have to be manually computed.*/
	d_b[0]=(gr_complex)d_xin[0]*in[0]+(gr_complex)d_xin[1]*in[1];
	d_b[1]=in[0]+(gr_complex)d_xin[0]*in[1];
	d_b[2]=in[0]+in[1];
	for(int i=2;i<d_dssize;i++)
		{
			d_b[0]+=(gr_complex)d_xin[i]*in[i];
			d_b[1]+=(gr_complex)d_xin[i-1]*in[i];
			d_b[2]+=(gr_complex)d_xin[i-2]*in[i];
		}
	
	gausselim();
	
};



void gausselim() 
{
	/*Solves Ah=b by Gauss-Jordan Elimination*/

	
	//Gaussian elimination
	B1=d_b[1]*(gr_complex)d_a[0][0]-d_b[0]*(gr_complex)d_a[1][0];
	B2=d_b[2]*(gr_complex)d_a[0][0]-d_b[0]*(gr_complex)d_a[2][0];
	A11=d_a[1][1]*d_a[0][0]-d_a[0][1]*d_a[1][0];
	A12=d_a[1][2]*d_a[0][0]-d_a[0][2]*d_a[1][0];
	A21=d_a[2][1]*d_a[0][0]-d_a[0][1]*d_a[2][0];
	A22=d_a[2][2]*d_a[0][0]-d_a[0][2]*d_a[2][0];
	C2=A22*A11-A12*A21;  // 3rd row pivot
	D2=B2*(gr_complex)A11-B1*(gr_complex)A21;	
	
	/*cout<<(int)A11<<' '<<(int)A22<<endl;//DEBUG*/
	//back substitution
	d_h[2]=D2/(gr_complex)C2;
	d_h[1]=(B1-d_h[2]*(gr_complex)A12)/(gr_complex)A11;
	d_h[0]=(d_b[0]-(gr_complex)d_a[0][1]*d_h[1]-(gr_complex)d_a[0][2]*d_h[2])/(gr_complex)d_a[0][0];
	//gr_complex temp;
	get_xk();
	//d_alpha= d_xk[0];
		//    for(int q=0;q<3;q++)
		 //	std::cout<<"\thest"<<q<<d_h[q]<<"a="<<d_alpha<<std::endl;
		
	//temp=d_h[0];
	//d_h[0]=d_h[2];
	//d_h[2]=temp;    
}			


	void get_xk(){
	d_xk[0]=real(d_h[0]*conj(d_h[0])+d_h[1]*conj(d_h[1])+d_h[2]*conj(d_h[2]));
	d_xk[1]=real(d_h[0]*conj(d_h[1])+d_h[1]*conj(d_h[2]));
	d_xk[2]=real(d_h[0]*conj(d_h[2]));
		//for(int q=0;q<3;q++)
		// std::cout<<"\txk"<<d_xk[q]<<std::endl;
		
	};


      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr




#endif /* INCLUDED_VITERBI_DEMOD_CF_IMPL_H */

