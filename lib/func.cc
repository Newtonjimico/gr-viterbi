#include <cmath>
#include <boost/math/special_functions/erf.hpp>
//#include <math.h>
#include<vector>
//#include <cfloat>
//#include<stdio.h>
#define OS2PI 0.398942280401433 // 1/sqrt(2*pi);
#define TWOPI 6.283185307179586

//using namespace std;

namespace bm = boost::math;
double qfunc(double x){ return 0.5*(1-bm::erf(0.7071067812*x)); }

std::vector<float> phasepulse(unsigned L, unsigned M, double bt);
std::vector<float> phasepulse(unsigned L, unsigned M, double bt)	
    { 
	double sum=0;       	
	double Ls = (double) L * M;	
      	std::vector<double> taps_d(L * M, 0.0);	
      	std::vector<float> taps(L*M, 0.0);	
      	// alpha = sqrt(2/ln(2)) * pi * BT
	//      double o = 5.336446256636997 * bt;
	// 2*pi*bt/sqrt(ln(2));
	double o=7.546874671011175* bt;	
      	
	for(unsigned n = 0; n < M * L; n++) 	
        	taps_d[n] = 1.0*(1+(n/(L*1.0)-(M+1)/2.0)*qfunc(o*(n/(L*1.0)-(M+1)/2.0))-(n/(L*1.0)-(M-1)/2.0)*qfunc(o*(n/(L*1.0)-(M-1)/2.0))
   				 -OS2PI/o*(exp(-0.5*pow( (n/(L*1.0)-(M+1)/2.0)*o,2))-exp(-0.5*pow( (n/(L*1.0)-(M-1)/2.0)*o,2) )));
	for(unsigned n = 0; n < M * L; n++)
	taps[n]=(float) taps_d[n];
       return taps;
      } 


