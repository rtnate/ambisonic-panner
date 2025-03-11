
#pragma once 

#include <JuceHeader.h>
#include "Audio/PluginProcessor.h"
#include "GUI/AutoPanComponent.h"
#include "GUI/LFOControlComponent.h"

class MainPannerComponent : public juce::Component, public juce::ChangeListener
{
  public:
    MainPannerComponent(AmbisonicPannerAudioProcessor& ap);
    ~MainPannerComponent();

    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* src) override;
  protected:
    AmbisonicPannerAudioProcessor& proc;
    std::unique_ptr<juce::TabbedComponent> tabs;
    std::unique_ptr<LFOControlComponent> lfos;
    std::unique_ptr<AutoPanComponent> autopan;

    void syncParamsUpstream();
    void syncParamsDownstream();
};