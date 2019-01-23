#include "../include/Bars.hh"
#include <vector>
#include <map>
#include <iostream>


Bars::Bars(){


}


Bars::~Bars(){



}


void Bars::initBar( double posx, double posy, double width, double height, sf::Color clr ){

  bar.setPosition(posx,posy);
  bar.setSize(sf::Vector2f(width,height));
  bar.setFillColor(clr);

}


void Bars::setBarHeight(double height){

  //bar_size.y = height;
  double bar_x  = getBar().getLocalBounds().width;
  //std::cout << " bar x " << bar_x << std::endl;
  bar.setSize( sf::Vector2f(bar_x, height) );
  //bar.getLocalBounds().height = height;

}


void Bars::setBarWidth(double width){

  bar_size.x = width;
  double bar_y  = getBar().getPosition().y;
  //std::cout << " bar x " << bar_x << std::endl;
  bar.setSize( sf::Vector2f(width, bar_y) );

  
}

double Bars::getBarHeight(){

  //std::cout << " bar height " << bar.getPosition().y << std::endl;
  return bar.getLocalBounds().height;
}


void Bars::setBarColor(std::vector<sf::Color> color){


}

void Bars::setBarCenterPosition(double x, double y ){



}

void Bars::updateBarSize(){

  bar.setSize(bar_size);

}

sf::RectangleShape Bars::getBar(){

  
  return bar;

}
