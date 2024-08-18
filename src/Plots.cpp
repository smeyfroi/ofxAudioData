#include "Plots.hpp"

namespace ofxAudioData {

Plots::Plots(std::shared_ptr<ofxAudioData::Processor> processorPtr_, bool darkMode_) :
processorPtr(processorPtr_),
darkMode(darkMode_)
{
  plots.resize(4);
  plotValueIndexes.resize(4);
  changePlot(0, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::peakEnergy));
  changePlot(1, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::spectralCentroid));
  changePlot(2, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::highFrequencyContent));
  changePlot(3, static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::pitch));
}

ofxHistoryPlot* Plots::makePlot(float* plottedValuePtr, std::string name, float low, float high) {
  float numSamples = ofGetWindowWidth() / 2;
  ofxHistoryPlot* plotPtr = new ofxHistoryPlot(plottedValuePtr, name, numSamples, true);
  if (low != 0.0 || high != 0.0) {
//    plotPtr->setLowerRange(low);
    plotPtr->setRange(low, high);
  }
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
  plotPtr->update(0);
  return plotPtr;
}

void Plots::resetPlots() {
  for (const auto& plotPtr : plots) {
    plotPtr->reset();
  }
}

void Plots::changePlot(size_t plotIndex, size_t valueIndex) {
  plots[plotIndex] = std::unique_ptr<ofxHistoryPlot>(makePlot(processorPtr->getScalarValuePtr(valueIndex), scalarNames[valueIndex], minScalarValues[valueIndex], maxScalarValues[valueIndex]));
  plotValueIndexes[plotIndex] = valueIndex;
}

void Plots::drawPlots(float width, float height) {
  if (!plotsVisible) return;
  for(int i = 0; i < 4; i++) {
    plots[i]->draw(0, i * height, width, height);
  }
}

bool Plots::keyPressed(int key, int plotIndex) {
  if (key == '<') {
    changePlot(plotIndex, (plotValueIndexes[plotIndex]+1) % static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count));
    resetPlots();
  } else if (key == '>') {
    changePlot(plotIndex, (plotValueIndexes[plotIndex]-1+static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count)) % static_cast<int>(ofxAudioAnalysisClient::AnalysisScalar::_count));
    resetPlots();
  } else if (key == 'p') {
    plotsVisible = !plotsVisible;
  } else {
    return false;
  }
  return true;
}

}
