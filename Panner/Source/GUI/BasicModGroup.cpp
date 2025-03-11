#include "BasicModGroup.h"

using namespace juce;
using namespace RTJuceGUI;

BasicModGroup::BasicModGroup(): 
  juce::GroupComponent("autopan-basic-mod-group", GroupTitle)
{
  initFaderWithLabel(FaderModX, "Left/Right");
  initFaderWithLabel(FaderModY, "Front/Back");
  initFaderWithLabel(FaderModZ, "Height");
  initFaderWithLabel(FaderModRadial, "Spin");
  initFaderWithLabel(FaderModTilt, "Tilt");
  initFaderWithLabel(FaderModR, "PingPong");
}

BasicModGroup::~BasicModGroup()
{

}

void BasicModGroup::paint(juce::Graphics& g)
{
  GroupComponent::paint(g);
}

void BasicModGroup::resized()
{
  auto flexBounds = getLocalBounds().toFloat().reduced(10.f, 20.f);
  flexBounds.translate(0., 0.f);
  FlexBox fb;
  fb.flexDirection = FlexBox::Direction::row;
  fb.flexWrap = FlexBox::Wrap::noWrap;
  fb.justifyContent = FlexBox::JustifyContent::center;
  fb.alignContent = FlexBox::AlignContent::center;
  fb.alignItems = FlexBox::AlignItems::center;
  constexpr float Padding = 5.f;
  auto itemHeight = flexBounds.getHeight();
  auto itemBoxWidth = flexBounds.getWidth() / NoFaders;
  auto itemWidth = itemBoxWidth - (Padding * 2.f);
  ////Manual Version 
  //auto itemBounds = juce::Rectangle<float>(itemBoxWidth, itemHeight);
  //auto faderBounds = itemBounds.withWidth(itemWidth).translated(Padding, 0);
  //for (int i = 0; i < NoFaders; i++)
  //{
  //  auto fader = m_faders[i];
  //  jassert(fader);
  //  fader->setBounds(faderBounds.toNearestInt());
  //  faderBounds.translate(itemBoxWidth, 0);
  //}
  OwnedArray<FlexBox> localFlex;
  FlexBox fbLocalRef;
  fbLocalRef.flexDirection = FlexBox::Direction::column;
  fbLocalRef.flexWrap = FlexBox::Wrap::noWrap;
  fbLocalRef.justifyContent = FlexBox::JustifyContent::spaceBetween;
  fbLocalRef.alignContent = FlexBox::AlignContent::center;
  fbLocalRef.alignItems = FlexBox::AlignItems::center;
  for (int i = 0; i < NoFaders; i++)
  {
    FlexBox* fbLoc = localFlex.add(new FlexBox());
    *fbLoc = fbLocalRef;
    auto label = m_labels[i];
    jassert(label);
    FlexItem flexLabel(*label);
    flexLabel.height = 18.f;
    flexLabel.width = itemWidth - 2.f;

    auto combo = m_combos[i];
    jassert(combo);
    FlexItem flexCombo(*combo);
    flexCombo.height = 18.f;
    flexCombo.width = jmin((float)itemWidth - 2.f, 75.f);
    auto fader = m_faders[i];
    jassert(fader);
    FlexItem flexFader(*fader);
    flexFader.height = itemHeight - flexLabel.height - flexCombo.height - 6.f;
    flexFader.width = jmin((float)itemWidth - 1.f, 85.f);
    FlexItem flexPad;
    flexPad.width = itemWidth - 2.f;
    flexPad.height = 6.f;
    fbLoc->items.add(flexLabel, flexFader, flexPad, flexCombo);
    FlexItem group(*fbLoc);
    group.height = itemHeight;
    group.width = itemWidth;
    fb.items.add(group);
  }
  fb.performLayout(flexBounds);
}

void BasicModGroup::initFaderWithLabel(FaderID faderId,
  juce::StringRef labelText)
{
  jassert(faderId <= NoFaders);
  if (faderId >= NoFaders) return;

  auto fader = new Fader();
  fader->setNormalisableRange({0., 100., 1,});
  fader->setValue(0., dontSendNotification);
  fader->setDoubleClickReturnValue(true, 0.);
  fader->setTextBoxStyle(Slider::TextBoxBelow, true, 120.f, 18.f);
  fader->setTextValueSuffix("%");
  auto label = new Label();
  label->setText(labelText, dontSendNotification);
  label->setJustificationType(Justification::centred);
  label->setFont(Font(16.f));
  auto lfo_select = new LFOSelection();
  auto c = m_combos.insert((int)faderId, lfo_select);
  jassert(c);
  c->onChange = [this](){ this->sendChangeMessage(); };
  addAndMakeVisible(*c);
  auto f = m_faders.insert((int)faderId, fader);
  jassert(f);
  f->onValueChange = [this](){ this->sendChangeMessage(); };
  addAndMakeVisible(*f);
  auto l = m_labels.insert((int)faderId, label);
  addAndMakeVisible(*l);
}