#include "Panner3DGroup.h"

using namespace juce;
using namespace RTJuceGUI;

Panner3DGroup::Panner3DGroup() : juce::GroupComponent("autopan-3d-panner-group", "3D Panner")
{
  threeDPanner = std::make_unique<TwoDPannerWithHeight>();
  threeDPanner->onPanChange = [this]()
  {
    sendChangeMessage();
  };
  addAndMakeVisible(*threeDPanner);
}


Panner3DGroup::~Panner3DGroup()
{

}

void Panner3DGroup::paint(juce::Graphics& g)
{
  juce::GroupComponent::paint(g);
}

void Panner3DGroup::resized()
{
  auto bounds = getLocalBounds().toFloat();
  FlexBox fb(FlexBox::Direction::row,
    FlexBox::Wrap::noWrap,
    FlexBox::AlignContent::center,
    FlexBox::AlignItems::center,
    FlexBox::JustifyContent::center);
  jassert(threeDPanner);
  auto layoutBounds = bounds.reduced(10.f).withTrimmedTop(10.f);
  //auto square = jmin(layoutBounds.getHeight(), layoutBounds.getWidth()) - 10.f;
  FlexItem flexPanner(*threeDPanner);
  flexPanner.height = layoutBounds.getHeight();
  flexPanner.width = layoutBounds.getWidth();
  flexPanner.margin = 5.f;
  fb.items.add(flexPanner);
  fb.performLayout(layoutBounds);
}