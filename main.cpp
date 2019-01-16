#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>
#include <complex>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "Histogram.hh"
#include "SoundManager.hh"
#include "FFT.hh"

int main(){

  std::cout << " starting program " << std::endl;

  int windowX = 800;
  int windowY = 800;
  sf::Vector2i windowPos(0,0);

  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"DFT" );
  window.setPosition(windowPos);
  
  SoundManager soundmanager;
  soundmanager.loadSound("/Users/bclary/Documents/work/codeprojects/music/95328__ramas26__c.wav");
  //lvb-sym-5-1.wav
  
  
  std::cout <<  " done  " << std::endl;

  const int sample_count = soundmanager.getSampleCount();
  int sample_rate = soundmanager.getSampleRate();
  double sample_duration = soundmanager.getSampleDuration();
  std::cout << " sample duration " << sample_duration << std::endl;
  double freq_res = (double)sample_rate/(double)soundmanager.getSampleCount();
  std::cout << " frequency resolution is  " << freq_res << std::endl;
 
  int max_sample_value = soundmanager.getMaxSampleValue();
  std::cout << " max value in sample " << max_sample_value << std::endl;
  std::complex<double>* X = soundmanager.getComplexNormalizedSamples();

  //std::cout << " first element of norm sample "  << X[200] << std::endl;
  
  FFT fft2;

  int index_min = 0;
  int index_max = 0;
  const int index_window = 4096;
  double index_window2 = 4096.0;

  // init histogram here  
  double window_fraction = 4096.0/(double)soundmanager.getSampleCount();
  std::cout << " window fraction is " << window_fraction << std::endl;

  double freq_scaler = 10.0;
  double minfreq = 1;
  double maxfreq = ((double)sample_count/2.0) * (sample_rate/(index_window2));
  std::cout << " sample count " << sample_count << std::endl;
  std::cout << " >> min freq: " << minfreq << " max freq: " << maxfreq << std::endl;
  int nbins = (maxfreq - minfreq)/freq_res;
  std::cout << " nbins: " << nbins << std::endl;
  Histogram fft_hist;
  double x_norm = 10.0;
  double bin_resolution = sample_rate/(4096.0 * x_norm);
  double x_scale = 1.0/10.0;// multiplicative factor for scaling the x axis bars
  fft_hist.initHistogram2(index_window/20, 1.0, 8000.0, x_scale);//  sample_rate, index_window2, x_norm, bin_resolution );
  //fft_hist.initHistogram((index_window/2) * sample_rate/(index_window2 ), sample_rate, index_window2, x_norm, bin_resolution );
    
  double freq = (261.0)*x_scale;
  sf::VertexArray temp_freqLines(sf::LinesStrip,0);
  sf::VertexArray trueFreqLines(sf::LinesStrip,0);
  trueFreqLines.append( sf::Vector2f(freq, 0) );
  trueFreqLines.append( sf::Vector2f(freq, windowY) );
  trueFreqLines[0].color = sf::Color::Red;
  trueFreqLines[1].color = sf::Color::Red;


  sf::Clock clock;
  sf::Clock clock2;
  double elapsedtime = 0.0;
  double total_elapsed_time = 0.0;
  double update_time = ((double)sample_duration/(double)sample_count) * index_window2 / 2. ; //- 0.001; //-0.0368;
  std::cout << " update time " << update_time << std::endl;
  soundmanager.playSound();

  while(window.isOpen()){
    sf::Event event;

    while( window.pollEvent(event) ){
      
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();       
      }
    }
    window.clear(sf::Color::Black);          

    sf::Time elapsed = clock.restart();
    sf::Time elapsed2 = clock2.getElapsedTime();
    
    elapsedtime = elapsed.asSeconds() + elapsedtime;
    //std::cout << " elapsed time " << elapsedtime << std::endl;

    total_elapsed_time = elapsed2.asSeconds();
    
    //windowing indices
    if(  elapsedtime > update_time ){ 
      if( index_max < sample_count){
      //do stuff here
      index_min = index_max;
      index_max = index_max + index_window;
      //std::cout << " index min " << index_min << std::endl;
      //std::cout << " index max " << index_max << std::endl;

      std::complex<double>* Xtemp = new std::complex<double>[index_window];
      for( int s = 0; s < index_window; s++ ){
	Xtemp[s] = X[index_min + s];
      }
      fft2.getFFT(Xtemp,index_window);

      
      //fft_hist.getData();
      
      for( int s = 1; s < index_window/2; s++ ){
	//temp_freqLines.append( sf::Vector2f( x_scale*(s*sample_rate/(index_window2 )) , windowY - std::abs(Xtemp[s])) );
	//temp_freqLines[s-1].color = sf::Color::Red;
	//std::cout << " precise frequency " << s*sample_rate/(index_window2 * 10) << std::endl;
	//std::cout << " rounded frequency " << (int)(s*sample_rate/(index_window2 * 10)) << std::endl;
	//int sampled_freq = (int)(s*sample_rate/(index_window2 * 10.0));
	//std::cout << " value  in main loop is " << 100.0*std::abs(Xtemp[s]) << std::endl;
	//fft_hist.getData()[s]->setBarHeight(windowY - 1000*std::abs(Xtemp[s]));
	//fft_hist.getData()[s]->updateBarSize();

	//if( sampled_freq < 4096 ){
	fft_hist.setBinContentByRange( (int)(s*sample_rate/(index_window2)), -1.0*(std::abs(Xtemp[s])));
	//}
	//std::cout << " >> s " << s << " " << X[s] << " " << std::abs(Xtemp[s]) << " " << s*(1.0/(freq_res)) << std::endl;
      }
      elapsedtime = 0.0;
      
      window.draw(trueFreqLines);
      window.draw(fft_hist);
      //window.draw(temp_freqLines);
      //}
      window.display();
      //temp_freqLines.clear();
      

      }    
    else{
      index_min = sample_count - index_window;
      index_max = sample_count;
      //window.display();

      //for( int s = 0; s < index_window; s++ ){
	//    fft_hist.setBinContent(s,0.0);
      //}
      //window.clear(sf::Color::Black);          
      
      //std::cout << " ---------------------------------------------------> FINISHED AND ELAPSED TIME IS " << total_elapsed_time << std::endl;
      //std::cout << " index min " << index_min << std::endl;
      //std::cout << " index max " << index_max << std::endl;      
    }
    }
    //if( elapsedtime > 0.5 ){
    
    for( int s = 0; s < index_window; s++ ){
      //    fft_hist.setBinContent(s,0.0);
    }
  }
  
  
  return 0;

}









  //fft2.getFFT(X,sample_count);

  /*const int nSamples = 2049 ;// soundmanager.getSampleCount();//sample_count;
  double nSeconds = 1.0;                      // total time for sampling
  double sampleRate = nSamples / nSeconds;    // n Hz = n / second
  double freqResolution = sampleRate / nSamples; // freq step in FFT result
  std::complex<double> x[nSamples];                // storage for sample data
  std::complex<double> X[nSamples];                // storage for FFT answer
  const int nFreqs = 5;
  double freq[nFreqs] = { 2, 8, 14, 22, 30 }; // known freqs for testing

  // generate samples for testing
  for(int i=0; i<nSamples; i++) {
    x[i] = std::complex<double>(0.,0.);
    // sum several known sinusoids into x[]
    for(int j=0; j<nFreqs; j++)
      x[i] += sin( 2*M_PI*freq[j]*i/nSamples );
    X[i] = x[i];        // copy into X[] for FFT work & result
  }
  */
  
