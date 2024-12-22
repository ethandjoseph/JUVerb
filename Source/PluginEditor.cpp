#include "PluginProcessor.h"
#include "PluginEditor.h"

JUverbAudioProcessorEditor::JUverbAudioProcessorEditor (JUverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	dampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    freezeButton.setClickingTogglesState(true);
	drySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	wetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);

    roomSizeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	dampingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	widthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
	wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

	//roomSizeSlider.setTextValueSuffix("");
	//dampingSlider.setTextValueSuffix("");
	//widthSlider.setTextValueSuffix("");
	drySlider.setTextValueSuffix(" %");
	wetSlider.setTextValueSuffix(" %");

	roomSizeSliderLabel.setText("Room Size", juce::dontSendNotification);
	dampingSliderLabel.setText("Damping", juce::dontSendNotification);
	widthSliderLabel.setText("Width", juce::dontSendNotification);
	freezeButton.setButtonText("Freeze");
	drySliderLabel.setText("Dry", juce::dontSendNotification);
	wetSliderLabel.setText("Wet", juce::dontSendNotification);

	roomSizeSliderLabel.attachToComponent(&roomSizeSlider, false);
	dampingSliderLabel.attachToComponent(&dampingSlider, false);
	widthSliderLabel.attachToComponent(&widthSlider, false);
	drySliderLabel.attachToComponent(&drySlider, false);
	wetSliderLabel.attachToComponent(&wetSlider, false);

	freezeButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkorchid);

	addAndMakeVisible(roomSizeSlider);
	addAndMakeVisible(dampingSlider);
	addAndMakeVisible(widthSlider);
	addAndMakeVisible(freezeButton);
	addAndMakeVisible(drySlider);
	addAndMakeVisible(wetSlider);

	roomSizeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROOM_SIZE", roomSizeSlider);
	dampingSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DAMPING", dampingSlider);
	widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", widthSlider);
	freezeButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "FREEZE", freezeButton);
	drySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DRY", drySlider);
	wetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WET", wetSlider);

    setSize (880, 280);
}

JUverbAudioProcessorEditor::~JUverbAudioProcessorEditor()
{
}

void JUverbAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::darkorchid);
}

void JUverbAudioProcessorEditor::resized()
{
	auto area = getLocalBounds().reduced(40);
	int sliderWidth = area.getWidth() / 6;
	int sliderHeight = area.getHeight() - 20;
	
	roomSizeSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
	dampingSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
	widthSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
	freezeButton.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
	drySlider.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
	wetSlider.setBounds(area.removeFromLeft(sliderWidth).reduced(8));
}
