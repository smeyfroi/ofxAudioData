#include "SpectrumPlots.hpp"

namespace ofxAudioData {

SpectrumPlots::SpectrumPlots(std::shared_ptr<ofxAudioData::Processor> processorPtr_, bool darkMode_) :
processorPtr(processorPtr_),
darkMode(darkMode_)
{}

bool SpectrumPlots::keyPressed(int key) {
  if (key == 'P') {
    plotsVisible = !plotsVisible;
    return true;
  } else if (key == 'p') {
    // Plots toggle
    plotsVisible = false;
    return true;
  } else {
    return false;
  }
}

void SpectrumPlots::createPlots() {
  if (!plots.empty()) return;
  size_t mfccCount = processorPtr->getMfcc().size();
  if (mfccCount == 0) return;
  plots.reserve(mfccCount);
  for (size_t i = 0; i < processorPtr->getMfcc().size(); i++) {
    float* valuePtr = const_cast<float*>(&processorPtr->getMfcc().data()[i]);
    std::string name = "mfcc " + ofToString(i);
    float maxHistory = ofGetWindowWidth() / 2;
    auto plotPtr = std::make_unique<ofxHistoryPlot>(valuePtr, name, maxHistory, true);
    if (!darkMode) {
      plotPtr->setColor(ofColor::black);
      plotPtr->setBackgroundColor(ofColor(0, 0));
      plotPtr->setGridColor(ofColor(240, 128));
    } else {
      plotPtr->setColor(ofColor::white);
    }
    plotPtr->setShowNumericalInfo(true);
    plotPtr->setRespectBorders(true);
    plotPtr->setDrawFromRight(true);
    plotPtr->setCropToRect(true);
    plotPtr->setShowSmoothedCurve(true); //plot a smoothed version of the values, but alos the original in lesser alpha
    plotPtr->setSmoothFilter(0.1); //smooth filter strength
//    plotPtr->update(0);
    plots.emplace_back(std::move(plotPtr));
  }
}

void SpectrumPlots::draw() {
  if (!plotsVisible) return;
  createPlots();
  float width = ofGetWindowWidth();
  float height = ofGetWindowHeight() / plots.size();
  for(int i = 0; i < plots.size(); i++) {
    plots[i]->draw(0, i*height, width, height);
  }
}

}
