#include "ChannelMeterComponent.h"
#include "Common/AmbiSpeakerSet.h"
using namespace juce;
//============== ChannelMeterComponent ========

ChannelMeterComponent::ChannelMeterComponent(const juce::String& labelText) :
  Component()
{
  barMeter = std::make_unique<AudioBarMeter>();
  label = std::make_unique<Label>();
  label->setText(labelText, dontSendNotification);
  label->setJustificationType(Justification::centred);
  addAndMakeVisible(*label);
  addAndMakeVisible(*barMeter);
}

ChannelMeterComponent::ChannelMeterComponent(const juce::String& name,
  const juce::String& labelText) : ChannelMeterComponent(labelText)
{
  setName(name);
}

ChannelMeterComponent::~ChannelMeterComponent()
{

}

void ChannelMeterComponent::resized()
{
  const int MaxMeterWidth = 20;
  const int MaxLabelWidth = 100;
  const int LabelHeight = 20;
  jassert(label);
  jassert(barMeter);
  auto bounds = getLocalBounds();
  if (mode == BarMode)
  { 
    auto labelWidth = bounds.getWidth() < MaxLabelWidth ? bounds.getWidth() : MaxLabelWidth;
    auto labelBounds = Rectangle<int>(labelWidth, LabelHeight);
    labelBounds.setCentre(bounds.getCentre());
    labelBounds.setY(bounds.getBottom() - LabelHeight);
    label->setBounds(labelBounds);
    auto meterWidth = bounds.getWidth() < MaxMeterWidth ? bounds.getWidth() : MaxMeterWidth;
    auto meterBounds = bounds.withBottom(labelBounds.getY());
    meterBounds = meterBounds.withSizeKeepingCentre(meterWidth, meterBounds.getHeight());
    barMeter->setBounds(meterBounds);
  } 
  else if (mode == DotMode)
  {
    auto labelWidth = bounds.getWidth() < MaxLabelWidth ? bounds.getWidth() : MaxLabelWidth;
    auto labelBounds = Rectangle<int>(labelWidth, LabelHeight);
    labelBounds.setCentre(bounds.getCentre());
    labelBounds.setY(bounds.getBottom() - LabelHeight);
    label->setBounds(labelBounds);
    auto meterWidth = bounds.getWidth() < MaxMeterWidth ? bounds.getWidth() : MaxMeterWidth;
    auto meterBounds = bounds.withBottom(labelBounds.getY());
    auto sq = jmin(meterWidth, meterBounds.getHeight());
    meterBounds = meterBounds.withSizeKeepingCentre(sq, sq);
    barMeter->setBounds(meterBounds);
  }
  /*else if (mode == DotMode)
  {
    auto maxRelWidth = bounds.getWidth() * 2 / 3;
    auto labelWidth = maxRelWidth < MaxLabelWidth ? maxRelWidth : MaxLabelWidth;
    auto labelHeight = LabelHeight < bounds.getHeight() ? LabelHeight : bounds.getHeight();
    auto labelBounds = Rectangle<int>(labelWidth, labelHeight);
    labelBounds.setPosition(bounds.getPosition());
    label->setBounds(labelBounds);
    auto meterWidth = bounds.getWidth() - labelBounds.getWidth();
    auto meterBounds = Rectangle<int>(meterWidth, meterWidth);
    auto center = bounds.getCentre();
    center.setX(bounds.getRight() - meterWidth);
    meterBounds.setCentre(center);
    barMeter->setBounds(meterBounds);
  }*/
}


//============== ChannelMeterGroupComponent ========
ChannelMeterGroupComponent::ChannelMeterGroupComponent()
{
  collapseButton = std::make_unique<CollapseButton>(*this);
  metersEnableButton = std::make_unique<EnableButton>(*this);
  m_isCollapsed = false;
  m_metersEnabled = true;
  collapseButton->setToggleState(m_isCollapsed, dontSendNotification);
  metersEnableButton->setToggleState(m_metersEnabled, dontSendNotification);
  enableLabel = std::make_unique<juce::Label>("Metering: ");
  addAndMakeVisible(*collapseButton);
  addAndMakeVisible(*metersEnableButton);
  addAndMakeVisible(*enableLabel);
}

ChannelMeterGroupComponent::~ChannelMeterGroupComponent()
{

}

void ChannelMeterGroupComponent::setMeterSource(
  int meterIndex, 
  AudioMeterSource* src)
{
  auto meter = meters[meterIndex];
  if (meter != nullptr) meter->setMeterSource(src);
}

void ChannelMeterGroupComponent::setAllMetersSource(
  AudioMeterSource* src)
{
  for (auto m : meters)
  {
    if (m != nullptr) m->setMeterSource(src);
  }
}

ChannelMeterComponent* ChannelMeterGroupComponent::addMeterChannel(
  juce::StringRef name,
  int channelIndex,
  AudioMeterSource* src)
{
  juce::String nameString = name;
  auto m = new ChannelMeterComponent(name);
  auto mAdded = meters.insert(channelIndex, m);
  if (mAdded != nullptr && src != nullptr)
    mAdded->setMeterSource(src, channelIndex);
  if (mAdded != nullptr) 
    addAndMakeVisible(*mAdded);
  return mAdded;
}

