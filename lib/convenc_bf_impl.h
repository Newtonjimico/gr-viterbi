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

#ifndef INCLUDED_VITERBI_CONVENC_BF_IMPL_H
#define INCLUDED_VITERBI_CONVENC_BF_IMPL_H

#include <viterbi/convenc_bf.h>


namespace gr {
  namespace viterbi {

typedef struct trel{
	char K;
	char G[2];
	char numStates;
	char numhStates;
	char **outputg1;
	char **outputg2;
	char **noutputg1;
	char **noutputg2;

} trellis;

    class convenc_bf_impl : public convenc_bf
    {
     private:
      	int d_K;
  	trellis d_t;

     public:
      convenc_bf_impl(int K, int g1, int g2);
      ~convenc_bf_impl();
     void set_trellis(trellis *t,int K, int G1,int G2, int Nrzrule);

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };




void convenc_bf_impl::set_trellis(trellis *t,int K, int G1,int G2, int Nrzrule){
	t->K=K;
	t->G[0]=G1;
	t->G[1]=G2;
	t->numhStates=1;
	for(int j=0;j<K-2;j++)
	t->numhStates*=2;
	t->numStates=t->numhStates*2;

	char **ptrg1;
	ptrg1=(char**) malloc(2*sizeof(char*));
	ptrg1[0]=(char*) malloc(t->numStates*sizeof(char));
	ptrg1[1]=(char*) malloc(t->numStates*sizeof(char));

	char **ptrg2;
	ptrg2=(char**) malloc(2*sizeof(char*));
	ptrg2[0]=(char*) malloc(t->numStates*sizeof(char));
	ptrg2[1]=(char*) malloc(t->numStates*sizeof(char));

	char **nptrg1;
	nptrg1=(char**) malloc(2*sizeof(char*));
	nptrg1[0]=(char*) malloc(t->numStates*sizeof(char));
	nptrg1[1]=(char*) malloc(t->numStates*sizeof(char));

	char **nptrg2;
	nptrg2=(char**) malloc(2*sizeof(char*));
	nptrg2[0]=(char*) malloc(t->numStates*sizeof(char));
	nptrg2[1]=(char*) malloc(t->numStates*sizeof(char));


	char dec10,g10,dec11,g11,dec20,g20,dec21,g21;

		for(char k=0; k<t->numStates;k++){
			dec10=0;
			dec11=0;
			dec20=0;
			dec21=0;
			g10=G1 & (k<<1);
			g11=g10+1;
			g20=G2 & (k<<1);
			g21=g20+1;
			for(int m=0;m<K;m++){
				dec10+= (1 & (g10>>m));
				dec11+= (1 & (g11>>m));//printf("%d", (1 & (g11>>m)));
				dec20+= (1 & (g20>>m));
				dec21+= (1 & (g21>>m));
						} //printf("\tg11 %d  \n",g11);
			//printf("\n%d\t%d\t%d\t%d",dec10,dec11,dec20,dec21);
			ptrg1[0][k]=Nrzrule*(2*( dec10 & 1)-1);
			ptrg1[1][k]=Nrzrule*(2*( dec11 & 1)-1);
			ptrg2[0][k]=Nrzrule*(2*( dec20 & 1)-1);
			ptrg2[1][k]=Nrzrule*(2*( dec21 & 1)-1);
			//printf("\n %d\t%d", ptr[0][k],ptr[1][k]);
			}

	t->outputg1=ptrg1;
	t->outputg2=ptrg2;
	t->noutputg1=nptrg1;
	t->noutputg2=nptrg2;


		for(char j=0;j<t->numStates;j++){
			t->noutputg1[j>>(K-2)][(j<<1) & (t->numStates-1)]=t->outputg1[0][j];
			t->noutputg1[j>>(K-2)][1+((j<<1) & (t->numStates-1))]=t->outputg1[1][j];
			t->noutputg2[j>>(K-2)][(j<<1) & (t->numStates-1)]=t->outputg2[0][j];
			t->noutputg2[j>>(K-2)][1+((j<<1) & (t->numStates-1))]=t->outputg2[1][j];
		}

	}





















  } // namespace viterbi
} // namespace gr











#endif /* INCLUDED_VITERBI_CONVENC_BF_IMPL_H */

