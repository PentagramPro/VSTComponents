
/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 VSTComponents
  vendor:             PentagramPro
  version:            1.0.0
  name:               VSTComponents
  description:        VST stuff
  license:            GNU v3
  minimumCppStandard: 14

  dependencies:       juce_audio_basics, juce_audio_formats

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/
#include "OwlDSP/CMultiChannelIir.h"
#include "OwlDSP/DSPDelay.h"
#include "OwlDSP/DSPIntegration.h"
#include "OwlDSP/DSPLowpassFilter2.h"

#include "Owl/AudioQueue.h"
#include "Owl/IVoiceModuleBase.h"
#include "Owl/IVoiceModuleBuffered.h"
#include "Owl/VoiceModuleBuffered.h"
#include "Owl/IVoiceModuleRealtime.h"
#include "Owl/IVoiceModuleHost.h"
#include "Owl/ListenerHandle.h"
#include "Owl/ListenerRegistry.h"
#include "Owl/ProperiesRegistry.h"
#include "Owl/SynthState.h"
#include "Owl/Toolbox.h"
#include "Owl/VoiceModuleBase.h"
#include "Owl/VoiceModuleHost.h"
#include "Owl/VoiceModuleHostSound.h"
#include "Owl/SynthStateManager.h"
#include "Owl/ISynthStateManagerListener.h"

#include "OwlUI/IGuiListener.h"
#include "OwlUI/IIndicator.h"

#include "PresetBrowser/IPresetBrowserListeners.h"
#include "PresetBrowser/PresetBrowser.h"
#include "PresetBrowser/PresetBrowserImpl.h"
#include "PresetBrowser/PresetItemAdapter.h"

#include "OwlVoices/ControlVoltageSource.h"
#include "OwlVoices/DelayVoice.h"
#include "OwlVoices/EnvelopeVoice.h"
#include "OwlVoices/FilterVoice.h"
#include "OwlVoices/IVoltageController.h"
#include "OwlVoices/LfoOscillatorVoice.h"
#include "OwlVoices/LimiterVoice.h"
#include "OwlVoices/MixerVoice.h"
#include "OwlVoices/MultiModeOscillator.h"
#include "OwlVoices/NoiseVoice.h"
#include "OwlVoices/SawtoothVoice.h"