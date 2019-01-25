#ifndef BARS_HH
#define BARS_HH

#include <SFML/Graphics.hpp>

class Bars{

public:
  Bars();
  ~Bars();
  
  void initBar(double,double,double,double,sf::Color);
  void setBarHeight(double);
  void setBarWidth(double);
  void setBarColor(std::vector<sf::Color>);
  void setBarCenterPosition(double, double);
  void updateBarSize();

  double getBarHeight();


  void initVBar(double,double,double,double,sf::Color);
  void setVBarHeight(double);
  void setVBarWidth(double);
  void setVBarColor(std::vector<sf::Color>);
  void setVBarCenterPosition(double, double);
  void updateVBarSize();

  
  sf::RectangleShape getBar();
  sf::VertexArray getVBar();
  

public:
  sf::RectangleShape bar;
  sf::Vector2f bar_size;
  
};

#endif
