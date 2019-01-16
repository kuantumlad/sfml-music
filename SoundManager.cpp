#include "SoundManager.hh"
#include <vector>
#include <iostream>

SoundManager::SoundManager(){

}


SoundManager::~SoundManager(){


}


void SoundManager::loadSound(const char* infile){

  if( !buffer.loadFromFile(infile) ){
    std::cout << " could not load song from file " << std::endl;
  }

  if( !music.openFromFile(infile) ){
    std::cout << " could not load and play song from file " << std::endl;
  }   

  
}

void SoundManager::playSound(){


  music.play();

}

const sf::Int16* SoundManager::getSample(){

  return buffer.getSamples();

}

double* SoundManager::getNormalizedSamples(){
  
  int norm = getMaxSampleValue();
  const sf::Int16* sample = buffer.getSamples();

  static double* temp_sample = new double[getSampleCount()];
  
  for( int s = 0; s < getSampleCount(); s++ ){    
    temp_sample[s] = (double)sample[s]/(double)norm ;   
  }

  return temp_sample;
}

std::complex<double>* SoundManager::getComplexNormalizedSamples(){
  
  int norm = getMaxSampleValue();
  const sf::Int16* sample = buffer.getSamples();

  static std::complex<double>* temp_sample = new std::complex<double>[getSampleCount()]; 
  for( int s = 0; s < getSampleCount(); s++ ){    
    temp_sample[s] = (double)sample[s]/(double)norm ;   
  }
  return temp_sample;
}



int SoundManager::getSampleCount(){

  return buffer.getSampleCount();
  
}

int SoundManager::getSampleRate(){

  return buffer.getSampleRate();

}

int SoundManager::getSampleDuration(){

  return buffer.getDuration().asSeconds();

}

int SoundManager::getMaxSampleValue(){

  const sf::Int16* sample = buffer.getSamples();
  
  int max_sample_amp = -1;
  int temp=-1;
  for( int b = 0; b < getSampleCount(); b++ ){
    int raw_sample = sample[b];
    if( raw_sample > max_sample_amp ){
      max_sample_amp=raw_sample;           
    }
  }

  return max_sample_amp;

}

