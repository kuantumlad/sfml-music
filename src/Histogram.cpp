#include "../include/Histogram.hh"
#include "../include/Bars.hh"
#include "../include/VBars.hh"

#include <vector>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

Histogram::Histogram(){

  histo_type="rectangle";

}


Histogram::~Histogram(){
  
}

void Histogram::setNumberOfBins(int bins){

}

void Histogram::setBinRangeMax(double max){

}

void Histogram::setBinRangeMin(double min){

}


void Histogram::initHistogram(int bins, double x_start, double y_start, double min, double max, double x_scale, std::string temp_histo_type){

  double resolution = (max - min)/(double)bins;
  double x_norm = 1.0;
  //std::cout << " second init histo test " << resolution << std::endl;
  
  for( int b = 0 ; b < bins; b++ ){
    //std::cout << " freq " << b*resolution << std::endl;
    //std::cout << " bar position " << b*resolution/x_norm << std::endl;
    //Bars *bar = new Bars();

    freq_ranges.push_back( b*resolution );
    //bar->initBar( x_scale*(b*(resolution/x_norm)), 800.0, resolution*x_scale, 0.0, sf::Color::White);
    //if ( b == 20 ){
    //  bar->initBar( x_scale*(b*(resolution/x_norm)), 800.0,resolution*x_scale, 0.0, sf::Color::Red);
    //}
    //map_data[b] = bar;

    if( temp_histo_type == "rectangle" ){
      Bars *bar = new Bars();      
      bar->initBar( x_start + x_scale*(b*(resolution/x_norm)), y_start, resolution*x_scale, 0.0, getFreqColor(b*(resolution/x_norm)));//sf::Color::White);
      map_data[b] = bar;
    }
    else if( temp_histo_type == "vertexarray" ){
      VBars *vbar = new VBars();
      vbar->initVBar( x_start + x_scale*(b*(resolution/x_norm)), y_start, resolution*x_scale, 0.0, getFreqColor(b*(resolution/x_norm)));
      map_vdata[b] = vbar;
    }
  
  }

}


/*void Histogram::initHistogram(int bins, double sample_rate, double sample_buffer_window, double x_norm, double bin_resolution){

  //double resolution = (max - min)/(double)bins;
  double resolution = bin_resolution;//sample_rate/(4096.0 * x_norm);
  std::cout << " resl first " << resolution << std::endl;
  for( int b = 1; b <= bins; b++ ){

    double posx = (b*resolution/x_norm);
    
    Bars *bar = new Bars();
    bin_size = b*resolution;
    bar->initBar( ((b*resolution/x_norm)), 800.0, resolution/x_norm, 0.0, sf::Color::White);
    //if( b == 130 ) bar->initBar(b*(resolution)/x_norm, 800.0, resolution/x_norm, 0.0, sf::Color::Red);
    //if( b == 129 ) bar->initBar(b*(resolution)/x_norm, 800.0, resolution/x_norm, 0.0, sf::Color::Blue);

    map_data[b] = bar;

  }
}
*/

void Histogram::initHistogram(int bins, double sample_rate, double sample_buffer_window, double x_norm, double bin_resolution){

  double resolution = bin_resolution;//sample_rate/(4096.0 * x_norm);
  
  std::cout << " resl first " << resolution << std::endl;
  for( int b = 1; b <= bins; b++ ){

    double posx = (b*resolution/x_norm);    
    bin_size = b*resolution;
    Bars *bar = new Bars();      
    bar->initBar( ((b*resolution/x_norm)), 800.0, resolution/x_norm, 0.0, sf::Color::White);
    map_data[b] = bar;
  }
}


void Histogram::setData(std::map<int,double> data ){

  

}

void Histogram::setVBinContent( int freq_bin, double value_y ){

  map_vdata[freq_bin]->setVBarHeight(value_y);
  

}

void Histogram::setBinContent( int freq_bin, double value_y ){

  //std::cout << " setting freq " << freq_bin << " value " << value_y << std::endl;
  //std::cout << " current height is " << map_data[bin]->getBar().getPosition().y  << std::endl;
  map_data[freq_bin]->setBarHeight(value_y);
  //map_data[bin]->setBarWidth(value_x);
  //map_data[bin]->getBar().setPosition(sf::Vector2f(bin_size,value));
  //map_data[bin]->updateBarSize();
  //std::cout << " new height is " << map_data[bin]->getBar().getPosition().y  << std::endl;
  //std::cout << " map data size " << map_data.size() << std::endl;
  //std::cout << " freq range size " << freq_ranges.size() << std::endl;
  //for( int b = 0; b < freq_ranges.size(); ++b ){

  //if( freq_bin > freq_ranges[b] && freq_bin <= freq_ranges[b+1] ){
      //std::cout << " old height " << map_data[b]->getBarHeight() << " newcurrent height " << value_y << std::endl;
  //  if ( map_data[b]->getBarHeight() > value_y ){
  //	map_data[b]->setBarHeight(value_y);
  //   }
      //if( value_y < 790 ){	
	//std:: cout << " frequency " << freq_bin << " in range " << freq_ranges[b] << "  " << freq_ranges[b+1] << std::endl;
	//std::cout << " bin number " << b <<  " " << value_y << std::endl;
      //}
      
  //}
  //}
  
  
  
}


void Histogram::setBinContentByRange( int freq_bin, double value_y ){

  for( int b = 0; b < freq_ranges.size(); ++b ){    
    if( freq_bin > freq_ranges[b] && freq_bin <= freq_ranges[b+1] ){
      if ( map_data[b]->getBarHeight() > value_y ){
       	map_data[b]->setBarHeight(value_y);
      }
    }
  }  
}

void Histogram::setVBinContentByRange( int freq_bin, double value_y ){

  for( int b = 0; b < freq_ranges.size(); ++b ){    
    if( freq_bin > freq_ranges[b] && freq_bin <= freq_ranges[b+1] ){
      if ( map_vdata[b]->getVBarHeight() > value_y ){
       	map_vdata[b]->setVBarHeight(value_y);
      }
    }
  }  
}


void Histogram::rebinContent(int rebin_size ){

}

std::map<int,Bars*> Histogram::getData(){

  return map_data;

}

sf::Color Histogram::getFreqColor(double freq ){

  // 0 -   32 Range 1
  // 32 -  512 Range 2
  // 512 - 2048 Range 3
  // 2048 - 8192 Range 4
  // 8192 - 16384 Range 5

  sf::Color freq_color = sf::Color::White;
  
  if( freq <= 32 ){
    freq_color = sf::Color::White;
  }
  else if( freq > 32 && freq <= 512 ){
    freq_color = sf::Color::Blue;
  }
  else if( freq > 512 && freq <= 2048 ){
    freq_color = sf::Color::Green;
  }
  else if( freq > 2048 && freq <= 8192 ){
    freq_color = sf::Color::Magenta;    
  }
  else if( freq > 8192 && freq <= 16384 ){
    freq_color = sf::Color::Yellow;
  }
    
  return freq_color;

}


void Histogram::draw( sf::RenderTarget& target, sf::RenderStates states ) const {

  for( std::map<int, VBars*>::const_iterator it = map_vdata.begin(); it != map_vdata.end(); ++it ){
    target.draw((it->second)->getVBar());
  }

}


