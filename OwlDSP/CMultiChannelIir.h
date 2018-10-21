#pragma once
#include "JuceHeader.h"

class CMultiChannelIir {
public:
	CMultiChannelIir(juce::IIRCoefficients& coefficients);

	void ProcessBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples);
private:

	std::vector<juce::IIRFilter> mIirFilters;
};