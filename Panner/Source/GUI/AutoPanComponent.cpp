#include "AutoPanComponent.h"
#include "LookAndFeel/RTLookAndFeel.h"

AutoPanComponent::AutoPanComponent()
{
  modEnabledLabel = std::make_unique<juce::Label>();
  modEnabledLabel->setText("Auto Pan Enabled", dontSendNotification);
  modEnabledButton = std::make_unique<juce::ToggleButton>();
  modEnabledButton->setButtonText("Auto Pan Enabled");
  modEnabledButton->onStateChange = [this]()
  {
    this->sendChangeMessage();
  };
  addAndMakeVisible(*modEnabledButton);
  quickRateKnob = std::make_unique<KnobType>();
  auto &kn = *quickRateKnob;
  auto range = juce::NormalisableRange<double>(0.01, 10, 0.01, 0.25);
  kn.setNormalisableRange(range);
  kn.onValueChange = [this]()
  {
    this->sendChangeMessage();
  };


  addAndMakeVisible(kn);
  kn.showTickMarks(true);

  //testFader = std::make_unique<FaderType>();
  //auto &fader = *testFader;
  //auto faderRange = juce::NormalisableRange<double>(0, 100, 0.1);
  //fader.setNormalisableRange(range);
  //fader.setTextValueSuffix("%");
  //fader.onValueChange = [this]()
  //{
  //  this->sendChangeMessage();
  //};
  //addAndMakeVisible(fader);
  //fader.showTickMarks(true);

  modGroup = std::make_unique<BasicModGroup>();
  addAndMakeVisible(*modGroup);

  panner3d = std::make_unique<Panner3DGroup>();
  addAndMakeVisible(*panner3d);

  decoderTruncateEnabled = std::make_unique<juce::ToggleButton>();
  decoderTruncateEnabled->setButtonText("Decoder Trunc. Enabled");
  decoderTruncateEnabled->onStateChange = [this]()
  {
    this->sendChangeMessage();
  };
  addAndMakeVisible(*decoderTruncateEnabled);
  encoderTruncateEnabled = std::make_unique<juce::ToggleButton>();
  encoderTruncateEnabled->setButtonText("Encoder Trunc. Enabled");
  encoderTruncateEnabled->onStateChange = [this]()
  {
    this->sendChangeMessage();
  };
  addAndMakeVisible(*encoderTruncateEnabled);
}

AutoPanComponent::~AutoPanComponent()
{

}

void AutoPanComponent::paint(juce::Graphics& g)
{
  g.fillAll(RTJuceGUI::Colours::WarmWhite);
}

void AutoPanComponent::resized()
{
   //auto bounds = getLocalBounds();
   //auto buttonBounds = bounds.withRight(195).withBottom(35);
   //buttonBounds.translate(15, 15);
   //modEnabledButton->setBounds(buttonBounds);
   //juce::Rectangle<int> knobBounds(85, 105);
   //knobBounds.setPosition(buttonBounds.getBottomLeft());
   //knobBounds.translate(57, 20);
   //quickRateKnob->setTextBoxStyle(juce::Slider::TextBoxBelow, true, knobBounds.getWidth() - 2, 20);
   //quickRateKnob->setBounds(knobBounds);
   //juce::Rectangle<int> button2bounds(250, 35);
   //button2bounds.setPosition(bounds.getX(), knobBounds.getBottom());
   //button2bounds.translate(15, 15);
   //  encoderTruncateEnabled->setBounds(button2bounds);
   //  button2bounds.translate(0, 35 + 15);
   //decoderTruncateEnabled->setBounds(button2bounds);

   auto localBounds = getLocalBounds().toFloat();
   FlexBox topLayout;
   topLayout.flexDirection = FlexBox::Direction::row; 
   auto Padding = 5.0f;
   jassert(panner3d);
   jassert(modGroup);
   FlexItem flexPanner3d(*panner3d);
   flexPanner3d.flexGrow = 1.f;
   flexPanner3d.flexShrink = 1.f;
   flexPanner3d.height = localBounds.getHeight() * .67f;
   flexPanner3d.flexBasis = localBounds.getWidth() * .33f;
   flexPanner3d.margin = FlexItem::Margin(5.0f);
   FlexItem flexModControl(*modGroup);
   flexModControl.flexShrink = 2.f;
   flexModControl.flexGrow = 2.f;
   flexModControl.height = localBounds.getHeight() * .67f;
   flexModControl.flexBasis = localBounds.getWidth() * .67f;
   flexModControl.margin = FlexItem::Margin(5.0f);
   topLayout.items = {flexPanner3d, flexModControl};
   topLayout.performLayout(localBounds.withHeight(
      localBounds.getHeight() * .67f));
   FlexBox lowerFlex;
   lowerFlex.flexDirection = FlexBox::Direction::row;
   lowerFlex.justifyContent = FlexBox::JustifyContent::flexEnd;
   lowerFlex.alignItems = FlexBox::AlignItems::center;
   FlexItem buttonItem(*modEnabledButton);
   buttonItem.height = 35.f;
   buttonItem.width = 185.f;
   buttonItem.margin = 15.f;
   lowerFlex.items.add(buttonItem);
   lowerFlex.performLayout(localBounds.withTop(localBounds.getHeight() * .67f));
   //testFader->setTextBoxStyle(juce::Slider::TextBoxBelow, 
   //   true, faderBounds.getWidth() - 2, 20);
   //testFader->setBounds(faderBounds);
}
