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



void interleavef(float *in, float *out, int R,int C);
void interleave(char *in, char *out, int R,int C);
void set_trellis(trellis *t,int K, int G1,int G2,int Nrzrule);
void convdec(const float *in,char *out, int N, trellis *t, vitstatecd**, vitbmsps *);



void convdecode(const float *in,char *out, int N, trellis *t, vitstatecd **st, vitbmsps *bmsps){
	bmsps[0].nsp=000.0;
	for(int k=1;k<t->numStates;k++)
	bmsps[k].nsp=1000.0;


	for(int l=0;l<(N+t->K-1);l++){	
		for(int k=0;k<t->numStates;k++){
			bmsps[k].bm[0]  = (in[(l<<1)]- t->outputg1[0][k])*(in[(l<<1)]- t->outputg1[0][k])
				     + (in[(l<<1)+1]-t->outputg2[0][k])*(in[(l<<1)+1]-t->outputg2[0][k]);
			bmsps[k].bm[1]  = (in[(l<<1)]- t->outputg1[1][k])*(in[(l<<1)]- t->outputg1[1][k])
				     + (in[(l<<1)+1]-t->outputg2[1][k])*(in[(l<<1)+1]-t->outputg2[1][k]);
			}
		
		for(int k=0;k<t->numStates;k++){
			bmsps[k].sp=bmsps[k].nsp;						
			}


		
		float pm0,pm1;
		for(int k=0;k<t->numStates;k++){
			char pstate=((t->numStates-1) & k<<1);
			pm0=bmsps[k].bm[0]+bmsps[pstate].sp;
			pm1=bmsps[k].bm[1]+bmsps[pstate+1].sp;
			//printf(" %2.1f %2.1f\t",pm0,pm1);
				if (pm0<pm1){
					bmsps[k].nsp=pm0;
					st[k][l].tracepath=pstate;
					//printf("  %d", st[k][l].tracepath); 
					}
				else{
					bmsps[k].nsp=pm1;
					st[k][l].tracepath=pstate+1;
					//printf("  %d", st[k][l].tracepath);
					}
				//printf("%1.0f\t",bmsps[k].nsp);
		}
			//printf("\t%d \n", l);

	//printf("%2.1f\t%2.1f\t%2.1f\t%2.1f\tin %1.2f%1.2f\n", bmsps[0].nsp,bmsps[1].nsp,bmsps[2].nsp,bmsps[3].nsp, in[(l<<1)],in[(l<<1)+1]);

	} // end of forward trace
		
	//printf("%2.1f\t%2.1f\t%2.1f\t%2.1f\tout%1.2f\n", bmsps[0].nsp,bmsps[1].nsp,bmsps[2].nsp,bmsps[3].nsp);	 
	char k=0;
	for(int l=N+t->K-2;l>=0;l--){
		out[l]= k>> (t->K-2);
		//printf("%d\n", st[k][l].tracepath);
		k=st[k][l].tracepath;
		
	}

}





void set_trellis(trellis *t,int K, int G1,int G2, int Nrzrule){
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





void interleavef(float *in, float *out, int R,int C){
	for(unsigned int r=0;r<R;r++)
		for(unsigned int c=0;c<C;c++)
		out[R*c+r]=in[C*r+c];
	}

void interleave(char *in, char *out, int R,int C){
	for(unsigned int r=0;r<R;r++)
		for(unsigned int c=0;c<C;c++)
		out[R*c+r]=in[C*r+c];
	}