void ChannelMeterGroupComponent::createMetersForChannelSet(
  const AudioChannelSet& chs, 
  int channelLimit,
  AudioMeterSource* src)
{
  clearAndRemoveAllMeters();
  channelLimit = channelLimit < 0 ? chs.size() : channelLimit;
  for (int i = 0; i < chs.size(); i++)
  {
    auto type = chs.getTypeOfChannel(i);
    String name = chs.getAbbreviatedChannelTypeName(type);
    int chIndex = i;
    auto m = addMeterChannel(name, chIndex, src);
    if (i > channelLimit) m->activateMeter(false);
    else m->activateMeter(true);
  }
  //Add Inactive Channels
  //for (i; i < chs.size(); i++)
  //{
  //  AudioMeterSource* src = srcs != nullptr ? srcs->getSourceForChannel(i) : nullptr;
  //  auto type = chs.getTypeOfChannel(i);
  //  String name = chs.getChannelTypeName(type);
  //  auto m = addMeterChannel(name, src);
  //  m->activateMeter(false);
  //}
}

void ChannelMeterGroupComponent::createMetersForSpeakerSet(const AmbiSpeakerSet* spkrs,
  int channelLimit,
  AudioMeterSource* src)
{
  jassert(spkrs);
  clearAndRemoveAllMeters();
  channelLimit = channelLimit < 0 ? spkrs->size() : channelLimit;
  for (int i = 0; i < spkrs->size(); i++)
  {
    String name = spkrs->get(i)->getName();
    int chIndex = i;
    auto m = addMeterChannel(name, chIndex, src);
    if (i > channelLimit) m->activateMeter(false);
    else m->activateMeter(true);
  }
  resized();
}

void ChannelMeterGroupComponent::resized()
{

  Rectangle<int> collapseBounds(CollapseButtonSize, CollapseButtonSize);
  Rectangle<int> enableBounds(EnableButtonWidth, EnableButtonHeight);
  auto bounds = getLocalBounds();
  collapseBounds.setPosition(bounds.getPosition());
  collapseBounds.translate(ItemPadding, ItemPadding);
  jassert(collapseButton);
  collapseButton->setBounds(collapseBounds);
  enableBounds.setPosition(bounds.getTopRight());
  enableBounds.translate(-1 * (enableBounds.getWidth() + ItemPadding), ItemPadding);
  jassert(metersEnableButton);
  metersEnableButton->setBounds(enableBounds);
  Rectangle<int> meterLabelBounds(60, EnableButtonHeight);
  meterLabelBounds.setPosition(enableBounds.getPosition());
  meterLabelBounds.translate(-1 * meterLabelBounds.getWidth(), 0);
  enableLabel->setBounds(meterLabelBounds);
  if (!isCollapsed())
  {
    auto meterGroupBox = bounds.reduced(ItemPadding / 2, 0).withTop(CollapseButtonSize + ItemPadding * 2);
    auto meterBoxWidth = meterGroupBox.getWidth() / meters.size();
    Rectangle<int> meterBox(meterBoxWidth, meterGroupBox.getHeight());
    meterBox.setPosition(meterGroupBox.getPosition());
    for (int i = 0; i < meters.size(); i++)
    {
      auto meterBounds = meterBox.reduced(ItemPadding / 2, 0);
      auto meter = meters[i];
      jassert(meter);
      meter->setMode(ChannelMeterComponent::BarMode);
      meter->setBounds(meterBounds);
      meterBox.translate(meterBoxWidth, 0);
    }
  }
  else {
    auto meterGroupBox = bounds.withLeft(collapseBounds.getRight())
                               .withRight(meterLabelBounds.getX());
    auto meterBoxWidth = meterGroupBox.getWidth() / meters.size();
    Rectangle<int> meterBox(meterBoxWidth, meterGroupBox.getHeight());
    meterBox.setPosition(meterGroupBox.getPosition());
    for (int i = 0; i < meters.size(); i++)
    {
      auto meterBounds = meterBox.reduced(ItemPadding / 2, ItemPadding / 2);
      auto meter = meters[i];
      jassert(meter);
      meter->setMode(ChannelMeterComponent::DotMode);
      meter->setBounds(meterBounds);
      meterBox.translate(meterBoxWidth, 0);
    }
  }
  repaint();
}

void ChannelMeterGroupComponent::paint(juce::Graphics& g)
{
  auto color = findColour(ResizableWindow::backgroundColourId);
  g.fillAll(color);
}

void ChannelMeterGroupComponent::clearAndRemoveAllMeters()
{
  for (auto m : meters)
  {
    if (m != nullptr)
    {
      removeChildComponent(m);
    }
  }
  meters.clear(true);
}

void ChannelMeterGroupComponent::addAndMakeVisibleAllMeters()
{
  for (auto m : meters)
  {
    addAndMakeVisible(*m);
  }
}
//============== CollapseButton ====================
void ChannelMeterGroupComponent::CollapseButton::buttonStateChanged()
{
  ToggleButton::buttonStateChanged();
  if (getToggleState())
  {
    parent.setCollapsedInternal(true);
    setButtonText("+");
  }
  else {
    parent.setCollapsedInternal(false);
    setButtonText("-");
  }
}

void ChannelMeterGroupComponent::EnableButton::buttonStateChanged()
{
  ToggleButton::buttonStateChanged();
  if (getToggleState())
  {
    parent.setMetersEnabledInternal(true);
    setButtonText("On");
  }
  else {
    parent.setMetersEnabledInternal(false);
    setButtonText("Off");
  }
}