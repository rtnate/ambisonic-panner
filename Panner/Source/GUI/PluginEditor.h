/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <LookAndFeel/RTLookAndFeel.h>
#include "Audio/PluginProcessor.h"
#include "Encoder/Source/PluginEditor.h"
#include "Decoder/Source/PluginEditor.h"
#include "ChannelMeterComponent.h"
#include "Common/PointSelection.h"
#include "GUI/MainPannerComponent.h"
//==============================================================================
/**
*/
class SpeakerSettingsComponent;

class AmbisonicPannerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             public juce::ChangeListener,
                                             public juce::ActionListener
{
public:
    AmbisonicPannerAudioProcessorEditor (AmbisonicPannerAudioProcessor& p);
    ~AmbisonicPannerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void updateBusLayout(const juce::AudioProcessor::BusesLayout&);
private:
    RTJuceGUI::CustomLookAndFeel lookAndFeel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AmbisonicPannerAudioProcessor& audioProcessor;
    std::unique_ptr<juce::TextButton> encoderButton;
    std::unique_ptr<juce::TextButton> decoderButton;
    std::unique_ptr<juce::TabbedComponent> tabs;
    std::unique_ptr<MainPannerComponent> mainPanner;
    std::unique_ptr<AmbisonicEncoderAudioProcessorEditor> encoderEditor;
    std::unique_ptr<AmbisonicsDecoderAudioProcessorEditor> decoderEditor;
    std::unique_ptr<SpeakerSettingsComponent> decoderSpeakerSettings;
    std::unique_ptr<ChannelMeterGroupComponent> meters;
    PointSelection pointSelection;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AmbisonicPannerAudioProcessorEditor)

    void showEncoderEditor();
    void showDecoderEditor();
    void changeListenerCallback(ChangeBroadcaster *src);
    void actionListenerCallback(const String& message) override;
    void updateMeteringSources();

    AudioMeterSource::TestSource testMeterSrc;
};
