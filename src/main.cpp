#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>
#include <complex>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "../include/Histogram.hh"
#include "../include/SoundManager.hh"
#include "../include/FFT.hh"

int main(){

  std::cout << " starting program " << std::endl;


  // Initialize window details
  int windowX = 800;
  int windowY = 800;
  sf::Vector2i windowPos(0,0);
  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"DFT" ); 
  window.setPosition(windowPos);

  // Load sound file from data
  // Here we load a simple middle c note played on a piano. It's frequency is 261 Hz.
  SoundManager soundManager;
  soundManager.loadSound("/Users/bclary/Documents/work/codeprojects/music/sounds/95328__ramas26__c.wav");

  // Get wav file specs
  const int sample_count = soundManager.getSampleCount();
  int sample_rate = soundManager.getSampleRate();
  double sample_duration = soundManager.getSampleDuration();
  double freq_res = (double)sample_rate/(double)soundManager.getSampleCount();

  std::cout << " SOUND FILE INFORMATION " << std::endl;
  std::cout << " --> Sample duration          " << sample_duration << "seconds" << std::endl;
  std::cout << " --> Frequency resolution is  " << freq_res << " Hz " << std::endl;
 
  int max_sample_value = soundManager.getMaxSampleValue();
  std::complex<double>* X = soundManager.getComplexNormalizedSamples();

  // Init the FFT class to call either the DFT I wrote or the FFT by Cooley–Tukey algorithm
  
  FFT fft2;

  int index_min = 0;
  int index_max = 0;
  const int index_window = 4096;
  double index_window2 = 4096.0;

  // Specifiy fraction of sample the FFT window covers
  double window_fraction = 4096.0/(double)soundManager.getSampleCount();

  double freq_scaler = 10.0;
  double minfreq = 1;
  double maxfreq = ((double)sample_count/2.0) * (sample_rate/(index_window2));
  int nbins = (maxfreq - minfreq)/freq_res;

  // Init histogram class to display results of FFT
  Histogram fftHist;
  double x_norm = 10.0;
  double bin_resolution = sample_rate/(index_window2 * x_norm);
  // multiplicative factor for scaling the x axis bars to make it look visually appealing
  double x_scale = 1.0/10.0;
  // Arguments used to init histograms are arbitrary and basedo on what looks "good"
  fftHist.initHistogram(index_window/20, 1.0, 8000.0, x_scale);
    
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
  // update_time value is based on the FFT window size
  double update_time = ((double)sample_duration/(double)sample_count) * index_window2 / 2.;
  soundManager.playSound();

  while(window.isOpen()){
    sf::Event event;

    while( window.pollEvent(event) ){
      
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();       
      }
    }
    window.clear(sf::Color::Black);          

    // set time keeping variables to monitor when to update the window
    sf::Time elapsed = clock.restart();
    sf::Time elapsed2 = clock2.getElapsedTime();
    
    elapsedtime = elapsed.asSeconds() + elapsedtime;
    total_elapsed_time = elapsed2.asSeconds();
    
    //windowing indices
    if(  elapsedtime > update_time ){ 
      if( index_max < sample_count){

	index_min = index_max;
	index_max = index_max + index_window;

	// Write the windowed elements into Xtemp array
	std::complex<double>* Xtemp = new std::complex<double>[index_window];
	for( int s = 0; s < index_window; s++ ){
	  Xtemp[s] = X[index_min + s];
	}

	// Pass Xtemp into FFT.
	//getFFT alters the elements of Xtemp to the result of the fft for that bin
	// note: must use fft rather than dft due to dft is of O(n2)
	fft2.getFFT(Xtemp,index_window);           
	for( int s = 1; s < index_window/2; s++ ){
	  fftHist.setBinContentByRange( (int)(s*sample_rate/(index_window2)), -1.0*(std::abs(Xtemp[s])));
	}
	
	elapsedtime = 0.0;

	// Draw histogram of sounds
	window.draw(trueFreqLines);
	window.draw(fftHist);
	window.display();
      }    
      else{
	index_min = sample_count - index_window;
	index_max = sample_count;
      }
    }    
  }

  std::cout <<  " done  " << std::endl;
  
  return 0;

}









