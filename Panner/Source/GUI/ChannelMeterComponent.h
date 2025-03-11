#pragma once

#include <JuceHeader.h>
#include <DataSources/AudioMeterSource.h>
#include <Components/AudioBarMeter.h>

class AmbiSpeakerSet;

class ChannelMeterComponent : public juce::Component
{
  public:
    enum Mode
    {
      BarMode = 0,
      DotMode = 1
    };

    ChannelMeterComponent(const juce::String& labelText);
    ChannelMeterComponent(const juce::String& name, const juce::String& labelText);
    ~ChannelMeterComponent() override;

    void resized() override;
    inline void setMeterSource(AudioMeterSource* src, int meterChannel = 0)
    {
      jassert(barMeter);
      barMeter->attachMeterSource(src, meterChannel);
    }

    inline void setLabelText(const juce::String& text, 
      juce::NotificationType notify)
    {
      jassert(label);
      label->setText(text, notify);
    }

    void setMode(Mode m)
    {
      mode = m;
    }

    Mode getMode() const {
      return mode;
    }

    void activateMeter(bool shouldActivate)
    {
      jassert(barMeter);
      barMeter->activate(shouldActivate);
    }
  protected:
    std::unique_ptr<AudioBarMeter> barMeter;
    std::unique_ptr<juce::Label> label;
    Mode mode;
    
};

class ChannelMeterGroupComponent : public juce::Component
{
  public:
    ChannelMeterGroupComponent();
    ~ChannelMeterGroupComponent() override;
    void setMeterSource(int meterIndex, AudioMeterSource* src);

    void setAllMetersSource(AudioMeterSource* src);

    ChannelMeterComponent* addMeterChannel(juce::StringRef name, 
      int channelIndex,
      AudioMeterSource* src = nullptr);

    void createMetersForChannelSet(const AudioChannelSet& chs, 
      int channeLimit = -1,
      AudioMeterSource* src = nullptr);

    void createMetersForSpeakerSet(const AmbiSpeakerSet* spkrs,
      int channeLimit = -1,
      AudioMeterSource* src = nullptr);

    bool isCollapsed() const {
      return m_isCollapsed;
    }

    void resized() override;
    void paint(juce::Graphics& g) override;

    int getDesiredHeight()
    {
      return isCollapsed() ? CollapseHeight : FullHeight;
    }
  protected:
    //========= Protected Types ================================
    class CollapseButton : public juce::ToggleButton
    {
      public:
        CollapseButton(ChannelMeterGroupComponent& p): 
          juce::ToggleButton("-"), parent(p){};

      protected:
        ChannelMeterGroupComponent& parent;
        void buttonStateChanged() override;
    };

    class EnableButton : public juce::ToggleButton
    {
    public:
      EnableButton(ChannelMeterGroupComponent& p) :
        juce::ToggleButton("On"), parent(p) {};

    protected:
      ChannelMeterGroupComponent& parent;
      void buttonStateChanged() override;
    };
    //========= Protected Members ================================
    static constexpr int FullHeight = 200;
    static constexpr int ItemPadding = 5;
    static constexpr int CollapseHeight = 40;
    static constexpr int CollapseItemHeight = CollapseHeight - (ItemPadding * 2);
    static constexpr int CollapseButtonSize = CollapseItemHeight;
    static constexpr int EnableButtonHeight = CollapseItemHeight;
    static constexpr int EnableButtonWidth = 50;
    juce::OwnedArray<ChannelMeterComponent> meters;
    std::unique_ptr<CollapseButton> collapseButton;
    std::unique_ptr<EnableButton> metersEnableButton;
    std::unique_ptr<juce::Label> enableLabel;

    //========= Protected Methods ================================
    void setCollapsedInternal(bool toCollapse)
    {
      m_isCollapsed = toCollapse;
      auto p = getParentComponent();
      if (p != nullptr) p->resized();
    }

    void setMetersEnabledInternal(bool toEnable)
    {
      m_metersEnabled = toEnable;
      auto p = getParentComponent();
      if (p != nullptr) p->resized();
    }

    void clearAndRemoveAllMeters();
    void addAndMakeVisibleAllMeters();
    //============================================================
  private:
    //========= Private Members ================================
    bool m_isCollapsed;
    bool m_metersEnabled;
};