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

  
  sf::RectangleShape getBar();
  

public:
  sf::RectangleShape bar;
  sf::Vector2f bar_size;
};

#endif
