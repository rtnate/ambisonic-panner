/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once


#include "Encoder/Source/PluginProcessor.h"
#include "Decoder/Source/PluginProcessor.h"
#include "Audio/AudioMeterProcessor.h"
#include "Audio/AudioMeterParameterGroup.h"
#include "PanModulator.h"
#include "PanParameters.h"
#include <JuceHeader.h>
//==============================================================================
class AmbisonicPannerAudioProcessor  : public juce::AudioProcessor,
                                       public juce::ChangeBroadcaster,
                                       public juce::ActionListener,
                                       public SurroundPanProvider
{
public:
    enum StandardSpeakerSet
    {
      SpeakerSetMono, 
      SpeakerSetStereo,
      SpeakerSetLCR,
      SpeakerSetQuad,
      SpeakerSet5Dot1,
      SpeakerSet5Dot1Dot2,
      SpeakerSet5Dot1Dot4,
      SpeakerSet7Dot1,
      SpeakerSet7Dot1Dot2,
      SpeakerSet7Dot1Dot4,
      SpeakerSet7Dot1Dot6,
      SpeakerSet9Dot1Dot4,
      SpeakerSet9Dot1Dot6
    };
    //==============================================================================
    AmbisonicPannerAudioProcessor();
    ~AmbisonicPannerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void numChannelsChanged() override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //=================================================================
    AmbisonicEncoderAudioProcessor& getEncoder() {
      jassert(encoderProc);
      return *encoderProc;
    }

    AmbisonicsDecoderAudioProcessor& getDecoder() {
      jassert(decoderProc);
      return *decoderProc;
    }

    AudioMeterParameterGroup* getMeters()
    {
      return meterParams;
    }

    AudioMeterParameterGroupSourceSet& getMeterSources()
    {
      jassert(meterSources);
      return *meterSources;
    }

    void setSpeakerSet(StandardSpeakerSet speakerSet);


    AudioChannelSet& getSpeakerSet()
    {
      if (speakerSet == nullptr)
      {
        speakerSet = std::make_unique<AudioChannelSet>();
        setSpeakerSet(SpeakerSet7Dot1Dot4);
      }
      return *speakerSet;
    }

    const AmbiSpeakerSet* getAmbiSpeakerSet()
    {
      auto s = decoderProc->getSpeakerSet();
      return s;
    }

    void setMeteringEnabled(bool toEnable = true)
    {
      jassert(meterParams);
      auto enable = meterParams->getEnabled();
      if (enable != nullptr) *enable = toEnable;
    }

    void actionListenerCallback(const String& message);

    void setAutoPanEnabled(bool toEnable)
    {
      modEnabledFlag = toEnable;
    }

    bool getAutoPanEnabled()
    {
      return modEnabledFlag.get();
    }

    void setModRate(float rate)
    {
      panMod->getRotLFO().setFrequency(rate);
    }

    float getModRate()
    {
      return panMod->getRotLFO().getFrequency();
    }

    AutoPanParameters* getAutoPanParameters() noexcept
    {
      return autoPanParameters.get();
    }

    const AutoPanParameters* getAutoPanParameters() const noexcept
    {
      return autoPanParameters.get();
    }

    void setPanPositionBasis(SurroundPanValue pan)
    {
      autoPanStartX = pan.x;
      autoPanStartY = pan.y;
      autoPanStartZ = pan.z;
    }

    SurroundPanValue getPanPosition(int ch = 0)
    {
      float x = lastPanX.get();
      float y = lastPanY.get();
      float z = lastPanZ.get();
      return SurroundPanValue(x, y, z);
    }
    static constexpr float DefaultPanFreq = 2.f;
private:
    //==============================================================================
    std::unique_ptr<AmbisonicEncoderAudioProcessor> encoderProc;
    std::unique_ptr<AmbisonicsDecoderAudioProcessor> decoderProc;
    std::unique_ptr<AutoPanParameters> autoPanParameters;
    std::unique_ptr<juce::AudioBuffer<float>> intermediateBuffer;
    std::unique_ptr<juce::AudioBuffer<float>> panModBuffer;
    std::unique_ptr<AudioMeterProcessor<float>> meterProc;
    std::unique_ptr<PanModulator> panMod;
    AudioMeterParameterGroup* meterParams;
    std::unique_ptr<AudioMeterParameterGroupSourceSet> meterSources;
    std::unique_ptr<AudioChannelSet> speakerSet;
    juce::String activeSetName;
    juce::Atomic<bool> modEnabledFlag;

    juce::Atomic<float> lastPanX;
    juce::Atomic<float> lastPanY;
    juce::Atomic<float> lastPanZ;

    juce::Atomic<float> autoPanStartX;
    juce::Atomic<float> autoPanStartY;
    juce::Atomic<float> autoPanStartZ;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmbisonicPannerAudioProcessor)
    static constexpr int InternalMaxAmbisonicOrder = 7;

};
