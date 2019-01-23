#include "../include/Histogram.hh"
#include "../include/Bars.hh"

#include <vector>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

Histogram::Histogram(){


}


Histogram::~Histogram(){
  
}

void Histogram::setNumberOfBins(int bins){

}

void Histogram::setBinRangeMax(double max){

}

void Histogram::setBinRangeMin(double min){

}

void Histogram::initHistogram(int bins, double min, double max, double x_scale){

  double resolution = (max - min)/(double)bins;
  double x_norm = 1.0;
  //std::cout << " second init histo test " << resolution << std::endl;
  
  for( int b = 0 ; b < bins; b++ ){
    //std::cout << " freq " << b*resolution << std::endl;
    //std::cout << " bar position " << b*resolution/x_norm << std::endl;
    Bars *bar = new Bars();

    freq_ranges.push_back( b*resolution );
    bar->initBar( x_scale*(b*(resolution/x_norm)), 800.0, resolution*x_scale, 0.0, sf::Color::White);
    if ( b == 20 ){
      bar->initBar( x_scale*(b*(resolution/x_norm)), 800.0,resolution*x_scale, 0.0, sf::Color::Red);
    }
      
    map_data[b] = bar;
  }

}


void Histogram::initHistogram(int bins, double sample_rate, double sample_buffer_window, double x_norm, double bin_resolution ){

  //double resolution = (max - min)/(double)bins;
  double resolution = bin_resolution;//sample_rate/(4096.0 * x_norm);
  std::cout << " resl first " << resolution << std::endl;
  for( int b = 1; b <= bins; b++ ){

    double posx = (b*resolution/x_norm);
    
    Bars *bar = new Bars();
    std::cout << " BAR " << b << std::endl;
    std::cout << " bar resol " << resolution << std::endl;
    std::cout << " pos x " << posx << std::endl;
    std::cout << " pos y " << 10.0 << std::endl;
    std::cout << " width " << resolution/x_norm << std::endl;
    std::cout << " height " << 10.0 + 2.0*b << std::endl;

    bin_size = b*resolution;
    bar->initBar( ((b*resolution/x_norm)), 800.0, resolution/x_norm, 0.0, sf::Color::White);
    //if( b == 130 ) bar->initBar(b*(resolution)/x_norm, 800.0, resolution/x_norm, 0.0, sf::Color::Red);
    //if( b == 129 ) bar->initBar(b*(resolution)/x_norm, 800.0, resolution/x_norm, 0.0, sf::Color::Blue);

    map_data[b] = bar;

  }
}


void Histogram::setData(std::map<int,double> data ){

  

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



void Histogram::rebinContent(int rebin_size ){

  //for(

}

std::map<int,Bars*> Histogram::getData(){

  //std::map<int, Bars*> temp_map;
  return map_data;

}


void Histogram::draw( sf::RenderTarget& target, sf::RenderStates states ) const {

  //for( int b = 0; b < map_data.size(); b++ ){
  for( std::map<int, Bars*>::const_iterator it = map_data.begin(); it != map_data.end(); ++it ){
    target.draw((it->second)->getBar());
    
    //std::cout << " bar " << it->first << " height " << (it->second)->getBar().getPosition().y << std::endl;
    
  }

}


