#pragma once

#include <memory>
#include "ofxAudioAnalysisClient.h"

namespace ofxAudioData {

struct ValiditySpec {
  ofxAudioAnalysisClient::AnalysisScalar scalar;
  bool isLessThan;
  float value;
};

class Processor {
public:
  Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_);
  void update();
  bool isDataValid(const std::vector<ValiditySpec>& validitySpec) const;
  float getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar);
  float* getScalarValuePtr(int scalar); // for Plots, via ofxHistoryPlot
  float getNormalisedScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar, float minValue, float maxValue, bool isLinear=true);
  inline auto& getMfcc() const { return audioAnalysisClientPtr->getMfcc(); };
  auto getNormalisedMfcc(float minValue, float maxValue) const;

private:
  float normalisedValue(float value, float minValue, float maxValue, bool isLinear) const;
  std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr;
};

}
