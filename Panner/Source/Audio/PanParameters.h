#pragma once

#include <JuceHeader.h>

#include "PanModulator.h"


using FloatParameter = juce::AudioParameterFloat;
using BoolParameter = juce::AudioParameterBool;
using ChoiceParameter = juce::AudioParameterChoice;

class LFOChoiceParameter : public juce::AudioParameterChoice
{
  public:
    LFOChoiceParameter(juce::ParameterID id, String name);
};

class LFOParameters : public juce::AudioProcessorParameterGroup
{
  public:
    using String = juce::String;
    LFOParameters(String id, String name);

    FloatParameter* getRate() noexcept
    {
      return rateHz;
    }

    const FloatParameter* getRate() const noexcept
    {
      return rateHz;
    }

    ChoiceParameter* getWaveform() noexcept
    {
      return waveform;
    }

    const ChoiceParameter* getWaveform() const noexcept
    {
      return waveform;
    }

    BoolParameter* getEnabled() noexcept
    {
      return enabled;
    }

    const BoolParameter* getEnabled() const noexcept
    {
      return enabled;
    }
  protected:
    BoolParameter* enabled;
    ChoiceParameter* waveform;
    FloatParameter* rateHz;
};

class PanModParameters : public juce::AudioProcessorParameterGroup
{
  public:
    using String = juce::String;
    PanModParameters(String id, String name);

    AudioParameterFloat* getX() noexcept
    {
      return xAmt;
    }

    const AudioParameterFloat* getX() const noexcept
    {
      return xAmt;
    }

    ChoiceParameter* getXLFO() noexcept
    {
      return xLFO;
    }

    const ChoiceParameter* getXLFO() const noexcept
    {
      return xLFO;
    }

    AudioParameterFloat* getY() noexcept
    {
      return xAmt;
    }

    const AudioParameterFloat* getY() const noexcept
    {
      return xAmt;
    }

    ChoiceParameter* getYLFO() noexcept
    {
      return yLFO;
    }

    const ChoiceParameter* getYLFO() const noexcept
    {
      return yLFO;
    }

    AudioParameterFloat* getZ() noexcept
    {
      return zAmt;
    }

    const AudioParameterFloat* getZ() const noexcept
    {
      return zAmt;
    }

    ChoiceParameter* getZLFO() noexcept
    {
      return zLFO;
    }

    const ChoiceParameter* getZLFO() const noexcept
    {
      return zLFO;
    }

    AudioParameterFloat* getRadius() noexcept
    {
      return radiusAmt;
    }

    const AudioParameterFloat* getRadius() const noexcept
    {
      return radiusAmt;
    }

    ChoiceParameter* getRadiusLFO() noexcept
    {
      return radiusLFO;
    }

    const ChoiceParameter* getRadiusLFO() const noexcept
    {
      return radiusLFO;
    }

    AudioParameterFloat* getSpin() noexcept
    {
      return spinAmt;
    }

    const AudioParameterFloat* getSpin() const noexcept
    {
      return spinAmt;
    }

    ChoiceParameter* getSpinLFO() noexcept
    {
      return spinLFO;
    }

    const ChoiceParameter* getSpinLFO() const noexcept
    {
      return spinLFO;
    }

    AudioParameterBool* getEnabled() noexcept
    {
      return panEnabled;
    }

    const AudioParameterBool* getEnabled() const noexcept
    {
      return panEnabled;
    }
  protected:
    AudioParameterBool* panEnabled;
    AudioParameterFloat* xAmt;
    LFOChoiceParameter* xLFO;
    AudioParameterFloat* yAmt;
    LFOChoiceParameter* yLFO;
    AudioParameterFloat* zAmt;
    LFOChoiceParameter* zLFO;
    AudioParameterFloat* radiusAmt;
    LFOChoiceParameter* radiusLFO;
    AudioParameterFloat* spinAmt;
    LFOChoiceParameter* spinLFO;
};

class AutoPanParameters : public juce::AudioProcessorParameterGroup
{
  public:
    using String = juce::String;

    AutoPanParameters(String id, String name);

    AutoPanParameters(): AutoPanParameters("autopan-params", "AutoPan"){};


    LFOParameters* getLFO1() noexcept { return lfo1; };
    const LFOParameters* getLFO1() const noexcept { return lfo1; };

    LFOParameters* getLFO2() noexcept { return lfo2; };
    const LFOParameters* getLFO2() const noexcept { return lfo2; };

    LFOParameters* getLFO3() noexcept { return lfo3; };
    const LFOParameters* getLFO3() const noexcept { return lfo3; };

    PanModParameters* getPanMod() noexcept { return panMod; };
    const PanModParameters* getPanMod() const noexcept { return panMod; };
  protected:
    LFOParameters* lfo1;
    LFOParameters* lfo2;
    LFOParameters* lfo3;
    PanModParameters* panMod;
};

class SurroundPanProvider
{
  public:
    using SurroundPanValue = juce::Vector3D<float>;
    virtual SurroundPanValue getPanPosition(int ch = 0) = 0;
};