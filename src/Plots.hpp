#pragma once

#include "Processor.hpp"
#include "ofxHistoryPlot.h"
#include "ofxAudioAnalysisClient.h"

namespace ofxAudioData {

class Plots {
public:
  Plots(std::shared_ptr<ofxAudioData::Processor>, bool darkMode = true);
  void drawPlots(float width, float height);
  bool keyPressed(int key, int plotIndex);

private:
  std::shared_ptr<ofxAudioData::Processor> processorPtr;
  
  std::vector<std::unique_ptr<ofxHistoryPlot>> plots;
  std::vector<size_t> plotValueIndexes;
  std::unique_ptr<ofxHistoryPlot> makePlot(float* plottedValuePtr, std::string name, float low, float high);
  void resetPlots();
  void changePlot(size_t plotIndex, size_t valueIndex);
  bool plotsVisible;
  bool darkMode;

  std::array<float, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count)> minScalarValues {
    0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0
  };
  std::array<float, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count)> maxScalarValues {
    500, 5000, 25,
    25, 50, 1, 0.5, 50,
    500000, 20000, 20000, 20000, 1000000,
    4000
  };
  const std::array<std::string, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count)> scalarNames {
    "Root Mean Square", "Peak Energy", "Zero Crossing Rate",
    "SpectralCentroid", "Spectral Crest", "Spectral Flatness", "Spectral Rollof", "Spectral Kurtosis",
    "Energy Difference", "Spectral Difference", "Spectral Difference HWR", "Complex Spectral Difference", "High Frequency Content",
    "Pitch"
  };

};

}
