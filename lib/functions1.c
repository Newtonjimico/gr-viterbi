/*#ifndef FUNCTOINS_H
#define FUNCTIONS_H
#include "functions.h"
#endif

#define T 100
#define T2 (T/2)
#define TM2 (T2-2)
#define ITER 1
#define P 48
*/
#include<stdio.h>
#include<stdlib.h>

void vitmlsesova(float *in, float *llr, int N, float* xk, vitstate **all);
float minf(float a,float b);
void vitmlsesova( float *in, float *llr, int N, float* xk, vitstate **all)
{
	

	int L=3;
	//char tracepath[T2][4];
	float bm[2][4]={};
	float sp[4]={};
	float nsp[4]={};
	nsp[0]=0;
	for(int k=1;k<4;k++)
	nsp[k]=1000.0; 
	float xoby2=xk[0]/2.0;
        //printf("%f\t%f\t%f\t", xk[0],xk[1],xk[2]);

	char pstate;
	float pm0,pm1;
	
	for(int l=0;l<(N+L-1);l++){
		////printf("%d%d\n", in[j*2],in[j*2+1]);
		// encoding rule 0=-1, 1=+1;

		bm[0][0]=-2*(-in[l]-xk[1]-xk[2]-xoby2);//state 0 000
		bm[1][0]=-2*(-in[l]-xk[1]+xk[2]-xoby2);// 	 001
		bm[0][1]=-2*(-in[l]+xk[1]-xk[2]-xoby2);//state 1 010
		bm[1][1]=-2*(-in[l]+xk[1]+xk[2]-xoby2);//	 011
		bm[0][2]=-2*( in[l]+xk[1]+xk[2]-xoby2);//state 2 100
		bm[1][2]=-2*( in[l]+xk[1]-xk[2]-xoby2);//	 101
		bm[0][3]=-2*( in[l]-xk[1]+xk[2]-xoby2);//state 3 110
		bm[1][3]=-2*( in[l]-xk[1]-xk[2]-xoby2);//	 111 
/*
		bm[0][0]=-2*( in[l]-xk[1]-xk[2]-xoby2);//state 0 000
		bm[1][0]=-2*( in[l]-xk[1]+xk[2]-xoby2);// 	 001
		bm[0][1]=-2*( in[l]+xk[1]-xk[2]-xoby2);//state 1 010
		bm[1][1]=-2*( in[l]+xk[1]+xk[2]-xoby2);//	 011
		bm[0][2]=-2*(-in[l]+xk[1]+xk[2]-xoby2);//state 2 100
		bm[1][2]=-2*(-in[l]+xk[1]-xk[2]-xoby2);//	 101
		bm[0][3]=-2*(-in[l]-xk[1]+xk[2]-xoby2);//state 3 110
		bm[1][3]=-2*(-in[l]-xk[1]-xk[2]-xoby2);//	 111
//	*/
		
		for(int k=0;k<4;k++){
			sp[k]=nsp[k];
			all[k][l].sp=nsp[k];
			}
		/*for(int m=0;m<2;m++){ printf("\n");
			for(int j=0;j<4;j++)
			printf("%1.3f\t",bm[m][j]);
			}
		*/

		//bm[T2][4][2]
		//printf("\n %d\t", l);
		for(int k=0;k<4;k++){
			pstate=(3 & (k<<1));
			pm0=bm[0][k]+sp[pstate];
			pm1=bm[1][k]+sp[pstate+1];
			if (pm0<pm1)
				{
				nsp[k]=pm0;
				//tracepath[l][k]=pstate;
				all[k][l].ps0=pstate;
				all[k][l].ps1=pstate+1;
				all[k][l].delta=pm1-pm0;
				//printf("%1.4f\t", all[k][l].delta);
				}
			else
				{
				nsp[k]=pm1;
				//tracepath[l][k]=pstate+1;
				all[k][l].ps0=pstate+1;
				all[k][l].ps1=pstate;
				all[k][l].delta=pm0-pm1;
				//printf("%1.4f\t", all[k][l].delta);
				}

			//printf("%1.1f\t",nsp[k]);
		}
			
	}


	

	//Reliability Extraction
	

	char ks0=0;
	char ks1=0;
	char ps0=0;
	char ps1=0;
	char psm0=0;
	char psm1=0;
	float delta=0;
	char bit0=0;
	char bit1=0;   
	float r0= -4*(in[0]-xk[1]-xk[2]); if(r0<0) r0=-r0; // Reliablity info for first bit of the sequence
	llr[0]=r0;
	for(int j=1;j<N+L-2;j++)
	llr[j]=1000.0;	
	float K;
	for(int j=N+L-2;j>0;j--){
		ps0=all[ks0][j].ps0;
		ps1=all[ks0][j].ps1;
		delta=all[ks0][j].delta;
		//printf("delta %1.2f\t%d\n",delta, j);
		bit0=(ks0&2)>>1;
		bit1=(ks0&2)>>1;
		psm0=ps0;
		psm1=ps1;
		ks0=ps0;		
        	K=(j-9);if(K<0) K=0; 
		for(int m=j-1;m>=K;m--){
			if(bit0!=bit1) 
				llr[m+1]=minf(llr[m+1],delta);
			bit0=(psm0&2)>>1;
			bit1=(psm1&2)>>1;
			psm0=all[psm0][m].ps0;
			psm1=all[psm1][m].ps0;
		}

	} 


	//Traceback to get Hard bits
	
	char k=0;
	for(int j=N+L-2;j>=0;j--){
		llr[j]= (1-2*((k&2)>>1))*llr[j]/3.9785;  /// Normalization for GMSK 0.3 BT
		k=all[k][j].ps0;
	} 


	//for(int j=0;j<N;j++){
	//printf("\n%d\t%1.4f\t\t%1.1f", j,llr[j],in[j]); }// Good way to see output 
	///for(int k=0;k<4;k++)
		//printf("%1.3f \t", all[k][j].delta);
	
}// end of vitmlsesova

float minf(float a,float b){
if(a>b)
return b;
else 
return a;
}

