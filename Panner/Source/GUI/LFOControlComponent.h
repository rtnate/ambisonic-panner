
#pragma once 

#include <JuceHeader.h>
#include "Components/Knob.h"
#include "Components/ControlGroupComponent.h"

class LFOSingleController : public juce::GroupComponent
{
  public:
    LFOSingleController(juce::String name);
    ~LFOSingleController() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

    void setRate(float rate, juce::NotificationType notify)
    {
      rateKnob->setValue(rate, notify);
    }

    void setWaveform(int waveform, juce::NotificationType notify)
    {
      auto wfi = waveform + 1;
      lfoWaveCombo->setSelectedId(wfi, notify);
    }

    float getRate() const noexcept {
      return (float)rateKnob->getValue();
    }

    int getWaveform() const noexcept
    {
      auto wfi = lfoWaveCombo->getSelectedId();
      if (wfi <= 0) return -1;
      else return wfi;
    }

    void setEnabled(bool toEnable, juce::NotificationType notify)
    {

    }

    bool getEnabled() const noexcept
    {
      return true;
    }
  protected: 
    std::unique_ptr<juce::Label> lfoLabel;
    std::unique_ptr<RTJuceGUI::Knob> rateKnob;
    std::unique_ptr<juce::Label> rateLabel;
    std::unique_ptr<juce::Label> lfoWaveLabel;
    std::unique_ptr<juce::ComboBox> lfoWaveCombo;
};

class LFOControlComponent : public juce::Component,
                            public juce::ChangeBroadcaster
{
  public:
    LFOControlComponent();
    ~LFOControlComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    LFOSingleController* getLfoController(int index)
    {
      return lfoControllers[index];
    }
  protected:
    OwnedArray<LFOSingleController> lfoControllers;
};