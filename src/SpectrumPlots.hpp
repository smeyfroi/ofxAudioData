#pragma once

#include "Processor.hpp"
#include "ofxHistoryPlot.h"

namespace ofxAudioData {

class SpectrumPlots {
public:
  SpectrumPlots(std::shared_ptr<ofxAudioData::Processor>, bool darkMode = true);
  bool keyPressed(int key);
  void draw();

private:
  std::shared_ptr<ofxAudioData::Processor> processorPtr;
  std::vector<std::unique_ptr<ofxHistoryPlot>> plots;
  
  void createPlots();

  bool plotsVisible;
  bool darkMode;

};

}
