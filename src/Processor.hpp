#pragma once

#include <memory>
#include "ofxAudioAnalysisClient.h"

namespace ofxAudioData {

class Processor {
public:
  Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_);
  void update();
  bool isDataValid();
  float getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar);
  float* getScalarValuePtr(int scalar); // for Plots, via ofxHistoryPlot
  float getNormalisedScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar, float minValue, float maxValue, bool isLinear=true);

private:
  std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr;
};

}
