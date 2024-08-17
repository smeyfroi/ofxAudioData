#pragma once

#include <memory>
#include "ofxAudioAnalysisClient.h"

namespace ofxAudioData {

class Processor {
public:
  Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_);
  void update();
  float getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar);
  
private:
  std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr;
};

}
