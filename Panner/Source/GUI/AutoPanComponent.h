
#pragma once 

#include <JuceHeader.h>
#include "Components/Knob.h"
#include "Components/Fader.h"
#include "BasicModGroup.h"
#include "Panner3DGroup.h"

class AutoPanComponent : public juce::Component, public juce::ChangeBroadcaster
{
  public:
    using KnobType = RTJuceGUI::Knob;
    using FaderType = RTJuceGUI::Fader;

    AutoPanComponent();
    ~AutoPanComponent();

    void paint(juce::Graphics &g) override;
    void resized() override;

    bool getAutoPanEnabledState()
    {
      return modEnabledButton->getToggleState();
    }

    void setAutoPanEnabledState(bool state, bool sendNotificaiton)
    {
      modEnabledButton->setToggleState(state, sendNotificaiton);
    }

    float getRateSetting()
    {
      return (float)quickRateKnob->getValue();
    }

    void setRateSetting(float rate, bool sendNotificaiton)
    {
      auto notify = sendNotificaiton ? juce::sendNotification : juce::dontSendNotification;
      quickRateKnob->setValue(rate, notify);
    }

    bool getDecoderTruncationEnabledState()
    {
      return decoderTruncateEnabled->getToggleState();
    }

    void setDecoderTruncationEnabledState(bool state, bool sendNotificaiton)
    {
      decoderTruncateEnabled->setToggleState(state, sendNotificaiton);
    }

    bool getEncoderTruncationEnabledState()
    {
      return encoderTruncateEnabled->getToggleState();
    }

    void setEncoderTruncationEnabledState(bool state, bool sendNotificaiton)
    {
      encoderTruncateEnabled->setToggleState(state, sendNotificaiton);
    }

    juce::Vector3D<float> getPanPosition()
    {
      return panner3d->getPanValue();
    }
    BasicModGroup& getModGroup()
    {
      jassert(modGroup);
      return *modGroup;
    }

  protected:
    std::unique_ptr<juce::Label> modEnabledLabel;
    std::unique_ptr<juce::ToggleButton> modEnabledButton;
    std::unique_ptr<KnobType> quickRateKnob;
    std::unique_ptr<juce::ToggleButton> decoderTruncateEnabled;
    std::unique_ptr<juce::ToggleButton> encoderTruncateEnabled;
    //std::unique_ptr<FaderType> testFader;
    std::unique_ptr<BasicModGroup> modGroup;
    std::unique_ptr<Panner3DGroup> panner3d;
};