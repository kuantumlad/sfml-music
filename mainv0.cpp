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
  
  sf::SoundBuffer buffer;
  // Load it from a file
  if (!buffer.loadFromFile("/Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav")){   
    std::cout << " ERROR " << std::endl;
    // error...
  }
  
  int channel_count = buffer.getChannelCount();
  int sample_count = buffer.getSampleCount();
  int sample_rate = buffer.getSampleRate();
  int duration  = buffer.getDuration().asSeconds();
  
  int total_song_len = sample_count / sample_rate;

  const sf::Int16 *sample = buffer.getSamples();

  std::cout << " >> CHANNEL COUNT IS " << channel_count << std::endl;
  std::cout << " >> SAMPLE COUNT IS " << sample_count << std::endl;
  std::cout << " >> SAMPLE RATE IS " << sample_rate << std::endl;
  std::cout << " >> SONG LENGTH IS " << total_song_len << std::endl;
  
  int current_sample = 0;
  int last_sample_index = 0;
  int dsample = sample_rate/100;
  double norm_value = pow(2,16); // / 2.0;

  std::vector<double> norm_sample;
  int s_min = 0;
  int s_max = 100000;
  std::vector<int> k;
  std::vector<int> n;
  double pi = 3.1415926538;

  // change input integer from [-1,1) / normalize

  // write to text file to read into root to explore signal
  std::ofstream bufferToText;
  std::string outDir = "./";
  std::string outName = outDir+"lvb_buffer.txt";
  bufferToText.open(outName);


  int counter = 0;
  for( int b = s_min; b < s_max; b++ ){
    
    double sample_norm = sample[b] / norm_value;
    norm_sample.push_back( sample[b] / norm_value );

    if( b > 60000 && b < 70000 ){
    
    double bufferNorm = sample[b] / norm_value ;
    bufferToText << bufferNorm << std::endl;
    //std::cout << " norm " << sample_norm << std::endl;
    counter++;
    }
    k.push_back(b);
    n.push_back(b);
    
  }

  bufferToText.close();

  /*  
  const unsigned SAMPLES = 360; //44100;
  const unsigned SAMPLE_RATE = 10;//44100;
  const unsigned AMPLITUDE = 100.0; //30000;

  sf::Int16 raw[SAMPLES];

  const double TWO_PI = 6.28318;
  
  const double freq = 255.0; //1.0/period;
  double period = 1.0/freq;//

  double w0 = 2.0*3.141526*freq;
  
  const double increment = period/SAMPLES;
  double x = 0;
  for (unsigned i = 0; i < SAMPLES; i++) {
    double n = (double)i/((double)SAMPLES);
    raw[i] = AMPLITUDE * sin(w0*n);
    //std::cout << " >> arg " << x*TWO_PI*freq << std::endl;
    x += increment;
    std::cout << " X " << x << " RAW " << raw[i] << std::endl;
  }

  //sf::SoundBuffer Buffer;
  //if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
  //std::cerr << "Loading failed!" << std::endl;
  // return 1;
  //}

  //int sample_count = Buffer.getSampleCount();
  //const sf::Int16 *sample = Buffer.getSamples();
  
  std::cout << " >> Max loop number" << sample_count << std::endl;
  std::vector<int> k;
  std::vector<int> n;
  double pi = 3.1415926538;
  
  for( int b = 0; b < sample_count; b++ ){

    std::cout << " >> b " << b << " " << sample[b] << std::endl;
    k.push_back(b);
    n.push_back(b);
  }

  double N = SAMPLES;// SAMPLE_RATE; //n.size();
  //  double ft_matrix[1000][1000];
  
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
    
  }


  for( int i = 0; i < SAMPLES; i++ ){
    double amp = 2.0*sqrt( pow(c_real[i],2) + pow(c_img[i],2) );
    if( amp > 1.0 ){
      std::cout << " >> " << i << " " << amp << std::endl;
    }
  }

  

  
  //std::cin.get();

  
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
