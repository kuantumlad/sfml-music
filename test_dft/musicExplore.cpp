#include <TMath.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>     
#include <math.h>       /* cos */


int musicExplore(){

  
  
  const int SAMPLES = 4;
  const int SAMPLE_RATE = 4;
  //sf::Int16 raw[SAMPLES];
  const double TWO_PI = 6.28318;
  const double freq = 255.0; //1.0/period;
  double period = 1.0/freq;//
  double pi = 3.1415926538;
  

  double delta_t = 4.0;//3.0/4.0;
  const double increment = delta_t/SAMPLES;

  std::vector<double> sample;
  std::vector<double> sample_t; 

  int TOT_SAMPLES = 23281280; //buffer elements
  int SONG_DURATION = 485; //seconds
  double secPerSample=(double)SONG_DURATION/(double)TOT_SAMPLES;
  double samplePerSecond = 48002;
  double norm = pow(2,16);// / 2.0;
  
  int buffer;
  double current_t = 0;
  int buffer_counter = 0;
  std::ifstream readBufferFromText("lvb_buffer.txt");
    
  std::vector< std::vector<double> > v_buffer_window;
  std::vector< std::vector<double> > v_time_window;
  
  int buffer_window_counter = 0;
  int max_window_counter = 1000;
  
  if( readBufferFromText.is_open() ){
  std:cout << " reading from file " << std::endl;
    while( readBufferFromText >> buffer ){
	readBufferFromText >> buffer;

      if( buffer_counter < max_window_counter ) { // && buffer_counter <= samplePerSecond ){
	sample.push_back((double)buffer/norm);
	sample_t.push_back(current_t);
	current_t+=secPerSample;
      }
      else{
	buffer_counter = 0;
	v_buffer_window.push_back(sample);
	v_time_window.push_back(sample_t);
	sample.clear();
	buffer_window_counter++;
      }
      //      std::cout << " buffer counter " << buffer_counter << std::endl;
      
      buffer_counter++;
      //      std::cout << " >> buffer " << buffer << " time " << current_t << std::endl;
    }
  }
  else{
    std::cout << " error opening file " << std::endl;
  }

  std::cout << " >> buffer window size " << v_buffer_window[0].size() << std::endl;
  std::cout << " >> windows " << v_buffer_window.size() << std::endl;
  
  std::vector< TGraph* > v_signal;
  
  TGraph *g_signal = new TGraph(sample.size(),&(sample_t[0]),&(sample[0]));

  for( int w = 0; w < v_buffer_window.size(); w++ ){
    v_signal.push_back( new TGraph(v_buffer_window[w].size(),&(v_time_window[w][0]), &(v_buffer_window[w][0]) ) );
    
  }

  
  TCanvas *c0 = new TCanvas(Form("c_%d",0), Form("c_%d",0), 1600,800);
  c0->Divide(8,6);
  
  for( int w = 0; w < v_buffer_window.size(); w++ ){
    c0->cd(w+1);
    v_signal[w]->SetTitle(Form("g_%d",w));
    v_signal[w]->Draw("ALP");
  }

  std::vector< std::vector<int> > v_k;
  std::vector< std::vector<int> > v_n;
  std::vector< std::vector<double> > v_out_freq;
  std::vector< std::vector<double> > v_buffers;
  
  for( int w = 0; w < v_buffer_window.size(); w++ ){
    std::vector<int> temp_k;
    std::vector<int> temp_n;
    std::vector<double> temp_out_freq;
    std::vector<double> temp_buffers;
    for( int b = 0; b < v_buffer_window[w].size()/2; b++ ){
      //      std::cout << " >> window w " << w << " " << v_buffer_window[w][b] << std::endl;
      //if( w == 26 ) std::cout << v_buffer_window[w][b] << std::endl;
      temp_buffers.push_back(v_buffer_window[w][b]);
      temp_k.push_back(b);
      temp_n.push_back(b);
      temp_out_freq.push_back((double)b);
    }
    v_buffers.push_back(temp_buffers);
    v_k.push_back(temp_k);
    v_n.push_back(temp_n);
    v_out_freq.push_back(temp_out_freq);
  }

  
  std::vector< TGraph* > g_windows_amp;
  
  
  // try processing signal here
  for( int w = 0; w < v_buffer_window.size(); w++ ){
    int N = v_buffer_window[w].size();
    int SAMPLES = v_buffer_window[w].size()/2;
    //std::cout << " >> samples for window " << w << ": " << SAMPLES << std::endl;
        
    std::vector<double> c_real;
    std::vector<double> c_img;
    std::vector<double> dft_amp;
      
    for( int t1 = 0; t1 < SAMPLES; t1++ ){

      double sum_real = 0.0;
      double sum_img = 0.0;
    
      for( int t2 = 0; t2 < SAMPLES; t2++ ){

	double real_cos = cos( 2*pi*v_k[w][t1]*v_n[w][t2]/N );
	double img_sin = -sin( 2*pi*v_k[w][t1]*v_n[w][t2]/N );

	//	std::cout << " real cos " << real_cos << std::endl;
	//std::cout << " img sin " << img_sin << std::endl;

	double x_in = v_buffers[w][t2]; //same size as matrix rows MUST BE!
	//std::cout << " >> x in " << v_buffer_window[w][t2] << std::endl;
	double c_out_real = x_in * real_cos;
	double c_out_img = x_in * img_sin;

	sum_real=sum_real+c_out_real ;
	sum_img=sum_img+c_out_img;
            
      }

      // std::cout << " >> sum real " << sum_real << " sum img " << sum_img << std::endl;
    
      c_real.push_back(sum_real);
      c_img.push_back(sum_img);
      double amp = sqrt( pow(c_real[t1],2) + pow(c_img[t1],2) );
      dft_amp.push_back(amp);
      //std::cout << " >> amp of freq " << t1 << ": " << amp << std::endl;
    }

    g_windows_amp.push_back( new TGraph(dft_amp.size(), &(v_out_freq[w][0]), &(dft_amp[0])) );
    
  }

  TCanvas *c_amp = new TCanvas("c_amp","c_amp",1600,800);
  c_amp->Divide(8,6);
  //c_amp->SetLogx();

  for( int w = 0; w < g_windows_amp.size(); w++ ){
    c_amp->cd(w+1);
    g_windows_amp[w]->SetTitle(Form("g_window%d_amp",w));
    //g_windows_amp[w]->SetMinimum(0.001);
    //g_windows_amp[w]->SetMaximum( v_buffer_window[w].size()/2 );
    g_windows_amp[w]->Draw("ALP");
    //g_windows_amp[w]->SetMarkerStyle(20);
  }
  
  /*

  
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
  
  */
  ////////////////////////////////////////////////////////////////////
  // Draw everything pretty like here
  //TCanvas *c1 = new TCanvas("c1","c1",1600,800);
  //c1->Divide(1,1);
  //c1->cd(1);
  //g_signal->SetTitle("Signal");
  //g_signal->GetXaxis()->SetTitle("time");
  //g_signal->GetYaxis()->SetTitle("Amplitude");
  //g_signal->Draw("ALP");

  /*TCanvas *c2 = new TCanvas("c2","c2",800,800);
  c2->Divide(1,1);
  c2->cd(1);
  g_amp->SetMarkerStyle(20);
  g_amp->GetXaxis()->SetTitle(" Frequency [Hz] ");
  g_amp->GetYaxis()->SetTitle(" Freq Magnitude ");
  g_amp->Draw("AP");
  */
  
  
  return 0;

}

