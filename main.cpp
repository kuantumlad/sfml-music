#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

int main(){


  sf::SoundBuffer buffer;
  if( !buffer.loadFromFile("//Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav") ){
    std::cout << " could not load song from file " << std::endl;
  }

  int channel_count = buffer.getChannelCount();
  int sample_count = buffer.getSampleCount()/10000;
  int sample_rate = buffer.getSampleRate();
  int duration = buffer.getDuration().asSeconds();

  double samplePerSeconds = (double)sample_count/(double)duration;
  double secondsPerSample = (double)duration/(double)sample_count;

  std::cout << " sample count " << sample_count << std::endl;
  std::cout << " seconds per sample " << secondsPerSample << std::endl;
  
  const sf::Int16 *sample = buffer.getSamples();

  int windowX = 1000;
  int windowY = 1000;
  sf::Vector2i windowPos(0,0);
  
  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"DFT" );
  window.setPosition(windowPos);

  //int max_sample_amp = -1;
  //int temp=-1;
  //for( int b = 0; b < sample_count; b++ ){
  //int raw_sample = sample[b];
  //if( raw_sample > max_sample_amp ){
  //  max_sample_amp=raw_sample;           
  // }
  //}
  //std::cout<< " normalize buffer samples by " << max_sample_amp << std::endl;
  // result: 29205



  int max_sample_amp = 29205;
  int hamming_interval = 16432;
  sf::VertexArray bufferLines(sf::LinesStrip,16324);
  int zeroLevel = 50;
  int compressFactor = 10;

  int numTimeWindows=sample_count/16432;
  int hamming_length = 1000;
  std::cout << " Number of time windows of 16432 buffer samples is " << numTimeWindows << std::endl;
  
  std::map<int, sf::VertexArray > m_bufferLine;
  
  int bufferWindowStart = 0;
  int bufferWindowEnd = hamming_interval;
  for( int i = 0; i < sample_count; i++ ){

    sf::VertexArray temp_bufferLines(sf::LinesStrip,hamming_interval);
    int temp_counter=0;
    for( int b=0; b < hamming_length; b++){
      if( (i + b ) == sample_count ) break;
      double norm_sample_amp = (double)sample[i+b]/(double)max_sample_amp * 100.0;
      //std::cout << " norm sample " << zeroLevel + norm_sample_amp << std::endl;
      temp_bufferLines[temp_counter].position = sf::Vector2f( temp_counter/10, zeroLevel + (int)norm_sample_amp);
      temp_counter++;
      std::cout << " >> on sample " << (i + b) << std::endl;
    }
    //bufferWindowStart=bufferWindowEnd;
    //bufferWindowEnd=bufferWindowEnd + hamming_interval;
    
    m_bufferLine[i]=temp_bufferLines;
    //std::cout<< " >> buffer start " << bufferWindowStart << " buffer end " << bufferWindowEnd << std::endl;

  }


  std::vector<int> v_small;
  std::vector<int> v_big;

  for( int i =0; i < 100; i++ ){
    v_big.push_back(i);
  }

  int small_size=5;
  int number_of_div=v_big.size();
  int index = 0;
  int shift=0;
  for( int i=0; i < number_of_div; i++ ){
    //std::cout << " on segment " << i << std::endl;
    for( int j = 0; j < small_size; j++ ){
      if( (i+j) == v_big.size() ) break;
      //std::cout << " >>  " << v_big[j + i] << std::endl;
    }

  }
    

  

  sf::Clock clock; // starts the clock
  
  int i = 0;
  double time2_elapsed=0;

  int tempt = 0;
  int deltat = 1;
  double tempt2=0.0;
  while(window.isOpen()){
    sf::Event event;

    while( window.pollEvent(event) ){
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
      }
    }
    
    sf::Time elapsed1 = clock.getElapsedTime();
    double time_elapsed1 = elapsed1.asSeconds();
    //std::cout << elapsed1.asSeconds() << std::endl;

    tempt=tempt+deltat;
    //std::cout << " >> " << tempt << std::endl;
    bool testtemp = tempt == 100000;
    //std::cout << " >> BOOLEAN TEST "<< testtemp << std::endl;
    if( tempt == 10000 ){
    
      //      std::cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> >> tempt  " << tempt << std::endl;
      //if( elapsed1.asSeconds() > duration ){
      //i=0;
      //}
      //clock.restart();
      tempt=0;
      window.clear(sf::Color::Black);          


      window.draw(m_bufferLine[i]);


      window.display();
      i++;  
    }


    
    time2_elapsed=elapsed1.asSeconds();
    
          
  }

    
  
  return 0;

}
