

#include "JuceHeader.h"

#if PLUGIN_IS_AMBI_DECODER 
#include "Decoder/Source/PluginProcessor.h"

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AmbisonicsDecoderAudioProcessor();
}

#elif PLUGIN_IS_AMBI_ENCODER 

#include "Encoder/Source/PluginProcessor.h"

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new AmbisonicEncoderAudioProcessor();
}


#elif PLUGIN_IS_AMBI_PANNER 

#else 

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return nullptr;
}
#endif



