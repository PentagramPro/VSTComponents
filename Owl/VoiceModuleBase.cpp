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
