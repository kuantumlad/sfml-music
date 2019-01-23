#include "../include/FFT.hh"
#include <cmath>
#include <complex>
#include <cstdio>


FFT::FFT(){


}


FFT::~FFT(){


}


void FFT::getSeparateOddsEvens( std::complex<double>* a, int n){
  std::complex<double>* b = new std::complex<double>[n/2];
  for(int i=0; i<n/2; i++){    // copy all odd elements to heap storage
    b[i] = a[i*2+1];
  }
  for(int i=0; i<n/2; i++){    // copy all even elements to lower-half of a[]
    a[i] = a[i*2];
  }  
  for(int i=0; i<n/2; i++){    // copy all odd (from heap) to upper-half of a[]
    a[i+n/2] = b[i];
  }
}

//get fourier transfor fast using Cooley-Tukey method
void FFT::getFFT(std::complex<double>* X, int N){//int start_sample, int end_sample){
  
  //  fft2 (complex<double>* X, int N) {
  if(N < 2) {
    // bottom of recursion.
    // Do nothing here, because already X[0] = x[0]
  } else {
    getSeparateOddsEvens(X,N);      // all evens to lower half, all odds to upper half
    getFFT(X,     N/2);   // recurse even items
    getFFT(X+N/2, N/2);   // recurse odd  items
    // combine results of two half recursions
    for(int k=0; k<N/2; k++) {
      std::complex<double> e = X[k    ];   // even
      std::complex<double> o = X[k+N/2];   // odd
      //w is the "twiddle-factor"
      std::complex<double> w = exp( std::complex<double>(0,-2.*M_PI*k/N) );

      X[k    ] = e + w * o;
      X[k+N/2] = e - w * o;
      
    }
  }

}


