#ifndef HISTOGRAM_HH
#define HISTOGRAM_HH

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Bars.hh"
#include "VBars.hh"

class Histogram : public sf::Drawable, public sf::Transformable {

public:
  Histogram();
  ~Histogram();

  double bin_size;
  double bin_min;
  double bin_max;
  double start_bin_center;
  double end_bin_center;
  int nbins;
  std::string histo_type;

  std::map<int, VBars*> map_vdata;
  std::map<int,Bars*> map_data;
  std::vector<double> freq_ranges;

  void setNumberOfBins(int);
  void setBinRangeMax(double);
  void setBinRangeMin(double);
  void initHistogram(int,double,double,double,double);
  void initHistogram(int,double,double,double);
  void initHistogram(int,double,double,double, std::string);
  void setData(std::map<int,double>);
  void setBinContent(int, double);
  void setVBinContent(int, double);
  void setBinContentByRange(int, double);
  void setVBinContentByRange(int, double);
  void rebinContent(int);
  std::map<int, Bars*> getData();
  sf::RectangleShape getHistogram();
  void draw(sf::RenderTarget&, sf::RenderStates) const;

};

#endif
