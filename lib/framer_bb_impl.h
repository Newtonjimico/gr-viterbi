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

#ifndef INCLUDED_VITERBI_FRAMER_BB_IMPL_H
#define INCLUDED_VITERBI_FRAMER_BB_IMPL_H

#include <viterbi/framer_bb.h>

namespace gr {
  namespace viterbi {

    class framer_bb_impl : public framer_bb
    {
     private:
      int d_nslot;
      char d_N;
      char d_dssize;
      char d_fcchsize;
      char *d_sch; /// array
      int d_framesize;
      int d_datapframe;
      int d_schsize;
      int d_sframesize;
      int d_fcount;
      char *d_schx;
     public:
      framer_bb_impl(int nslot, int fcchsize, int schsize, int dssize, int isr);
      ~framer_bb_impl();
	void initialize(){
	d_sch=new char[d_schsize];
	d_schx=new char[64];
	set_sch();
	set_schx();
	d_N=d_dssize-2;
	d_framesize= d_dssize*d_nslot+d_schsize+d_fcchsize;
	d_sframesize=d_fcchsize*3+2*64;
	};


      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);
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
};

void set_schx(){		
		d_schx[0]=0;
		d_schx[1]=0;
		d_schx[2]=0;
		d_schx[3]=0;
		d_schx[4]=0;
		d_schx[5]=0;
		d_schx[6]=0;
		d_schx[7]=0;
		d_schx[8]=0;
		d_schx[9]=0;
		d_schx[10]=0;
		d_schx[11]=0;
		d_schx[12]=0;
		d_schx[13]=0;
		d_schx[14]=0;
		d_schx[15]=0;
		d_schx[16]=0;
		d_schx[17]=0;
		d_schx[18]=0;
		d_schx[19]=0;
		d_schx[20]=0;
		d_schx[21]=0;
		d_schx[22]=0;
		d_schx[23]=0;
		d_schx[24]=0;
		d_schx[25]=0;
		d_schx[26]=0;
		d_schx[27]=0;
		d_schx[28]=0;
		d_schx[29]=0;
		d_schx[30]=0;
		d_schx[31]=0;
		d_schx[32]=0;
		d_schx[33]=0;
		d_schx[34]=0;
		d_schx[35]=0;
		d_schx[36]=0;
		d_schx[37]=0;
		d_schx[38]=0;
		d_schx[39]=0;
		d_schx[40]=0;
		d_schx[41]=0;
		d_schx[42]=0;
		d_schx[43]=0;
		d_schx[44]=0;
		d_schx[45]=0;
		d_schx[46]=0;
		d_schx[47]=0;
		d_schx[48]=0;
		d_schx[49]=0;
		d_schx[50]=0;
		d_schx[51]=0;
		d_schx[52]=0;
		d_schx[53]=0;
		d_schx[54]=0;
		d_schx[55]=0;
		d_schx[56]=0;
		d_schx[57]=0;
		d_schx[58]=0;
		d_schx[59]=0;
		d_schx[60]=0;
		d_schx[61]=0;		
		d_schx[62]=0;
		d_schx[63]=0;
}



void fill_fcch(char *out){
	for(int j=0;j<d_fcchsize;j++)
	out[j]=0;
	};
void fill_sch(char *out){
	for(int j=0;j<d_schsize;j++)
	out[j]=d_sch[j];
	};
	
void fill_data(const char *in, char *out){
	for(int k=0;k<d_nslot;k++){
		for(int j=0;j<d_N;j++)
		out[k*d_dssize+j]=in[j+k*d_N];
		out[k*d_dssize+d_N]=0;
		out[k*d_dssize+d_N+1]=0;		
		}	
	};


void fill_schx(char *out){
	for(int j=0;j<64;j++)
	out[j]=d_schx[j];
	};

void insert_sframe(char *out){
fill_fcch(out[0*d_fcchsize]);
fill_fcch(out[1*d_fcchsize]);
fill_sch64(out[2*d_fcchsize]);
fill_sch64(out[2*d_fcchsize+64]);
fill_fcch(out[2*d_fcchsize+64+64]);
//if(d_sframesize!= (3*d_fcchsize+64+64))
//	exit (-1);
};




      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_FRAMER_BB_IMPL_H */

