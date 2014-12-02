#include<iostream>
#include<complex>

int xcorrlag_ii(const int* x, int N, int lag)
{
	/*Calculates autocorrelation at lag 'lag' of an 
	integer array 'x' of length 'N'. */
	int ans=0; 
	for(int i=lag;i<N;i++)
		ans+=x[i]*x[i-lag]; //Can be optimised by VOLK
	return ans;
}



void gausselim(int **a, gr_complex *b, gr_complex *h)
{
	/*Solves Ah=b by Gauss-Jordan Elimination*/
	int A11,A12,A21,A22,C2; 
	gr_complex B1,B2,D2;
	
	//Gaussian elimination
	B1=b[1]*(gr_complex)a[0][0]-b[0]*(gr_complex)a[1][0];
	B2=b[2]*(gr_complex)a[0][0]-b[0]*(gr_complex)a[2][0];
	A11=a[1][1]*a[0][0]-a[0][1]*a[1][0];
	A12=a[1][2]*a[0][0]-a[0][2]*a[1][0];
	A21=a[2][1]*a[0][0]-a[0][1]*a[2][0];
	A22=a[2][2]*a[0][0]-a[0][2]*a[2][0];
	C2=A22*A11-A12*A21;  // 3rd row pivot
	D2=B2*(gr_complex)A11-B1*(gr_complex)A21;	

	/*cout<<(int)A11<<' '<<(int)A22<<endl;//DEBUG*/
	//back substitution
	h[2]=D2/(gr_complex)C2;
	h[1]=(B1-h[2]*(gr_complex)A12)/(gr_complex)A11;
	h[0]=(b[0]-(gr_complex)a[0][1]*h[1]-(gr_complex)a[0][2]*h[2])/(gr_complex)a[0][0];
    for(int q=0;q<3;q++)
    {
        std::cout<<"\thest"<<q<<h[q]<<std::endl;
    }
}




void LS_estimator(gr_complex *h_esti, const char xbin[], const gr_complex *r)
{
	/*N is the size of r. Length of xbin array will be N but only first N-2 
	elements will be filled. The last two are 0s.*/
	
	//Ensuring that the last two elements are zero. 
	int xnrz[N];
	for(int i=0;i<N-2;i++)
		xnrz[i]=(xbin[i]==0)?1:-1;
	xnrz[N-2]=1;
	xnrz[N-1]=1;
	/***********

	Calculating A matrix = X^H*X
	**********/
	int A[3][3];
	A[0][0]=N;//If elements are in NRZ form, then diag elements=N.
	A[0][1]=-xnrz[0]+xcorrlag_ii(xnrz,N,1);
	A[0][2]=-xnrz[0]-xnrz[1]+xcorrlag_ii(xnrz,N,2);
	A[1][0]=A[0][1];
	A[1][1]=N;//diag element
	//A[1][2]=1-xnrz[0]+xcorrlag_ii(xnrz,N-1,1);
	A[1][2]=1+A[0][1]-xnrz[N-1]*xnrz[N-2]; //Optimised version of above
	A[2][0]=A[0][2];
	A[2][1]=A[1][2];
	A[2][2]=N;//diag element
	
	//DEBUG
	/*for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cout<<A[i][j]<<' ';
		cout<<endl;
	}*/
	
	/***********
	Calculating b vector = X^H*r
	**********/
	gr_complex b[3];
	/*The approach is to combine three possible for loops into one.
	From i=2 onwards, it can be combined.
	This means that i=0 and i=1 elements have to be manually computed.*/
	b[0]=(gr_complex)xnrz[0]*r[0]+(gr_complex)xnrz[1]*r[1];
	b[1]=-r[0]+(gr_complex)xnrz[0]*r[1];
	b[2]=-r[0]-r[1];
	for(int i=2;i<N;i++)
	{
		b[0]+=(gr_complex)xnrz[i]*r[i];
		b[1]+=(gr_complex)xnrz[i-1]*r[i];
		b[2]+=(gr_complex)xnrz[i-2]*r[i];
	}
	
	//DEBUG
	/*for(int i=0;i<3;i++)
		cout<<b[i]<<' ';*/
	
	/***********
	Calculating  h_esti using Gauss-Jordan Elimination
	***********/
	gausselim(A,b,h_esti);
}


