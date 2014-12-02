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

#ifndef INCLUDED_VITERBI_SYNC_CC_IMPL_H
#define INCLUDED_VITERBI_SYNC_CC_IMPL_H

#include <viterbi/sync_cc.h>
#include "lut.h"
#include <gnuradio/random.h>
#include <gnuradio/expj.h>
#define M_TWOPI 6.28318530717958647692
namespace gr {
  namespace viterbi {

    class sync_cc_impl : public sync_cc
    {
     private:
       	int d_nslot;
	int d_framesize;
	int d_framemfcchsize;
	int d_fcchsize;
	int d_schsize;
	int d_dssize;
	float d_fmax;
	float d_freq;

	int d_syncindex;
	int d_pindex;
	float peak;
	float tpeak;
	gr_complex *d_sch;
	gr_complex drot[4];
	gr_complex xsch[9];
// For frequency estimator
	
	gr_complex *drin;
	gr_complex **wn;
	gr_complexd *fftxk;
	
	char d_pk;
	double a1;
	double a2;
	double ci1;
	double ci2;
	double ci3;
	double temp1;
//	double temp2= d_wo_new 
	double temp3;
	double tpibyfcch;
	float del1;
	float del2;
	float del;
	float cdel;
	float d_m; 
			

	gr_complex xcorrL1;
	gr_complex xcorrL2;
	double d_randwo;
	



	double d_wo_new;
	double d_wo_old;
	double d_wo_avg;


	float d_r;
	float d_std;
	double rand;
	int d_seed;
	random d_rng;

     public:
      sync_cc_impl(int nslot,int fcchsize,int schsize,int dssize);
      ~sync_cc_impl();
	

	void initialize(){   // 		initialize class variables and functions
		d_sch=new gr_complex[d_schsize];
		drin=new gr_complex[d_fcchsize]; // derorated innput sequence for FCCH f_offset estimation
		tpibyfcch=M_TWOPI/d_fcchsize;
		initfft();
	
		set_drot();			// d_drot[4]={1,-1j,-1,1j}
		set_sch();			// load gr_complex d_sch[32] with 32-bit training seq 0's n 1's
		set_nrzsch();	
		set_rotnrz_sch();		// encode d_sch into nrz +/- 1s, and rotate it with -pi/2 shift per bit 
		d_framesize=d_fcchsize+d_schsize+d_dssize*d_nslot;	
		d_framemfcchsize=d_framesize-d_fcchsize;// d_framemfcchsize=d_framesize-d_fcchsize
		d_syncindex=0;			// incremental index of global peak per frame
		d_wo_old=0;
		d_wo_new=0;
		};


	void initfft(){  // Guided search ALGO, but search will be done across five bins where peak is expected  
	fftxk=new gr_complexd[5];
	wn=new gr_complex*[5];
	for(int k=0;k<5;k++)
	wn[k]=new gr_complex[d_fcchsize];
		for(int k=0;k<5;k++)	
			for(int n=0;n<d_fcchsize;n++)
			wn[k][n]=gr_expj(-tpibyfcch*k*n);
	};


	void set_drot(){ // derotate vector at symbol spaced
		drot[0]=1.0;
		drot[1]=-1j*1.0;
		drot[2]=-1.0;
		drot[3]=1j*1.0;	
	};

	void set_nrzsch(){ // Note: set 1 as -1 and 0 as +1 
		for(int j=0;j<d_schsize;j++)
		d_sch[j]=1-2*real(d_sch[j]);	
	};

//  rotate nrz'ed sch seq 
	void set_rotnrz_sch(){
		for(int j=0;j<d_schsize;j++){
		d_sch[j]=drot[j%4]*d_sch[j];
		}
	};


