#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class JUverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JUverbAudioProcessorEditor (JUverbAudioProcessor&);
    ~JUverbAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUverbAudioProcessor& audioProcessor;
	juce::Slider roomSizeSlider;
	juce::Slider dampingSlider;
	juce::Slider widthSlider;
	juce::TextButton freezeButton;
	juce::Slider drySlider;
	juce::Slider wetSlider;

	juce::Label roomSizeSliderLabel;
	juce::Label dampingSliderLabel;
	juce::Label widthSliderLabel;
	juce::Label drySliderLabel;
	juce::Label wetSliderLabel;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> freezeButtonAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUverbAudioProcessorEditor)
};