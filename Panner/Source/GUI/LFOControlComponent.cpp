#include "LFOControlComponent.h"
#include "Audio/LFO.h"
#include "LookAndFeel/RTLookAndFeel.h"

using namespace juce;
using namespace RTJuceGUI;

LFOSingleController::LFOSingleController(juce::String name) : juce::GroupComponent()
{
  constexpr wchar_t space = L'\x20';
  String cmpName = name.toLowerCase().replaceCharacter(space, '_');
  cmpName = "lfo-controller-" + cmpName;
  setName(cmpName);
  lfoLabel = std::make_unique<juce::Label>();
  lfoLabel->setText(name, dontSendNotification);
  lfoLabel->setJustificationType(Justification::centred);
  rateKnob = std::make_unique<Knob>();
  rateKnob->setRange(0.01, 10, 0.01);
  rateLabel = std::make_unique<juce::Label>();
  rateLabel->setText("Rate: ", dontSendNotification);
  rateLabel->setJustificationType(Justification::centred);
  lfoWaveLabel = std::make_unique<juce::Label>();
  lfoWaveLabel->setText("Wave Type: ", dontSendNotification);
  lfoWaveLabel->setJustificationType(Justification::centred);
  lfoWaveCombo = std::make_unique<juce::ComboBox>();
  lfoWaveCombo->addItem("Sine", LFO::WaveTypeSine + 1);
  lfoWaveCombo->addItem("Triangle", LFO::WaveTypeTriangle + 1);
  lfoWaveCombo->addItem("Square", LFO::WaveTypeSquare + 1);
  lfoWaveCombo->addItem("Sawtooth", LFO::WaveTypeSawtooth + 1);
  rateKnob->setTextBoxStyle(Slider::TextBoxBelow, true, 100.f,
    14 + 2);
  setText(name);
  //addAndMakeVisible(*lfoLabel);
  addAndMakeVisible(*rateKnob);
  addAndMakeVisible(*rateLabel);
  addAndMakeVisible(*lfoWaveLabel);
  addAndMakeVisible(*lfoWaveCombo);
}

LFOSingleController::~LFOSingleController()
{

}

void LFOSingleController::paint(juce::Graphics& g)
{
  auto background = findColour(ResizableWindow::ColourIds::backgroundColourId);
  g.setColour(background);
  g.fillRoundedRectangle(getLocalBounds().toFloat(), 5.0f);
  GroupComponent::paint(g);
}

