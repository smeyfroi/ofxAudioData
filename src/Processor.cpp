#include "Processor.hpp"
#include "ofUtils.h"

namespace ofxAudioData {

Processor::Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_) :
audioAnalysisClientPtr { audioAnalysisClientPtr_ }
{}

void Processor::update() {
  audioAnalysisClientPtr->update();
}

bool Processor::isDataValid(const std::vector<ValiditySpec>& sampleValiditySpecs) const {
  for (const auto& spec : sampleValiditySpecs) {
    if (spec.isLessThan && audioAnalysisClientPtr->getScalarValue(spec.scalar) > spec.value) return false;
    if (!spec.isLessThan && audioAnalysisClientPtr->getScalarValue(spec.scalar) < spec.value) return false;
  }
  return true;
}

float Processor::getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar) {
  return audioAnalysisClientPtr->getScalarValue(scalar);
}

float* Processor::getScalarValuePtr(int scalar) {
  return audioAnalysisClientPtr->getScalarValuePtr(scalar);
}

float Processor::normalisedValue(float value, float minValue, float maxValue, bool isLinear) const {
  if (!isLinear) {
    value = std::log(value);
    minValue = std::log(minValue);
    maxValue = std::log(maxValue);
  }
  value = ofMap(value, minValue, maxValue, 0.0, 1.0);
  value = std::abs(value);
  return value - std::floor(value); // wrap around
}

float Processor::getNormalisedScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar, float minValue, float maxValue, bool isLinear) {
  return normalisedValue(getScalarValue(scalar), minValue, maxValue, isLinear);
}

auto Processor::getNormalisedMfcc(float minValue, float maxValue) const {
  std::vector<float> result;
  for (float mfccValue : getMfcc()) {
    result.push_back(normalisedValue(mfccValue, minValue, maxValue, false));
  }
  return result;
}

}
