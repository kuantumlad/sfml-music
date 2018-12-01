#include <TMath.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>     
#include <math.h>       /* cos */


int exploreDFT(){

  
  
  const int SAMPLES = 4;
  const int SAMPLE_RATE = 4;
  //sf::Int16 raw[SAMPLES];
  const double TWO_PI = 6.28318;
  const double freq = 255.0; //1.0/period;
  double period = 1.0/freq;//

  double delta_t = 4.0;//3.0/4.0;
  const double increment = delta_t/SAMPLES;

  std::vector<double> sample;
  std::vector<double> sample_t; 
  
  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    double n = (double)i/((double)SAMPLES);
    double raw_amp = 5.0 + 2.0*cos( (3.1415926/2.0 ) * x  - (3.1415926/2.0 ) ) + 3.0 * cos( 3.1415926 * x );
    
    //std::cout << " >> arg " << x*TWO_PI*freq << std::endl;
    x+= increment;
    std::cout << " X " << x << " RAW " << raw_amp << std::endl;
    sample.push_back((int)raw_amp);
    sample_t.push_back(x);
  }

  TGraph *g_signal = new TGraph(SAMPLES,&(sample_t[0]),&(sample[0]));

   
  std::vector<int> k;
  std::vector<int> n;
  std::vector<double> out_freq_value;
  double pi = 3.1415926538;
  
  for( int b = 0; b < SAMPLES; b++ ){

    std::cout << " >> b " << b << " " << sample[b] << std::endl;
    k.push_back(b);
    n.push_back(b);
    out_freq_value.push_back((double)b);
  }


  std::vector<double> c_real;
  std::vector<double> c_img;
  std::vector<double> dft_amp;
  
  int N = 4;
  
  for( int t1 = 0; t1 < SAMPLES; t1++ ){


    double sum_real = 0.0;
    double sum_img = 0.0;
    
    for( int t2 = 0; t2 < SAMPLES; t2++ ){
      double real_cos = cos( 2*pi*k[t1]*n[t2]/N );
      double img_sin = -sin( 2*pi*k[t1]*n[t2]/N );

      //std::cout << " real cos " << real_cos << std::endl;
      //std::cout << " img sin " << img_sin << std::endl;

      int x_in = sample[t2]; //same size as matrix rows MUST BE!
      double c_out_real = x_in * real_cos;
      double c_out_img = x_in * img_sin;

      sum_real=sum_real+c_out_real ;
      sum_img=sum_img+c_out_img;
      
      
    }

    std::cout << " >> sum real " << sum_real << " sum img " << sum_img << std::endl;
    
    c_real.push_back(sum_real);
    c_img.push_back(sum_img);
    double amp = sqrt( pow(c_real[t1],2) + pow(c_img[t1],2) );
    dft_amp.push_back(amp);
    std::cout << " >> amp of freq " << t1 << ": " << amp << std::endl;
  }

  // amplitude graph
  TGraph *g_amp = new TGraph(N,&( out_freq_value[0]),&(dft_amp[0]));
  g_amp->SetTitle("DFT Freq Amplitude");
  

  ////////////////////////////////////////////////////////////////////
  // Draw everything pretty like here
  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(1,1);
  c1->cd(1);
  g_signal->SetTitle("Signal");
  g_signal->GetXaxis()->SetTitle("time");
  g_signal->GetYaxis()->SetTitle("Amplitude");
  g_signal->Draw("ALP");

  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c2->Divide(1,1);
  c2->cd(1);
  g_amp->SetMarkerStyle(20);
  g_amp->GetXaxis()->SetTitle(" Frequency [Hz] ");
  g_amp->GetYaxis()->SetTitle(" Freq Magnitude ");
  g_amp->Draw("AP");
  
  
  
  return 0;

}

