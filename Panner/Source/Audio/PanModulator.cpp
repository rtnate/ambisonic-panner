#include "PanModulator.h"

using namespace juce;
using namespace juce::dsp;

void PanModulator::processBlock(const InputBlock& input, OutputBlock& output) noexcept
{
  intermediate.clear();
  AudioBlock<float> block = intermediate.getSubBlock(0, output.getNumSamples());
  ProcessContextReplacing<float> ctx(block.getSingleChannelBlock(0));
  lfo.process(ctx);
  ProcessContextReplacing<float> ctx2(block.getSingleChannelBlock(1));
  rotLfo.process(ctx2);
  jassert(input.getNumChannels() >= 2);
  jassert(output.getNumChannels() >= 2);
  
  const float* xSrc = input.getChannelPointer(0);
  const float* ySrc = input.getChannelPointer(1);
  float*  xDest = output.getChannelPointer(0);
  float* yDest = output.getChannelPointer(1);
  const float* lfoResult = intermediate.getChannelPointer(0);
  const float* rotLfoResult = intermediate.getChannelPointer(1);
  auto blkSize = output.getNumSamples();

  float lfoOut, inX, inY, x, y, r, th;
  while(blkSize--)
  {
    lfoOut = *lfoResult++;
    inX = *xSrc++;
    inY = *ySrc++;
    calcMod(lfoOut, x, y);
    x += inX;
    y += inY;
    lfoOut = *rotLfoResult++;
    lfoOut *= juce::MathConstants<float>::pi;
    lfoOut *= rot_depth;
    r = std::sqrtf(x * x + y * y);
    th = std::atan2f(y, x);
    th += lfoOut;
    x = r * std::cos(th);
    y = r * std::sin(th);
    *xDest++ = x;
    *yDest++ = y;
  }
}