	void get_freqsync(const gr_complex *in){
	// assume uniform random frequency around 1 bin width = (19200/fcchsize) Hz
	//int randi=199;

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/
/*********d_randwo should increase linearly with time to mimic Doppler pattern ***********/
/*****************************************************************************************/
	d_randwo=(((711 & 1023)/1024.0)-0.5)*tpibyfcch*0+2.97555*tpibyfcch;// 
/*****************************************************************************************/
/*****************************************************************************************//*****************************************************************************************/
/*****************************************************************************************//*****************************************************************************************/
/*****************************************************************************************/

	for(int j=0;j<d_fcchsize;j++)
		//drin[j]=gr_expj(d_randwo*j)*in[j]*drot[j%4];  // d_randwo to be estimated
		drin[j]=in[j]*drot[j%4];  // d_randwo to be estimated
		peak=0;
		for(int k=0;k<5;k++){ 
			fftxk[k]=0.0;
			for(int n=0;n<d_fcchsize;n++)
				fftxk[k]+=drin[n]*wn[k][n];  // FFT computation for only 5bins
			tpeak=abs(fftxk[k]);
			//std::cout<<"\n\tpeak"<<tpeak<<"\t"<<k<<std::endl;
			if (tpeak > peak){
				peak=tpeak;
				d_pk=k;  // got peak index 
			}
		}	
// Guided search begins
		a1=real(fftxk[d_pk-1]/fftxk[d_pk]);
		a2=real(fftxk[d_pk+1]/fftxk[d_pk]);
	//std::cout<<"\n\ta1"<<a1<<"\ta2"<<a2<<std::endl;
	del1=a1/(1-a1);
	del2=-a2/(1-a2);
	del=del1;
	//std::cout<<"\n\td1"<<del1<<"\td2"<<del2<<std::endl;
	if ((del1>0) && (del2>0))
		del=del2; 
	d_m=d_pk+del; 
	cdel=0.5;
	fftxk[1]=0;fftxk[2]=0;fftxk[0]=0;// resuse for I1, I2, I3
	 temp1=tpibyfcch*(d_m-cdel);
	 d_wo_new=tpibyfcch*d_m;

	 temp3=tpibyfcch*(d_m+cdel);
	for(int n=0;n<d_fcchsize;n++){
		fftxk[0]+=drin[n]*gr_expj(-temp1*n); // i1
		fftxk[1]+=drin[n]*gr_expj(-d_wo_new*n); // i2
		fftxk[2]+=drin[n]*gr_expj(-temp3*n); // i3		
		}
	ci1=real(fftxk[0]*conj(fftxk[0])); //I1
	ci2=real(fftxk[1]*conj(fftxk[1])); //I2
	ci3=real(fftxk[2]*conj(fftxk[2])); //I3
	//std::cout<<"\t\t\tI2="<<ci2<<std::endl;
          	for(int q=0;q<6;q++){ // hard coded for Q=6 iteration
		     cdel=cdel/2.0;
		  	if(ci3>ci1){
				ci1=ci2;
				d_m=d_m+cdel;
			}
			else{
				ci3=ci2;
				d_m=d_m-cdel;
			}
		    d_wo_new=tpibyfcch*d_m;
		    fftxk[1]=0;
			for(int n=0;n<d_fcchsize;n++) // UPDATE I2
				fftxk[1]+=drin[n]*gr_expj(-d_wo_new*n);		
		    ci2=real(fftxk[1]*conj(fftxk[1]));
		}
	
	d_wo_new=tpibyfcch*d_m;
	// End of Guided search d_wo_new is new freq estimation 

	//std::cout<<d_wo_new<<"IN\two="<<d_randwo<<"\ttpibyfcch="<<tpibyfcch<<"\tdm="<<d_m<<std::endl;
	};

	

	
// 	Timing synchronization
//      get sync peak, +/- 4 lags from expected peak index
	void synchronize(const gr_complex *in){
		// set xsch array to 0
		for(int k=0;k<9;k++)
			xsch[k]=0;
		// find acf	
		for(int k=-4;k<5;k++)
			for(int t=0;t<d_schsize;t++)
			xsch[k+4]+=d_sch[t]*in[t+k];
		peak=0;
		for(int k=0;k<9;k++){
			tpeak=abs(xsch[k]); 
			if(tpeak>peak){
			peak=tpeak;
			d_pindex=k-4;
			}
		//std::cout<<"peak:"<<tpeak<<"\tind:"<<k-4<<std::endl;
		}
		//std::cout<<"\n\n\ngpeak:"<<peak<<"\tind:"<<d_pindex<<std::endl;
	};	

	void get_timesync(const gr_complex *in, gr_complex *out){ //&in[j*d_framesize+d_syncindex], &out[j*(d_framemfcchsize)]);  //assuming a prior frequency sync

d_wo_avg=0.5*(d_wo_old+d_wo_new); // Averaging two frequency estimatoins

		//8.6332    7.6943    6.8576    6.1118    5.4472    4.8548    4.3268 // N=64 crlb in Hz
		// 6.3536    5.6626    5.0468    4.4980    4.0088  //N=80 crlb in Hz
		synchronize(in);  // posteriori timing sync correction, corrected index after the call will be in d_pindex
//std::cout<<d_wo_new<<"OUT\two="<<d_randwo<<"\ttpibyfcch="<<tpibyfcch<<"\tdm="<<d_m<<std::endl;
d_freq=(d_wo_avg-d_randwo)*19200/M_TWOPI;
if (d_freq>d_fmax)
d_fmax=d_freq;
//std::cout<<d_fmax<<std::endl;

			for(int j=0;j<d_framemfcchsize;j++)  // derorate and send sch+tch part to demod block
				out[j]=gr_expj(M_TWOPI*8/19200.0*j)*in[j+d_pindex-1]*drot[j%4]; 

		d_syncindex+=d_pindex;
		d_wo_old=d_wo_new;
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
	//std::cout<<d_sch[j]<<std::endl;
};

      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_SYNC_CC_IMPL_H */

