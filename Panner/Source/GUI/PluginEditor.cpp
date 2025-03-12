#include "GUI/PluginEditor.h"
#include "Decoder/Source/SpeakerPresetHelper.h"
#include "Decoder/Source/SpeakerSettingsComponent.h"
using namespace juce;


AmbisonicPannerAudioProcessorEditor::AmbisonicPannerAudioProcessorEditor(AmbisonicPannerAudioProcessor& p) :
  AudioProcessorEditor(&p), audioProcessor(p) 
{
  setLookAndFeel(&lookAndFeel);
  audioProcessor.addChangeListener(this);
  mainPanner = std::make_unique<MainPannerComponent>(p);
  encoderButton = std::make_unique<TextButton>("Encoder", "Encoder");
  encoderButton->setButtonText("Encoder");
  decoderButton = std::make_unique<TextButton>("Decoder", "Decoder");
  decoderButton->setButtonText("Decoder");
  tabs = std::make_unique<TabbedComponent>(TabbedButtonBar::TabsAtTop);
  encoderEditor = std::make_unique<AmbisonicEncoderAudioProcessorEditor>(
    audioProcessor.getEncoder());
  decoderEditor = std::make_unique<AmbisonicsDecoderAudioProcessorEditor>(
    audioProcessor.getDecoder());
  auto bg = findColour(ResizableWindow::ColourIds::backgroundColourId);

  //addAndMakeVisible(*encoderEditor);
  //addAndMakeVisible(*decoderEditor);
  tabs->addTab("Panning", RTJuceGUI::Colours::WarmWhite, mainPanner.get(), false, 0);
  tabs->addTab("Encoder", RTJuceGUI::Colours::VintageRed, encoderEditor.get(), false, 1);

  auto s = new SpeakerSettingsComponent(
    audioProcessor.getDecoder().getSpeakerSet(),
    audioProcessor.getDecoder().getSpeakerPresetHelper(), 
    audioProcessor.getDecoder().getDecodingPresetHelper(),
    &pointSelection, 
    audioProcessor.getDecoder().getAmbiSettings(),
    audioProcessor.getDecoder().getDecoderSettings(),
    audioProcessor.getDecoder().getTestSoundGenerator(), 
    this, 
    audioProcessor.getDecoder().getFilterSpecification(),
    audioProcessor.getDecoder().getZoomSettingsPointer(), 
    audioProcessor.getDecoder().getChannelLayout());

  decoderSpeakerSettings = std::unique_ptr< SpeakerSettingsComponent>(s);
  //addAndMakeVisible(*decoderSpeakerSettings);
  tabs->addTab("Speakers", RTJuceGUI::Colours::VintageGreen, decoderSpeakerSettings.get(), false, 2);
  tabs->addTab("Decoder", RTJuceGUI::Colours::VintageAmber, decoderEditor.get(), false, 3);
  addAndMakeVisible(*tabs);
  tabs->setLookAndFeel(&lookAndFeel);
  meters = std::make_unique<ChannelMeterGroupComponent>();
  updateMeteringSources();
  addAndMakeVisible(*meters);
  audioProcessor.getDecoder().getSpeakerPresetHelper()->addActionListener(this);
  tabs->setCurrentTabIndex(0, false);

  setSize(1024, 768);
}

AmbisonicPannerAudioProcessorEditor::~AmbisonicPannerAudioProcessorEditor()
{
  audioProcessor.removeChangeListener(this);
  audioProcessor.getDecoder().getSpeakerPresetHelper()->removeActionListener(this);
  setLookAndFeel(nullptr);
}

//==============================================================================
void AmbisonicPannerAudioProcessorEditor::paint(juce::Graphics& g)
{
  //g.fillAll(findColour(ResizableWindow::ColourIds::backgroundColourId));
  //g.drawFittedText("Hello Component", getLocalBounds(), Justification::centred, 2);
}

void AmbisonicPannerAudioProcessorEditor::resized()
{
  //const int ButtonHeight = 20;
  //const int ButtonBoxMinWidth = 250;
  //const int ButtonGap = 25;
  //const int ButtonBoxWidth = (getWidth() / 2) > ButtonBoxMinWidth ? getWidth() / 2 : ButtonBoxMinWidth;
  //const int ButtonWidth = (ButtonBoxWidth - ButtonGap) / 2;
  //auto buttonBox = getLocalBounds().withHeight(ButtonHeight).withSizeKeepingCentre(ButtonBoxWidth, ButtonHeight).translated(0, 5);
  //auto encBox = buttonBox.withWidth(ButtonWidth);
  //auto decBox = encBox.translated(ButtonWidth + ButtonGap, 0);
  //encoderButton->setBounds(encBox);
  //decoderButton->setBounds(decBox);
  juce::Decibels::gainToDecibels(0.5);
  jassert(meters);
  const int MetersCollapsedHeight = 50;
  const int MetersFullHeight = 200;
  auto bounds = getLocalBounds();
  auto meterHeight = meters->getDesiredHeight();
  auto meterBounds = bounds.withTop(bounds.getBottom() - meterHeight);
  meters->setBounds(meterBounds);
  tabs->setBounds(bounds.withBottom(meterBounds.getY()));
}

void AmbisonicPannerAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* src)
{
  if (src == (ChangeBroadcaster*)&audioProcessor)
  {
    updateMeteringSources();
    resized();
    repaint();
  }
}

void AmbisonicPannerAudioProcessorEditor::updateMeteringSources()
{
  auto outputs = audioProcessor.getBusesLayout().getMainOutputChannelSet();
  auto speakerSet = audioProcessor.getAmbiSpeakerSet();
  meters->createMetersForSpeakerSet(speakerSet, 
    outputs.size(),
    &audioProcessor.getMeterSources());

  //meters->setAllMetersSource(&testMeterSrc);
  resized();
  repaint();
}

void AmbisonicPannerAudioProcessorEditor::showEncoderEditor()
{
  //auto bg = findColour(juce::ResizableWindow::ColourIds::backgroundColourId, true);
  //encoderEditor = std::make_unique<EncoderWindow>(audioProcessor, "Encoder", bg);
  //encoderEditor->onClosed = [this]()
  //{
  //  encoderEditor->setVisible(false);
  //  encoderEditor.reset();
  //};
  //addChildComponent(*encoderEditor);
  //encoderEditor->setBounds(getLocalBounds().reduced(2).withTop(30));
  //addAndMakeVisible(*encoderEditor);
  //encoderEditor->setVisible(true);
}

void AmbisonicPannerAudioProcessorEditor::showDecoderEditor()
{
  //auto bg = findColour(juce::ResizableWindow::ColourIds::backgroundColourId, true);
  //decoderEditor = std::make_unique<DecoderWindow>(audioProcessor, "Decoder", bg);
  //decoderEditor->onClosed = [this]()
  //{
  //  decoderEditor->setVisible(false);
  //  decoderEditor.reset();
  //};
  //addChildComponent(*decoderEditor);
  //decoderEditor->setBounds(getLocalBounds().reduced(2).withTop(30));
  //decoderEditor->setVisible(true);
}

void AmbisonicPannerAudioProcessorEditor::updateBusLayout(
  const AudioProcessor::BusesLayout& layout)
{
  
}


void AmbisonicPannerAudioProcessorEditor::actionListenerCallback(const String& message)
{
  if (message == ACTION_MESSAGE_PRESET_CHANGED)
  {
    updateMeteringSources();
  }
}