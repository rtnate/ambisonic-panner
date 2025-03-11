#pragma once 

#include "LFO.h"


class PanModulator
{
  public:
    PanModulator(): lfo(), depth(0){};

    void setDepth(float d) noexcept
    {
      depth = d;
    }

    float getDepth() const noexcept
    {
      return depth;
    }

    void setRotationDepth(float d) noexcept
    {
      rot_depth = d;
    }

    float getRotationDepth() const noexcept
    {
      return rot_depth;
    }
    void setRotation(float theta) noexcept
    {
      float x = std::cosf(theta);
      float y = std::sinf(theta);
      setProportion(x, y);
    }

    void setProportion(float x_prop, float y_prop) noexcept
    {
      x_mod_mult = x_prop;
      y_mod_mult = y_prop;
    }

    LFO& getLFO() noexcept
    { 
      return lfo;
    }

    const LFO& getLFO() const noexcept
    {
      return lfo;
    }

    LFO& getRotLFO() noexcept
    {
      return rotLfo;
    }

    const LFO& getRotLFO() const noexcept
    {
      return rotLfo;
    }

    void prepare(const juce::dsp::ProcessSpec& sp) noexcept
    {
      juce::dsp::ProcessSpec lfoSpec = sp;
      lfoSpec.numChannels = 1;
      lfo.prepare(lfoSpec);
      rotLfo.prepare(lfoSpec);
      intermediate = juce::dsp::AudioBlock<float>(
        intermediateMemory, 2, sp.maximumBlockSize);
    }

    void reset() noexcept
    {
      lfo.reset();
    }

    template<typename ProcessContext>
    void process(const ProcessContext& ctx)
    {
      processBlock(ctx.getInputBlock(), ctx.getOutputBlock());
    }


    void processSample(float inX, float inY, float& outX, float& outY) noexcept
    {
      float lfoOut = lfo.processSample(0.f);
      float x, y;
      calcMod(lfoOut, x, y);
      outX = inX + x;
      outY = inY + y;
    }

    using InputBlock = juce::dsp::ProcessContextReplacing<float>::ConstAudioBlockType;
    using OutputBlock = juce::dsp::ProcessContextReplacing<float>::AudioBlockType;
    void processBlock(const InputBlock &input, OutputBlock& output) noexcept;

  protected:
    float depth;
    float rot_depth;
    float x_mod_mult;
    float y_mod_mult;
    float x_out;
    float y_out;
    LFO lfo;
    LFO rotLfo;
    juce::dsp::AudioBlock<float> intermediate;
    juce::HeapBlock<char> intermediateMemory;
    
    void calcMod(float lfoIn, float& outX, float& outY)
    {
      float mod = lfoIn * depth;
      outX = mod * x_mod_mult;
      outY = mod * y_mod_mult;
    }
};