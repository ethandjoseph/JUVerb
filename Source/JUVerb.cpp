#include "JUVerb.h"

void JUVerb::reset()
{
	reverb.reset();
}

void JUVerb::prepare(juce::dsp::ProcessSpec spec)
{
	reverb.prepare(spec);
}

void JUVerb::setParameters(float size, float damping, float width, bool freeze, float dry, float wet)
{
	reverbParameters.roomSize = size;
	reverbParameters.damping = damping;
	reverbParameters.width = width;
	reverbParameters.freezeMode = freeze;
	reverbParameters.dryLevel = dry;
	reverbParameters.wetLevel = wet;
	reverb.setParameters(reverbParameters);
}

void JUVerb::process(juce::AudioBuffer<float>& buffer)
{
	juce::dsp::AudioBlock<float> block(buffer);
	juce::dsp::ProcessContextReplacing context (block);
	reverb.process(context);
}