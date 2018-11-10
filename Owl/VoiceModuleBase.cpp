#include "VoiceModuleBase.h"
#include "IVoiceModuleHost.h"

double CVoiceModuleBase::GetSampleRate() const
{
	return mHost->GetSampleRate();
}

std::string CVoiceModuleBase::GetPropName(const std::string & propertyName) const
  {
	return GetName() + "." + propertyName;
  }

  void CVoiceModuleBase::StartSound()
  {
	  mIsBusy = true;
  }

  void CVoiceModuleBase::StopSound()
  {
	  mIsBusy = false;
	  mHost->SoundEnded();
  }

  void CVoiceModuleBase::AddMuteRule(MutePredicate predicate)
  {
	  mMuteRules.push_back(predicate);
  }

  bool CVoiceModuleBase::IsMute() const
  {
	  for (auto& rule : mMuteRules) {
		  if (rule(*this)) {
			  return true;
		  }
	  }
	  return false;
  }

  void CVoiceModuleBase::ProcessBlockOfSound(juce::AudioSampleBuffer & outputBuffer, int startSample, int numSamples)
  {
	  if (IsMute()) {
		  return;
	  }
	  ProcessBlock(outputBuffer, startSample, numSamples);
  }