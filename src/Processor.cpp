#include "Processor.hpp"

namespace ofxAudioData {

Processor::Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_) :
audioAnalysisClientPtr { audioAnalysisClientPtr_ }
{}

void Processor::update() {
  audioAnalysisClientPtr->update();
}

bool Processor::isDataValid() {
  return audioAnalysisClientPtr->getScalarValue(ofxAudioAnalysisClient::AnalysisScalar::rootMeanSquare) > 100 && audioAnalysisClientPtr->getScalarValue(ofxAudioAnalysisClient::AnalysisScalar::pitch) < 5000 && audioAnalysisClientPtr->getScalarValue(ofxAudioAnalysisClient::AnalysisScalar::pitch) > 50;
}

float Processor::getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar) {
  return audioAnalysisClientPtr->getScalarValue(scalar);
}

float Processor::getNormalisedScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar, float minValue, float maxValue, bool isLinear) {
  float value = getScalarValue(scalar);
  if (!isLinear) {
    value = std::log(value);
    minValue = std::log(minValue);
    maxValue = std::log(maxValue);
  }
  value = ofMap(value, minValue, maxValue, 0.0, 1.0);
  value = std::abs(value);
  return value - std::floor(value);
}

}
