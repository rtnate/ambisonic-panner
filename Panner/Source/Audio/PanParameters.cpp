#include "PanParameters.h"


using namespace juce;
LFOChoiceParameter::LFOChoiceParameter(juce::ParameterID id, String name) :
  ChoiceParameter(id, name, { "LFO #1", "LFO #2", "LFO #2" }, 1)
{

}

LFOParameters::LFOParameters(String id, String name):
  juce::AudioProcessorParameterGroup(id, name, "-")
{
  //Enabled
  ParameterID enId = id + "-enabled";
  String enName = name + " Enabled";
  enabled = new BoolParameter(enId, enName, false);
  addChild(std::unique_ptr<BoolParameter>(enabled));
  //Waveform
  ParameterID wfId = id + "-waveform";
  String wfName = name + " Waveform";
  StringArray choices;
  choices.insert((int)LFO::WaveTypeSine, "Sine");
  choices.insert((int)LFO::WaveTypeTriangle, "Triangle");
  choices.insert((int)LFO::WaveTypeSquare, "Sqaure");
  choices.insert((int)LFO::WaveTypeSawtooth, "Sawtooth");
  waveform = new ChoiceParameter(wfId, wfName, 
                                 choices, (int)LFO::WaveTypeSine);
  addChild(std::unique_ptr<ChoiceParameter>(waveform));
  //Rate
  ParameterID rtId = id + "-rate";
  String rtName = name + " Rate";
  rateHz = new FloatParameter(rtId, rtName, 0.01f, 10.f, 0.1f);
  addChild(std::unique_ptr<FloatParameter>(rateHz));
}

PanModParameters::PanModParameters(String id, String name) :
  juce::AudioProcessorParameterGroup(id, name, "-")
{
  //X
  ParameterID xId = id + "-xamt";
  String xName = name + " X Amount";
  xAmt = new FloatParameter(xId, xName, 0.f, 1.f, 0.f);
  addChild(std::unique_ptr<FloatParameter>(xAmt));
  //X LFO
  ParameterID xlfoId = id + "-xlfo";
  String xlfoName = name + " X LFO";
  xLFO = new LFOChoiceParameter(xlfoId, xlfoName);
  addChild(std::unique_ptr<ChoiceParameter>(xLFO));
  //Y
  ParameterID yId = id + "-yamt";
  String yName = name + " Y Amount";
  yAmt = new FloatParameter(yId, yName, 0.f, 1.f, 0.f);
  addChild(std::unique_ptr<FloatParameter>(yAmt));
  //Y LFO
  ParameterID ylfoId = id + "-ylfo";
  String ylfoName = name + " Y LFO";
  yLFO = new LFOChoiceParameter(ylfoId, ylfoName);
  addChild(std::unique_ptr<ChoiceParameter>(yLFO));
  //Z
  ParameterID zId = id + "-zamt";
  String zName = name + " Z Amount";
  zAmt = new FloatParameter(zId, zName, 0.f, 1.f, 0.f);
  addChild(std::unique_ptr<FloatParameter>(zAmt));
  //Z LFO
  ParameterID zlfoId = id + "-zlfo";
  String zlfoName = name + " Z LFO";
  zLFO = new LFOChoiceParameter(zlfoId, zlfoName);
  addChild(std::unique_ptr<ChoiceParameter>(zLFO));
  //Radius
  ParameterID rId = id + "-ramt";
  String rName = name + " Radius Amount";
  radiusAmt = new FloatParameter(rId, rName, 0.f, 1.f, 0.f);
  addChild(std::unique_ptr<FloatParameter>(radiusAmt));
  //Radius LFO
  ParameterID rlfoId = id + "-rlfo";
  String rlfoName = name + " Radius LFO";
  radiusLFO = new LFOChoiceParameter(rlfoId, rlfoName);
  addChild(std::unique_ptr<ChoiceParameter>(radiusLFO));
  //Spin
  ParameterID sId = id + "-spinamt";
  String sName = name + " Spin Amount";
  spinAmt = new FloatParameter(sId, sName, 0.f, 1.f, 0.f);
  addChild(std::unique_ptr<FloatParameter>(spinAmt));
  //Spin LFO
  ParameterID slfoId = id + "-slfo";
  String slfoName = name + " Spin LFO";
  spinLFO = new LFOChoiceParameter(slfoId, slfoName);
  addChild(std::unique_ptr<ChoiceParameter>(spinLFO));
  //Enabled 
  ParameterID enId = id + "-apenabled";
  String enName = name + " Pan Mod Enabled";
  panEnabled = new BoolParameter(enId, enName, false);
  addChild(std::unique_ptr<BoolParameter>(panEnabled));
}


AutoPanParameters::AutoPanParameters(String id, String name) :
  juce::AudioProcessorParameterGroup(id, name, "-")
{
  String lfo1_id = id + "-lfo1";
  String lfo1_name = name + " LFO 1";
  lfo1 = new LFOParameters(lfo1_id, lfo1_name);
  addChild(std::unique_ptr<AudioProcessorParameterGroup>(lfo1));
  //LFO 2
  String lfo2_id = id + "-lfo2";
  String lfo2_name = name + " LFO 2";
  lfo2 = new LFOParameters(lfo2_id, lfo2_name);
  addChild(std::unique_ptr<AudioProcessorParameterGroup>(lfo2));
  //LFO 3
  String lfo3_id = id + "-lfo3";
  String lfo3_name = name + " LFO 3";
  lfo3 = new LFOParameters(lfo3_id, lfo3_name);
  addChild(std::unique_ptr<AudioProcessorParameterGroup>(lfo3));
  //Mod 
  String mod_id = id + "-panmod";
  String mod_name = name + " Movement";
  panMod = new PanModParameters(mod_id, mod_name);
  addChild(std::unique_ptr<AudioProcessorParameterGroup>(panMod));
}