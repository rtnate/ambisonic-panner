#pragma once

#include <JuceHeader.h>

#include <Components/TwoDPannerWithHeight.h>


class Panner3DGroup : public juce::GroupComponent, public juce::ChangeBroadcaster
{
  public:
    Panner3DGroup();
    ~Panner3DGroup() override;

    void paint(juce::Graphics& g) override;

    void resized() override;

    juce::Vector3D<float> getPanValue()
    {
      jassert(threeDPanner);
      return threeDPanner->getPanValue();
    }
  protected:
    std::unique_ptr<RTJuceGUI::TwoDPannerWithHeight> threeDPanner;
};
