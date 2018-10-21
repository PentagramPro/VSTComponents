#include "VSTComponents.h"

#include "OwlDSP/CMultiChannelIir.cpp"
#include "OwlDSP/DSPDelay.cpp"
#include "OwlDSP/DSPIntegration.cpp"
#include "OwlDSP/DSPLowpassFilter2.cpp"

#include "Owl/AudioQueue.cpp"
#include "Owl/ProperiesRegistry.cpp"
#include "Owl/SynthState.cpp"
#include "Owl/Toolbox.cpp"
#include "Owl/VoiceModuleBase.cpp"
#include "Owl/VoiceModuleHost.cpp"