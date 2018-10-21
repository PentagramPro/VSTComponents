
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
#include "Owl/IVoiceModule.h"
#include "Owl/IVoiceModuleHost.h"
#include "Owl/ListenerHandle.h"
#include "Owl/ListenerRegistry.h"
#include "Owl/ProperiesRegistry.h"
#include "Owl/SynthState.h"
#include "Owl/Toolbox.h"
#include "Owl/VoiceModuleBase.h"
#include "Owl/VoiceModuleHost.h"
#include "Owl/VoiceModuleHostSound.h"