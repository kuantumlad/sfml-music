#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <complex>     
#include <math.h>       /* cos */
#include <string>
#include <fstream>

int main(){

  //sf::Music music;
  //if (!music.openFromFile("/Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav")){
  //  std::cout << " ERROR LOADING MUSIC FILE " << std::endl;
  //  sf::sleep(sf::seconds(5));
  //  return -1; // error
  //}
  //music.play();


  const int SAMPLES = 100;
  const int SAMPLE_RATE = 100;
  sf::Int16 raw[SAMPLES];
  const double TWO_PI = 6.28318;
  const double freq = 255.0; //1.0/period;
  double period = 1.0/freq;//

  double delta_t = 10.0;//3.0/4.0;
  const double increment = delta_t/SAMPLES;
  

  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    double n = (double)i/((double)SAMPLES);
    raw[i] = 5.0 + 2.0*cos( (3.1415926/2.0 ) * x  - (3.1415926/2.0 ) ) + 3.0 * cos( 3.1415926 * x );
    
    //std::cout << " >> arg " << x*TWO_PI*freq << std::endl;
    x+= increment;
    std::cout << " X " << x << " RAW " << raw[i] << std::endl;
  }

  sf::SoundBuffer Buffer;
  if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
    std::cerr << "Loading failed!" << std::endl;
    return 1;
  }

  int sample_count = Buffer.getSampleCount();
  const sf::Int16 *sample = Buffer.getSamples();
  
  std::cout << " >> Max loop number" << sample_count << std::endl;
  std::vector<int> k;
  std::vector<int> n;
  double pi = 3.1415926538;
  
  for( int b = 0; b < sample_count; b++ ){

    std::cout << " >> b " << b << " " << sample[b] << std::endl;
    k.push_back(b);
    n.push_back(b);
  }

  double N = SAMPLE_RATE;
  
  std::cout << " >> buffer size " << N << std::endl;
  std::cout << " >> buffer rate " << Buffer.getSampleRate() << std::endl;
  
  std::vector<double> c_real;
  std::vector<double> c_img;
  
  for( int t1 = 0; t1 < SAMPLES; t1++ ){


    double sum_real = 0.0;
    double sum_img = 0.0;
    
    for( int t2 = 0; t2 < SAMPLES; t2++ ){
      double real_cos = cos( 2*pi*k[t1]*n[t2]/N );
      double img_sin = -sin( 2*pi*k[t1]*n[t2]/N );

      //std::cout << " real cos " << real_cos << std::endl;
      //std::cout << " img sin " << img_sin << std::endl;

      int x_in = raw[t2]; //same size as matrix rows MUST BE!
      double c_out_real = x_in * real_cos;
      double c_out_img = x_in * img_sin;

      sum_real=sum_real+c_out_real ;
      sum_img=sum_img+c_out_img;
      
      
    }

    std::cout << " >> sum real " << sum_real << " sum img " << sum_img << std::endl;
    
    c_real.push_back(sum_real/SAMPLES);
    c_img.push_back(sum_img/SAMPLES);
    double amp = 2.0*sqrt( pow(c_real[t1],2) + pow(c_img[t1],2) );
    
  }


  

  /* extras
  const unsigned SAMPLES = 44100;
  const unsigned SAMPLE_RATE = 44100;
  const unsigned AMPLITUDE = 30000;

  sf::Int16 raw[SAMPLES];

  const double TWO_PI = 6.28318;
  const double increment = 440./44100;
  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    raw[i] = AMPLITUDE * sin(x*TWO_PI);
    x += increment;
    std::cout << " X " << x << std::endl;
  }

  sf::SoundBuffer Buffer;
  if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
    std::cerr << "Loading failed!" << std::endl;
    return 1;
  }

  
  sf::Sound Sound;
  Sound.setBuffer(Buffer);
  Sound.setLoop(true);
  Sound.play();
  while (1) {
    sf::sleep(sf::milliseconds(100));
  }
  std::cin.get();
  */  
  
  return 0;

}


  //fft2.getFFT(X,sample_count);

  /*const int nSamples = 2049 ;// soundManager.getSampleCount();//sample_count;
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
  
//-----------------------------------------------------

// For the main main.cpp class removed print out statement

	  //temp_freqLines.append( sf::Vector2f( x_scale*(s*sample_rate/(index_window2 )) , windowY - std::abs(Xtemp[s])) );
	  //temp_freqLines[s-1].color = sf::Color::Red;
	  //std::cout << " precise frequency " << s*sample_rate/(index_window2 * 10) << std::endl;
	  //std::cout << " rounded frequency " << (int)(s*sample_rate/(index_window2 * 10)) << std::endl;
	  //int sampled_freq = (int)(s*sample_rate/(index_window2 * 10.0));
	  //std::cout << " value  in main loop is " << 100.0*std::abs(Xtemp[s]) << std::endl;
	  //fftHist.getData()[s]->setBarHeight(windowY - 1000*std::abs(Xtemp[s]));
	  //fftHist.getData()[s]->updateBarSize();

	  //std::cout << " >> s " << s << " " << X[s] << " " << std::abs(Xtemp[s]) << " " << s*(1.0/(freq_res)) << std::endl;

//window.draw(temp_freqLines);
	//}
		//temp_freqLines.clear();     

