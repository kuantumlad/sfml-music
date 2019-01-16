#ifndef FFT_HH
#define FFT_HH

#include <complex>
#include <cstdio>


class FFT{

public:
  FFT();
  ~FFT();

  void getFFT(std::complex<double>*, int );
  void getSeparateOddsEvens(std::complex<double>*, int);

  //const double M_PI = 3.1415926535897;


};
#endif
