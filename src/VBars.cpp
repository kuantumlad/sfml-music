#include "../include/VBars.hh"
#include <iostream>
#include <vector>

VBars::VBars(){


}


VBars::~VBars(){



}

void VBars::initVBar( double posx, double posy, double width, double height, sf::Color clr ){

  vbarpos.push_back( sf::Vector2f(posx,posy) );
  vbarpos.push_back( sf::Vector2f(posx+width,posy) );
  vbarpos.push_back( sf::Vector2f(posx+width,posy+height) );
  vbarpos.push_back( sf::Vector2f(posx,posy+height) );
  
  vbar.setPrimitiveType(sf::Quads);
  vbar.resize(4);

  vbar[0].position = sf::Vector2f(posx,posy);
  vbar[1].position = sf::Vector2f(posx+width,posy);
  vbar[2].position = sf::Vector2f(posx+width,posy+height);
  vbar[3].position = sf::Vector2f(posx,posy+height);
  
  vbar[0].color = clr;
  vbar[1].color = clr;
  vbar[2].color = sf::Color::Red;
  vbar[3].color = sf::Color::Red;

  
}

void VBars::setVBarHeight(double height){

  double vbar_x_left = vbarpos[0].x;
  double vbar_x_right = vbarpos[1].x;
  double vbar_y = vbarpos[2].y;

  vbar[2].position = sf::Vector2f( vbar_x_right, vbar_y + height);
  vbar[3].position = sf::Vector2f( vbar_x_left, vbar_y + height );

  
}

double VBars::getVBarHeight(){

  return vbar.getBounds().height;
  
}

sf::VertexArray VBars::getVBar(){

  return vbar;

}



