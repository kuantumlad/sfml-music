#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

int main(){


  //sf::SoundBuffer buffer;
  
  //if( !buffer.loadFromFile("//Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav") ){
    //if( !buffer.loadFromFile("/home/kuantumlad/Documents/projects/sfml-music/lvb-sym-5-1.wav") ){
    // std::cout << " could not load song from file " << std::endl;
  //}
  
  const int SAMPLES = 1000; // number of samples 
  const int SAMPLE_RATE = 5000;//441000;
  sf::Int16 raw[SAMPLES];
  double x = 0.0;
  double delta_t = 10.0;//3.0/4.0;
  //  const double increment = delta_t/SAMPLES;

  const double TWO_PI = 6.28318;
  const double increment = 1./(double)SAMPLE_RATE;//441000;
  //double x = 0;

  double div_t = 1000.0; // divide axis into 1000 points
  double freq = 45.0; // choose frequency between 0 to 1000. 
  double frequency_test = freq/div_t;//0.100;///100.0;//5;
    
  for (unsigned i = 0; i < SAMPLES; i++) {
    //double angle = TWO_PI * frequency_test * i/(double)SAMPLE_RATE;
    //double angle = TWO_PI*(double)i;
    double angle = TWO_PI * frequency_test * i;//
    raw[i] = 10.0 * sin(angle);
    x = x + increment;
    //std::cout << raw[i] << std::endl;
    std::cout << " X " << x << " raw " << raw[i] << std::endl;
  }

   sf::SoundBuffer buffer;
   if (!buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
     std::cerr << "Loading failed!" << std::endl;
     return 1;
   }

   //int sample_count = buffer.getSampleCount();
   //const sf::Int16 *sample = buffer.getSamples();

  int channel_count = buffer.getChannelCount();
  int sample_count_true=buffer.getSampleCount();
  int sample_count = buffer.getSampleCount();
  int sample_rate = buffer.getSampleRate();
  int duration = buffer.getDuration().asSeconds();

  const double pi = 3.141592658;
  
  double samplePerSeconds = (double)sample_count/(double)duration;
  double secondsPerSample = (double)duration/(double)sample_count;

  std::cout << " sample count " << sample_count << std::endl;
  std::cout << " seconds per sample " << secondsPerSample << std::endl;
  
  const sf::Int16 *sample = buffer.getSamples();
  
  /*int max_sample_amp = -1;
  int temp=-1;
  for( int b = 0; b < sample_count; b++ ){
  int raw_sample = sample[b];
  if( raw_sample > max_sample_amp ){
    max_sample_amp=raw_sample;           
   }
  }
  std::cout<< " normalize buffer samples by " << max_sample_amp << std::endl;
  // result: 29205
  */

  int max_sample_amp = 10.0; //29205;
  int hamming_interval = 100;
  sf::VertexArray bufferLines(sf::LinesStrip,100);//16324);
  int zeroLevel = 500;
  int compressFactor = 10;

  int numTimeWindows=sample_count;///16432;
  int hamming_length = 100;
  std::cout << " Number of time windows of 16432 buffer samples is " << numTimeWindows << std::endl;
  
  std::map<int, sf::VertexArray > m_bufferLine;
  
  int bufferWindowStart = 0;//sample_count_true/2;
  int bufferWindowEnd = 100;//hamming_interval;

  std::vector<sf::VertexArray> test_array;

  std::cout << " loading information " << std::endl;
  for( int i = bufferWindowStart; i < (bufferWindowStart + sample_count); i++ ){

   sf::VertexArray temp_bufferLines(sf::LinesStrip,0);
    int temp_counter=0;

    for( int b=0; b < hamming_length; b++){
      if( (i + b ) == sample_count ) continue;
      //  double norm_sample_amp = (double)sample[i+b]/(double)max_sample_amp * 100.0;
      //std::cout << " position "<<  temp_counter <<  " sample " <<  (double)sample[i+b] <<  " norm sample " << zeroLevel + norm_sample_amp << std::endl;

      //temp_bufferLines[temp_counter].position = sf::Vector2f( temp_counter, zeroLevel + (int)norm_sample_amp);
      //temp_bufferLines.append( sf::Vector2f( temp_counter/10, zeroLevel + (int)norm_sample_amp) );

      //std::cout << " >> position " << temp_bufferLines[temp_counter].position.x << " y pos "  << temp_bufferLines[temp_counter].position.y <<  std::endl;
      //temp_counter++;
      //std::cout << " >> on sample " << (i + b) << " " << temp_bufferLines.getVertexCount() << std::endl;
    }
    //bufferWindowStart=bufferWindowEnd;
    //bufferWindowEnd=bufferWindowEnd + hamming_interval;
    
    m_bufferLine[i]=temp_bufferLines;
    //std::cout<< " >> buffer start " << bufferWindowStart << " buffer end " << bufferWindowEnd << std::endl;
    //std::cout << " size of VA " << m_bufferLine[0].getVertexCount() << std::endl;
    test_array.push_back(temp_bufferLines);
    
  }

  //std::cout << " buffer line size " << m_bufferLine.size() << std::endl;
  //std::cout << " test buffer lines size " << test_array[0].getVertexCount() << std::endl;
  
  std::vector<int> v_small;
  std::vector<int> v_big;

  for( int i =0; i < 100; i++ ){
    v_big.push_back(i);
  }

  int small_size=5;
  int number_of_div=v_big.size();
  int index = 0;
  int shift=0;//100000;
  //for( int i=0; i < number_of_div; i++ ){
    //std::cout << " on segment " << i << std::endl;
    //for( int j = 0; j < small_size; j++ ){
      //if( (i+j) == v_big.size() ) break;
      //std::cout << " >>  " << v_big[j + i] << std::endl;
  //}

  //}
    
  int windowX = 500;
  int windowY = 500;
  sf::Vector2i windowPos(0,0);

  sf::VertexArray trueFreqLines(sf::LinesStrip,0);
  trueFreqLines.append( sf::Vector2f(frequency_test*div_t, 0) );
  trueFreqLines.append( sf::Vector2f(frequency_test*div_t, windowY) );

  sf::VertexArray timeLines(sf::LinesStrip,0);
  timeLines.append( sf::Vector2f(100, 0) );
  timeLines.append( sf::Vector2f(100, windowY) );

  sf::RenderWindow window( sf::VideoMode(windowX,windowY,32),"DFT" );
  window.setPosition(windowPos);

  sf::Clock clock; // starts the clock
  
  int i = 0;
  double time2_elapsed=0;

  int tempt = 0;
  int deltat = 1;
  double tempt2=0.0;

  //sf::Music music;
  //if (!music.openFromFile("/home/kuantumlad/Documents/projects/sfml-music/lvb-sym-5-1.wav")){
  //if( !music.openFromFile("//Users/bclary/Documents/work/codeprojects/music/lvb-sym-5-1.wav")) {
  // std::cout << " ERROR LOADING MUSIC FILE " << std::endl;
  //sf::sleep(sf::seconds(5));
  // return -1; // error
  // }
  //music.play();


  int b = 0;
  sf::VertexArray temp_bufferLines(sf::LinesStrip,0);
  sf::VertexArray temp_freqLines(sf::LinesStrip,0);
  
  sf::Sound Sound;
  Sound.setBuffer(buffer);
  Sound.setLoop(true);
  //while (1) {
  //sf::sleep(sf::milliseconds(100));
  //}
  //std::cin.get();
  Sound.play();
  

  while(window.isOpen()){
    sf::Event event;

    while( window.pollEvent(event) ){

      
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ){
	window.close();
	Sound.stop();
	//music.stop();
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
      std::vector< double > current_buffer;
      while( b <= SAMPLES ){//1000 ){
	double norm_sample_amp = (double)sample[shift+b];///(double)max_sample_amp;// *100.0;
	temp_bufferLines.append( sf::Vector2f( b, windowY/2 + norm_sample_amp) );// changed this from int to double //(int)norm_sample_amp) );
	current_buffer.push_back(norm_sample_amp);
	b++;
      }
      // output_data[y].re += input_data[x].re * ca - input_data[x].im * sa;
      
      for( int t1 = 0; t1 < 500; t1++ ){//current_buffer.size(); t1++ ){
	if( t1 >= current_buffer.size()/2 ) continue;
	double N = current_buffer.size();
	double sum_real = 0.0;
	double sum_img = 0.0;	
	for( int t2 = 0; t2 < 1000; t2++){//current_buffer.size(); t2++ ){
	  double real_cos = cos(2*pi*t1*t2/(N));
	  double img_sin = sin(2*pi*t1*t2/(N));


	  
	  //std::cout << " real cos " << real_cos << std::endl;
	  //std::cout << " img sin " << img_sin << std::endl;
	  
	  int x_in = current_buffer[t2];///10; //same size as matrix rows MUST BE!
	  double c_out_real = x_in * real_cos;
	  double c_out_img = -x_in * img_sin;
	  
	  sum_real=sum_real+c_out_real ;
	  sum_img=sum_img+c_out_img;
	  
	  
	}
	double amp = sqrt( pow(sum_real,2) + pow(sum_img,2) );
	temp_freqLines.append( sf::Vector2f(t1, windowY - (amp)/10.0) );
	//std::cout << " >> kth freq " << t1 << " amp " << amp<< std::endl;
      }

      window.draw(timeLines);
      window.draw(trueFreqLines);
      window.draw(temp_bufferLines);
      window.draw(temp_freqLines);
      window.display();
      shift=shift+1;
      temp_bufferLines.clear();
      temp_freqLines.clear();
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