void LFOSingleController::resized()
{
  static constexpr float KnobRadius = 25.f; 
  auto bounds = getLocalBounds().toFloat();
  Font mainLabelFont(18.f);
  Font labelFont(17.f);
  Font detailFont(16.f);
  const float ComboWidth = detailFont.getStringWidthFloat("Long Text Here");
  lfoLabel->setFont(mainLabelFont);
  rateLabel->setFont(labelFont);
  lfoWaveLabel->setFont(labelFont);


  if (getWidth() > getHeight())
  {
    //Horizontal Layout
    Rectangle<float> controlBox;
    Rectangle<float> titleBox;
    FlexBox fbMain;
    fbMain.flexWrap = FlexBox::Wrap::noWrap;
    fbMain.flexDirection = FlexBox::Direction::row;
    fbMain.justifyContent = FlexBox::JustifyContent::center;
    fbMain.alignContent = FlexBox::AlignContent::center;
    fbMain.alignItems = FlexBox::AlignItems::center;
    FlexBox fbRate;
    fbRate.flexWrap = FlexBox::Wrap::noWrap;
    fbRate.flexDirection = FlexBox::Direction::column;
    fbRate.justifyContent = FlexBox::JustifyContent::center;
    fbRate.alignContent = FlexBox::AlignContent::center;
    fbRate.alignItems = FlexBox::AlignItems::center;
    FlexBox fbWaveForm = fbRate;
    fbWaveForm.justifyContent = FlexBox::JustifyContent::center;
    //Rate
    FlexItem flexRateLabel(*rateLabel);
    flexRateLabel.height = labelFont.getHeight() + 8;
    flexRateLabel.minWidth = 100.f;
    FlexItem flexRateControl(*rateKnob);
    flexRateControl.height = 90.f;
    flexRateControl.width = 75.f;
    fbRate.items.add(flexRateLabel, flexRateControl);
    //WaveForm 
    FlexItem flexWaveLabel(*lfoWaveLabel);
    flexWaveLabel.height = labelFont.getHeight() + 8;
    flexWaveLabel.minWidth = 100.f;
    FlexItem flexWaveCombo(*lfoWaveCombo);
    flexWaveCombo.height = detailFont.getHeight() + 6;
    flexWaveCombo.width = ComboWidth;
    fbWaveForm.items.add(flexWaveLabel, flexWaveCombo);
    auto flexBounds = bounds.reduced(10., 15.);
    fbMain.items.add(
      FlexItem(fbRate).withHeight(flexBounds.getHeight())
                      .withMinWidth(flexBounds.getWidth() / 2.),
      FlexItem(fbWaveForm).withHeight(flexBounds.getHeight())
                          .withMinWidth(flexBounds.getWidth() / 2.));
    fbMain.performLayout(bounds.reduced(10., 15.));

/*
    if (bounds.getHeight() > (mainLabelFont.getHeight() + 2.) * 3)
    {
      auto titleWidth = mainLabelFont.getStringWidthFloat(lfoLabel->getText());
      titleBox = bounds.withRight(titleWidth + 3.)
                       .withBottom(mainLabelFont.getHeight() + 2.f);
      controlBox = bounds.withTop(titleBox.getBottom());
    }
    else
    {
      auto titleWidth = mainLabelFont.getStringWidthFloat(lfoLabel->getText());
      titleBox = bounds.withRight(titleWidth + 3.);
      controlBox = bounds.withLeft(titleBox.getRight());
    }
    lfoLabel->setBounds(titleBox.toNearestInt());
    auto knobKnobBox = Rectangle<float>(KnobRadius * 2. + 5.,  
      KnobRadius * 2. + 5.);
    auto knobGroupBox = Rectangle<float>(knobKnobBox.getWidth() + 4.f, 
      controlBox.getHeight());
    auto comboGroupBox = Rectangle<float>(ComboWidth + 4.f,
      controlBox.getHeight());

    auto emtpySpace = controlBox.getWidth() - knobGroupBox.getWidth() 
                      - comboGroupBox.getWidth();
    auto widthGap = emtpySpace / 3.f;
    knobGroupBox.setPosition(controlBox.getTopLeft());
    knobGroupBox.translate(widthGap, 0);
    comboGroupBox.setPosition(controlBox.getTopRight());
    comboGroupBox.translate(-1 * widthGap - comboGroupBox.getWidth(), 0);
    auto knobLabelBox = knobGroupBox.withHeight(labelFont.getHeight() + 2);
    auto knobAreaBox = knobGroupBox.withTop(knobLabelBox.getBottom());
    
    knobKnobBox.setCentre(knobAreaBox.getCentre());
    rateLabel->setBounds(knobLabelBox.toNearestInt());
    rateKnob->setBounds(knobKnobBox.toNearestInt());
    rateKnob->setTextBoxStyle(Slider::TextBoxBelow, true, 
      (int)knobKnobBox.getWidth(),
      (int)detailFont.getHeight());
    auto comboLabelBox = comboGroupBox.withHeight(labelFont.getHeight() + 2);
    auto comboAreaBox = comboGroupBox.withTop(comboLabelBox.getBottom());
    auto comboComboBox = Rectangle<float>(comboAreaBox.getWidth() - 2., 
                                          detailFont.getHeight() + 6.);
    comboComboBox.setCentre(comboAreaBox.getCentre());
    lfoWaveLabel->setBounds(comboLabelBox.toNearestInt());
    lfoWaveCombo->setBounds(comboComboBox.toNearestInt()); */
  }
  else
  {
    //Vertical Layout
  }
}



LFOControlComponent::LFOControlComponent() : juce::Component()
{
  auto lfoControl = new LFOSingleController("LFO #1");
  lfoControllers.add(lfoControl);
  addAndMakeVisible(*lfoControl);
  lfoControl = new LFOSingleController("LFO #2");
  lfoControllers.add(lfoControl);
  addAndMakeVisible(*lfoControl);
  lfoControl = new LFOSingleController("LFO #3");
  lfoControllers.add(lfoControl);
  addAndMakeVisible(*lfoControl);
}

LFOControlComponent::~LFOControlComponent()
{

}

void LFOControlComponent::paint(juce::Graphics& g)
{
  auto bg = RTJuceGUI::Colours::VintageGray;
  g.fillAll(bg);
}

void LFOControlComponent::resized()
{
  auto bounds = getLocalBounds();
  auto controlGroupBox = bounds.withHeight(bounds.proportionOfHeight(0.3333f));
  auto padding = 5;
  for (auto lfo : lfoControllers)
  {
    jassert(lfo);
    auto lfoBounds = controlGroupBox.reduced(getWidth() / 4, padding);
    lfo->setBounds(lfoBounds);
    controlGroupBox.translate(0, controlGroupBox.getHeight());
  }
}