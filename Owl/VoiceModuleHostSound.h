#pragma once
#include "JuceHeader.h"

struct CVoiceModuleHostSound : public SynthesiserSound
{
    CVoiceModuleHostSound() {}
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};