#pragma once
#include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class JUVerb
{

public:
    JUVerb() {};

    ~JUVerb() {};

    void reset();

    void prepare(juce::dsp::ProcessSpec spec);

	void setParameters(float size, float damping, float width, bool freeze, float dry, float wet);

    void process(juce::AudioBuffer<float>& buffer);

private:
	juce::dsp::Reverb::Parameters reverbParameters;
	juce::dsp::Reverb reverb;
    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> wetBuffer;
	float size = 0.5;
	float damping = 0.5;
	float width = 1.0;
	bool freeze = false;
    float dry = 100.0;
    float wet = 50.0;
};