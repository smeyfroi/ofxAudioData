#include "Processor.hpp"

namespace ofxAudioData {

Processor::Processor(std::shared_ptr<ofxAudioAnalysisClient::BaseClient> audioAnalysisClientPtr_) :
audioAnalysisClientPtr { audioAnalysisClientPtr_ }
{}

void Processor::update() {
  audioAnalysisClientPtr->update();
}

float Processor::getScalarValue(ofxAudioAnalysisClient::AnalysisScalar scalar) {
  return audioAnalysisClientPtr->getScalarValue(scalar);
}

}
