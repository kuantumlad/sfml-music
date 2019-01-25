#ifndef VBARS_HH
#define VBARS_HH

#include <SFML/Graphics.hpp>

class VBars{

public:
  VBars();
  ~VBars();
  
  void initVBar(double,double,double,double,sf::Color);
  void setVBarHeight(double);
  void setVBarWidth(double);
  void setVBarColor(std::vector<sf::Color>);
  void setVBarCenterPosition(double, double);
  void updateVBarSize();

  double getVBarHeight();
  std::vector<sf::Vector2f> getVBarPosition();
  
  sf::VertexArray getVBar();
  

public:
  sf::VertexArray vbar;
  std::vector<sf::Vector2f> vbarpos;


};

#endif
