#pragma once

#include <JuceHeader.h>

class LFO
{
  public:
    static constexpr size_t LUTSize = 1024;

    enum WaveType
    {
      WaveTypeSine = 0,
      WaveTypeTriangle = 1,
      WaveTypeSquare = 2,
      WaveTypeSawtooth = 3
    };


    LFO(WaveType w)
    {
      setWaveType(w);
    }

    LFO(): LFO(WaveTypeSine){};

    void setFrequency(float f) noexcept
    {
      oscillator.setFrequency(f);
    }

    float getFrequency() const noexcept
    {
      return oscillator.getFrequency();
    }

    void setWaveType(WaveType w) noexcept
    {
      waveType = w;
      auto func = GetWaveFunction(w);
      if (func == nullptr)
      {
        oscillator.initialise([](float in){ return 0.f; }, LUTSize);
      }
      else
      {
        oscillator.initialise(func, LUTSize);
      } 
    }

    void prepare(const juce::dsp::ProcessSpec& spec) noexcept
    {
      oscillator.prepare(spec);
    }

    void reset() noexcept
    {
      oscillator.reset();
    }

    float JUCE_VECTOR_CALLTYPE processSample(float input) noexcept
    {
      return oscillator.processSample(input);
    }

    template<typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
      oscillator.process(context);
    }


    typedef float (*WaveFunction)(float);

    static WaveFunction GetWaveFunction(WaveType w) noexcept
    {
      if (w == WaveTypeSine)
      {
        return CalculateSine;
      }
      else if (w == WaveTypeTriangle)
      {
        return CalculateTriangle;
      }
      else if (w == WaveTypeSquare)
      {
        return CalculateSquare;
      }
      else if (w == WaveTypeSawtooth)
      {
        return CalculateSawtooth;
      }
      return nullptr;
    }
    static float CalculateSine(float input) noexcept
    {
      return std::sinf(input);
    }

    static float CalculateTriangle(float input) noexcept
    {
      constexpr float kPi = juce::MathConstants<float>::pi;
      return (input < 0) ?
        juce::jmap(input, -kPi, 0.f, -1.f, 1.f) : 
        juce::jmap(input, 0.f, kPi, 1.f, -1.f);
    }

    static float CalculateSquare(float input) noexcept
    {
      constexpr float kPi = juce::MathConstants<float>::pi;
      return (input < 0) ? -1.f : 1.f;
    }

    static float CalculateSawtooth(float input) noexcept
    {
      constexpr float kPi = juce::MathConstants<float>::pi;
      return juce::jmap(input, -kPi, kPi, -1.f, 1.f);
    }
  protected:
    juce::dsp::Oscillator<float> oscillator;
    WaveType waveType;
};