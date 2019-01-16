#ifndef SOUNDMANAGER_HH
#define SOUNDMANAGER_HH

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <complex>

class SoundManager{


public:
  SoundManager();
  ~SoundManager();

  void loadSound(const char*);
  void playSound();
  int getSampleCount();
  int getSampleRate();
  int getSampleDuration();
  int getMaxSampleValue();
  const sf::Int16* getSample();
  //std::vector<double> getNormalizedSamples();
  double* getNormalizedSamples();
  std::complex<double>* getComplexNormalizedSamples();
  
public:
  std::vector<double> normsamples;
  std::vector<int> samples;
  sf::SoundBuffer buffer;
  sf::Music music;
  
};
#endif
