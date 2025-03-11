/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Audio/PluginProcessor.h"
#include "GUI/PluginEditor.h"
#include "RT-DSP/Dynamics/GainConverter.h"

using namespace juce;
//==============================================================================

//juce::Decibels::gainToDecibels(0.5f);
//==============================================================================
AmbisonicPannerAudioProcessor::AmbisonicPannerAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::create9point1point6(), true)
                     #endif
                       )
{
  modEnabledFlag = false;
  intermediateBuffer = std::make_unique<juce::AudioBuffer<float>>();
  panModBuffer = std::make_unique<juce::AudioBuffer<float>>();
  encoderProc = std::make_unique<AmbisonicEncoderAudioProcessor>();
  decoderProc = std::make_unique<AmbisonicsDecoderAudioProcessor>();
  autoPanParameters = std::make_unique<AutoPanParameters>("surr-auto-pan", "Surround Auto Pan");
  meterParams = new AudioMeterParameterGroup("outmeters", "Output Meters", 16);
  addParameterGroup(std::unique_ptr<AudioProcessorParameterGroup>(meterParams));
  meterSources = std::make_unique<AudioMeterParameterGroupSourceSet>(meterParams);
  speakerSet = std::make_unique<AudioChannelSet>();
  panMod = std::make_unique<PanModulator>();

}

AmbisonicPannerAudioProcessor::~AmbisonicPannerAudioProcessor()
{
  autoPanParameters.reset();
}
//==============================================================================
const juce::String AmbisonicPannerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AmbisonicPannerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AmbisonicPannerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AmbisonicPannerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AmbisonicPannerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AmbisonicPannerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AmbisonicPannerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AmbisonicPannerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AmbisonicPannerAudioProcessor::getProgramName (int index)
{
    return {};
}

void AmbisonicPannerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void AmbisonicPannerAudioProcessor::numChannelsChanged()
{
  sendChangeMessage();
}

//==============================================================================
void AmbisonicPannerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    jassert(encoderProc);
    jassert(decoderProc);
    jassert(intermediateBuffer);
    BusesLayout busses;
    busses.inputBuses.add(AudioChannelSet::mono());
    busses.outputBuses.add(AudioChannelSet::ambisonic(InternalMaxAmbisonicOrder));
    jassert(encoderProc->checkBusesLayoutSupported(busses));
    encoderProc->setBusesLayout(busses);
    encoderProc->prepareToPlay(sampleRate, samplesPerBlock);
    encoderProc->getEncoderSettings()->ambiOrder = 3;
    encoderProc->getEncoderSettings()->distanceEncodingFlag = false;
    BusesLayout decoderBusses;
    decoderBusses.inputBuses.add(AudioChannelSet::ambisonic(InternalMaxAmbisonicOrder));
    decoderBusses.outputBuses.add(AudioChannelSet::create9point1point6());
    jassert(decoderProc->checkBusesLayoutSupported(decoderBusses));
    decoderProc->setBusesLayout(decoderBusses);
    decoderProc->getAmbiSettings()->setUsedDecoderCount(1);
    decoderProc->getAmbiSettings()->singleDecoder->setAmbiOrder(3);
    setSpeakerSet(SpeakerSet7Dot1Dot4);
    decoderProc->prepareToPlay(sampleRate, samplesPerBlock);
    auto chs = decoderBusses.getMainInputChannels();
    intermediateBuffer->setSize(chs, samplesPerBlock);
    meterProc = std::make_unique<AudioMeterProcessor<float>>();
    dsp::ProcessSpec ps;
    ps.sampleRate = sampleRate;
    ps.numChannels = 16;
    ps.maximumBlockSize = samplesPerBlock;
    meterProc->prepare(ps);
    ps.numChannels = 2;
    panModBuffer->setSize(2, samplesPerBlock);
    panMod->reset();
    panMod->prepare(ps);
    panMod->setDepth(0.0f);
    panMod->setRotationDepth(1.f);
    panMod->setRotation(juce::MathConstants<float>::halfPi);
    panMod->getLFO().setWaveType(LFO::WaveTypeSine);
    panMod->getLFO().setFrequency(1.f);
    panMod->getRotLFO().setWaveType(LFO::WaveTypeSawtooth);
    panMod->getRotLFO().setFrequency(DefaultPanFreq);
}

void AmbisonicPannerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
  jassert(encoderProc);
  jassert(decoderProc);
  encoderProc->releaseResources();
  decoderProc->releaseResources();
  intermediateBuffer->setSize(0, 0);
}


bool AmbisonicPannerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  //For now, don't care, plugin will handle it

  int noInputs = layouts.getMainInputChannels();
  int noOutputs = layouts.getMainOutputChannels();
  if (noInputs == 0 || (noInputs > 16))
    return false;

  if (noOutputs < 1 || (noOutputs > 24 && noOutputs != 64))
    return false;

  return true;
}


void AmbisonicPannerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    jassert(intermediateBuffer);
    int ipChannels = getTotalNumInputChannels();
    if (ipChannels == 0)
    {
      buffer.clear();
      return;
    }
    auto currentBlockSize = buffer.getNumSamples();

    //======== Begin Autio Pan Process ================
    if (modEnabledFlag.get() == true) {
      auto sources = encoderProc->getSources();
      AmbiSource* source = sources->get(0);
      juce::Vector3D<double> sourceVector = sources->getAbsSourcePoint(0);
      dsp::AudioBlock<float> panModBlock(*panModBuffer);
      panModBlock = panModBlock.getSubBlock(0, currentBlockSize);
      panModBlock.getSingleChannelBlock(0).fill(0);
      panModBlock.getSingleChannelBlock(1).fill(0.8);
    
      dsp::ProcessContextReplacing panCtx(panModBlock);
      panMod->process(panCtx);

      float outX = panModBlock.getSample(0, currentBlockSize - 1);
      float outY = panModBlock.getSample(1, currentBlockSize - 1);

      sourceVector.x = outX;
      sourceVector.y = outY;
      sources->setAbsSourcePoint(0, sourceVector);
    }
    //======== End Auto Pan Process ==================

    intermediateBuffer->clear();
    //Copy Channel 1 to the input
    intermediateBuffer->copyFrom(0, 0, buffer, 0, 0, currentBlockSize);
    jassert(encoderProc);
    encoderProc->processBlock(*intermediateBuffer, midiMessages);
    jassert(decoderProc);
    decoderProc->processBlock(*intermediateBuffer, midiMessages);
    jassert(meterProc);
    jassert(meterParams);
    bool metersOn = getMeterSources().metersEnabled();
    if (metersOn) {
      auto data = intermediateBuffer->getArrayOfWritePointers();
      dsp::AudioBlock<float> meterAudio(data, 16, currentBlockSize);
      dsp::ProcessContextReplacing<float> ctx(meterAudio);
      meterProc->process(ctx);
      for (int i = 0; i < 16; i++)
      {
        auto data = meterProc->getLastOutput(i);
        auto meter = meterParams->getChannel(i);
        if (data != nullptr && meter != nullptr)
        {
          //Persist Clip Flag
          bool didClip = meter->didClip() || data->didClip();
          AudioMeterData d(data->getValue(), data->getValue(), didClip);
          *meter = d;
        }
      }
    }
    for (int i = 0; i < getTotalNumOutputChannels(); i++)
    {
      if (i < 16) {
        buffer.copyFrom(i, 0, *intermediateBuffer, i, 0, currentBlockSize);
      }
      else {
        buffer.clear(i, 0, currentBlockSize);
      }
    }
}

//==============================================================================
bool AmbisonicPannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AmbisonicPannerAudioProcessor::createEditor()
{
    //return new GenericAudioProcessorEditor(*this);
    return new AmbisonicPannerAudioProcessorEditor(*this);
}

//==============================================================================
void AmbisonicPannerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AmbisonicPannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmbisonicPannerAudioProcessor();
}

void AmbisonicPannerAudioProcessor::setSpeakerSet(StandardSpeakerSet set)
{
  jassert(decoderProc);
  jassert(speakerSet);
  juce::String presetName = "Stereo";
  switch (set)
  { 
    case SpeakerSetMono:
      presetName = "Standard - Mono";
      *speakerSet = AudioChannelSet::mono();
      break;
    case SpeakerSetStereo:
      presetName = "Standard - Stereo 30deg";
      *speakerSet = AudioChannelSet::stereo();
      break;
    case SpeakerSetLCR:
      presetName = "LCRS";
      *speakerSet = AudioChannelSet::createLCR();
      break;
    case SpeakerSetQuad:
      presetName = "Regular 2D - Quadro (4)";
      *speakerSet = AudioChannelSet::quadraphonic();
      break;
    case SpeakerSet5Dot1:
      presetName = "5.1 ITU";
      *speakerSet = AudioChannelSet::create5point1();
      break;
    case SpeakerSet5Dot1Dot2:
      presetName = "5.1.2";
      *speakerSet = AudioChannelSet::create5point1point2();
      break;
    case SpeakerSet5Dot1Dot4:
      presetName = "5.1.4";
      *speakerSet = AudioChannelSet::create5point1point4();
      break;
    case SpeakerSet7Dot1:
      presetName = "7.1";
      *speakerSet = AudioChannelSet::create7point1();
      break;
    case SpeakerSet7Dot1Dot2:
      presetName = "7.1.2";
      *speakerSet = AudioChannelSet::create7point1point2();
      break;
    case SpeakerSet7Dot1Dot4:
      presetName = "7.1.4";
      *speakerSet = AudioChannelSet::create7point1point4();
      break;
    case SpeakerSet7Dot1Dot6:
      presetName = "7.1.6";
      *speakerSet = AudioChannelSet::create7point1point6();
      break;
    case SpeakerSet9Dot1Dot4:
      presetName = "9.1.4";
      *speakerSet = AudioChannelSet::create9point1point4();
      break;
    case SpeakerSet9Dot1Dot6:
      presetName = "9.1.6";
      *speakerSet = AudioChannelSet::create9point1point6();
      break;
  }
  decoderProc->getSpeakerPresetHelper()->selectPresetName(presetName);
  activeSetName = presetName;
  sendChangeMessage();
}


void AmbisonicPannerAudioProcessor::actionListenerCallback(const String& message)
{

}