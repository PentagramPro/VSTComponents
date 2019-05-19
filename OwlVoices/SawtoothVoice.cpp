#include "SawtoothVoice.h"
#include "VSTComponents/Owl/ProperiesRegistry.h"

CSawtoothVoice::CSawtoothVoice(const std::string & name, IVoiceModuleHost & host, double detuneScale) : CVoiceModuleBuffered(name,host)
, mDetuneScale(detuneScale)
{
	mDelay.Reset(GetSampleRate(), mPortamento);
}

void CSawtoothVoice::SetSamplesPerCycle(int samples)
{
	mNextSamplesPerCycle = samples;
	if (mCurrentSamplesPerCycle == 0) {
		mCurrentSamplesPerCycle = mNextSamplesPerCycle;
	}
}


void CSawtoothVoice::OnNoteStart(int midiNoteNumber, float velocity, SynthesiserSound *, int currentPitchWheelPosition)
{
	const double detune = (mDetune - 1)*mDetuneScale + 1;
	auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber)*detune;
	DBG("Sawtooth voice cycles per second: " << cyclesPerSecond);
	SetSamplesPerCycle(GetSampleRate() / cyclesPerSecond);

	StartSound();
}

void CSawtoothVoice::OnNoteStop(float velocity, bool allowTailOff)
{
	StopSound();
}

void CSawtoothVoice::ProcessBlock(AudioSampleBuffer & outputBuffer, int startSample, int numSamples)
{
	int samplesCount = numSamples;
	int currentSample = startSample;

	if (mCurrentSamplesPerCycle <= 0 && mNextSamplesPerCycle <= 0) {
		return;
	}

	mDelay.SetTransferTime(mPortamento);

	// === set up modulation ===
	std::function<double(double)> modulationFunction;

	if (mFrequencyModulator) {
		modulationFunction = [this](double currentSample) {
			const double fmVal = mFrequencyModulator->GetValue(currentSample);
			if (fmVal >= 0)
				return fmVal + 1;
			else
				return 1 / (-fmVal+1);
		};
	}
	else {
		modulationFunction = [](double currentSample) {
			return 1;
		};
	}

	// === main loop ===

	while (--samplesCount >= 0) {
		mSampleCounter++;
		double samplesPerCycleModulated = mCurrentSamplesPerCycle * modulationFunction(currentSample);

		if (mSampleCounter >= samplesPerCycleModulated) {
			mSampleCounter = mSampleCounter - samplesPerCycleModulated;
			mCurrentSamplesPerCycle = mDelay.Next(mNextSamplesPerCycle);
			
			samplesPerCycleModulated = mCurrentSamplesPerCycle * modulationFunction(currentSample);
		}
		else {
			mDelay.Next(mNextSamplesPerCycle);
		}

		double value = mSampleCounter / samplesPerCycleModulated;

		for (auto i = outputBuffer.getNumChannels(); --i >= 0;) {
			outputBuffer.addSample(i, currentSample, value);
		}
		currentSample++;
	}
}


void CSawtoothVoice::InitProperties(CPropertiesRegistry & registry)
{
	registry.AddProperty(GetPropName("Detune"), new CPropertyDouble01(mDetune, 1,1.02));
	registry.AddProperty(GetPropName("Portamento"), new CPropertyDouble01(mPortamento, 0.003,0.5));
}
