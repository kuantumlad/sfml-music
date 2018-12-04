#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

int main(){


  sf::SoundBuffer buffer;
  
  if( !buffer.loadFromFile("//Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav") ){
    //if( !buffer.loadFromFile("/home/kuantumlad/Documents/projects/sfml-music/lvb-sym-5-1.wav") ){
    std::cout << " could not load song from file " << std::endl;
  }


  int channel_count = buffer.getChannelCount();
  int sample_count_true=buffer.getSampleCount();
  int sample_count = buffer.getSampleCount()/10000;
  int sample_rate = buffer.getSampleRate();
  int duration = buffer.getDuration().asSeconds();

  double samplePerSeconds = (double)sample_count/(double)duration;
  double secondsPerSample = (double)duration/(double)sample_count;

  std::cout << " sample count " << sample_count << std::endl;
  std::cout << " seconds per sample " << secondsPerSample << std::endl;
  
  const sf::Int16 *sample = buffer.getSamples();

  
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



  int max_sample_amp = 10000; //29205;
  int hamming_interval = 100;
  sf::VertexArray bufferLines(sf::LinesStrip,16324);
  int zeroLevel = 500;
  int compressFactor = 10;

  int numTimeWindows=sample_count/16432;
  int hamming_length = 100;
  std::cout << " Number of time windows of 16432 buffer samples is " << numTimeWindows << std::endl;
  
  std::map<int, sf::VertexArray > m_bufferLine;
  
  int bufferWindowStart = 0;//sample_count_true/2;
  int bufferWindowEnd = 1000;//hamming_interval;

  std::vector<sf::VertexArray> test_array;

  std::cout << " loading information " << std::endl;
  for( int i = bufferWindowStart; i < (bufferWindowStart + sample_count); i++ ){

    sf::VertexArray temp_bufferLines(sf::LinesStrip,0);
    int temp_counter=0;

    for( int b=0; b < hamming_length; b++){
      if( (i + b ) == sample_count ) continue;
      double norm_sample_amp = (double)sample[i+b]/(double)max_sample_amp * 100.0;
      //std::cout << " position "<<  temp_counter <<  " sample " <<  (double)sample[i+b] <<  " norm sample " << zeroLevel + norm_sample_amp << std::endl;

      //temp_bufferLines[temp_counter].position = sf::Vector2f( temp_counter, zeroLevel + (int)norm_sample_amp);
      temp_bufferLines.append( sf::Vector2f( temp_counter/10, zeroLevel + (int)norm_sample_amp) );

      //std::cout << " >> position " << temp_bufferLines[temp_counter].position.x << " y pos "  << temp_bufferLines[temp_counter].position.y <<  std::endl;
      temp_counter++;
      //std::cout << " >> on sample " << (i + b) << " " << temp_bufferLines.getVertexCount() << std::endl;
    }
    //bufferWindowStart=bufferWindowEnd;
    //bufferWindowEnd=bufferWindowEnd + hamming_interval;
    
    m_bufferLine[i]=temp_bufferLines;
    //std::cout<< " >> buffer start " << bufferWindowStart << " buffer end " << bufferWindowEnd << std::endl;
    //std::cout << " size of VA " << m_bufferLine[0].getVertexCount() << std::endl;
    test_array.push_back(temp_bufferLines);
    
  }

  std::cout << " buffer line size " << m_bufferLine.size() << std::endl;
  std::cout << " test buffer lines size " << test_array[0].getVertexCount() << std::endl;
  
  std::vector<int> v_small;
  std::vector<int> v_big;

  for( int i =0; i < 100; i++ ){
    v_big.push_back(i);
  }

  int small_size=5;
  int number_of_div=v_big.size();
  int index = 0;
  int shift=0;
  //for( int i=0; i < number_of_div; i++ ){
    //std::cout << " on segment " << i << std::endl;
    //for( int j = 0; j < small_size; j++ ){
      //if( (i+j) == v_big.size() ) break;
      //std::cout << " >>  " << v_big[j + i] << std::endl;
  //}

  //}
    

  int windowX = 1000;
  int windowY = 1000;
  sf::Vector2i windowPos(0,0);
  
  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"DFT" );
  window.setPosition(windowPos);


  sf::Clock clock; // starts the clock
  
  int i = 0;
  double time2_elapsed=0;

  int tempt = 0;
  int deltat = 1;
  double tempt2=0.0;

  sf::Music music;
  //if (!music.openFromFile("/home/kuantumlad/Documents/projects/sfml-music/lvb-sym-5-1.wav")){
  if( !music.openFromFile("//Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav")) {
     std::cout << " ERROR LOADING MUSIC FILE " << std::endl;
    sf::sleep(sf::seconds(5));
    return -1; // error
  }
  music.play();


  int b = 0;
  sf::VertexArray temp_bufferLines(sf::LinesStrip,0);

  while(window.isOpen()){
    sf::Event event;

    while( window.pollEvent(event) ){

      
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
	music.stop();
      }
    }
    
    sf::Time elapsed1 = clock.getElapsedTime();
    double time_elapsed1 = elapsed1.asSeconds();
    //std::cout << elapsed1.asSeconds() << std::endl;

    //tempt=tempt+deltat;
    //std::cout << " >> " << tempt << std::endl;
    bool testtemp = tempt == 100000;
    //std::cout << " >> BOOLEAN TEST "<< testtemp << std::endl;
    //if( tempt == 10000 ){
    
    //std::cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> >> tempt  " << tempt << std::endl;
      //if( elapsed1.asSeconds() > duration ){
      //i=0;
      //}
      //clock.restart();
    
    //if ( i == m_bufferLine.size() ) i = 0;
      
      window.clear(sf::Color::Black);          

      
      
      //while ( i < 1000 ){
      b=0;
      while( b < 10000 ){
	double norm_sample_amp = (double)sample[shift+b]/(double)max_sample_amp * 100.0;
	temp_bufferLines.append( sf::Vector2f( b/10, 500 + (int)norm_sample_amp) );
	b++;
      }
      window.draw(temp_bufferLines);
      window.display();
      shift=shift+100;
      temp_bufferLines.clear();
      //}
      
      //std::cout << " buffer position " << m_bufferLine[i][0].position.x << " y pos " << m_bufferLine[i][0].position.y << std::endl;
      //window.draw(m_bufferLine[i]);
      //if( tempt == 1 ){	
      //	if( i < test_array.size() ){
      //	  std::cout << " draw " << i << std::endl;

      //  window.draw(test_array[i]);

      //}
      //else{
      //  i = 0;
      //}
      //tempt=0;
      //i++;
	//}
	
       
      //}
      //tempt++;


      
      //time2_elapsed=elapsed1.asSeconds();
    
          
  }

    
  
  return 0;

}
