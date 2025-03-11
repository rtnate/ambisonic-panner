#pragma once

#include <JuceHeader.h>
#include <Components/Fader.h>

class BasicModGroup : public juce::GroupComponent, public juce::ChangeBroadcaster
{
  public:
    using Fader = RTJuceGUI::Fader;
    using Label = juce::Label;

    class LFOSelection : public juce::ComboBox
    {
      public:
        LFOSelection() : juce::ComboBox()
        {
          addItem("LFO #1", 1);
          addItem("LFO #2", 2);
          addItem("LFO #3", 3);
          setSelectedId(1, dontSendNotification);
          setJustificationType(Justification::centred);
        };

        ~LFOSelection() override
        {

        }
    };

    enum FaderID {
      FaderModX = 0,
      FaderModY = 1,
      FaderModZ = 2,
      FaderModR = 3,
      FaderModRadial = 4,
      FaderModTilt = 5,
      NoFaders = 6
    };

    static constexpr char GroupTitle[] = "AutoPan Amount";

    BasicModGroup();

    ~BasicModGroup() override;

    void paint(juce::Graphics& g) override;

    void resized() override;

    void setFaderValue(FaderID faderId, float newValue,
      juce::NotificationType notify)
    {
      auto fader = m_faders[faderId];
      if (fader != nullptr) return fader->setValue(newValue, notify);
    }

    float getFaderValue(FaderID faderId) const noexcept
    {
      auto fader = m_faders[faderId];
      if (fader != nullptr) return fader->getValue();
      else return 0.f;
    }

    int getFaderLFOSelection(FaderID faderId)
    {
      auto combo = m_combos[faderId];
      if (combo != nullptr)
      {
        int val = combo->getSelectedId();
        if (val > 0) return val -1;
      }
      return -1;
    }

    void setFaderLFOSelection(FaderID faderId, int selectedId, 
      juce::NotificationType notify)
    {
      auto combo = m_combos[faderId];
      if (combo != nullptr)
      {
       combo->setSelectedId(selectedId + 1, notify);
      }
    }
  protected:
    juce::OwnedArray<Fader> m_faders;
    juce::OwnedArray<Label> m_labels;
    juce::OwnedArray<LFOSelection> m_combos;

    void initFaderWithLabel(FaderID faderId, juce::StringRef labelText);
};