#pragma once

class IVoiceModuleHost {
public:
    virtual ~IVoiceModuleHost() {}
    virtual double GetSampleRate() const = 0;
    virtual void SoundEnded() = 0;
};