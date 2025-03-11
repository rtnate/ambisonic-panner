#include "MainPannerComponent.h"
#include "LookAndFeel/RTLookAndFeel.h"
using namespace juce;
MainPannerComponent::MainPannerComponent(AmbisonicPannerAudioProcessor& ap): proc(ap)
{
  tabs = std::make_unique<TabbedComponent>(TabbedButtonBar::TabsAtLeft);
  lfos = std::make_unique<LFOControlComponent>();
  autopan = std::make_unique<AutoPanComponent>();
  tabs->addTab("AutoPan", RTJuceGUI::Colours::VintageAmber, autopan.get(), false);
  autopan->setAutoPanEnabledState(ap.getAutoPanEnabled(), false);
  autopan->setRateSetting(ap.DefaultPanFreq, false);
  autopan->addChangeListener(this);
  autopan->setDecoderTruncationEnabledState(false, false);
  autopan->setEncoderTruncationEnabledState(false, false);
  tabs->addTab("LFO's", RTJuceGUI::Colours::VintageRed, lfos.get(), false);
  tabs->setCurrentTabIndex(0);
  addAndMakeVisible(*tabs);
}

MainPannerComponent::~MainPannerComponent()
{

}

void MainPannerComponent::resized()
{
  tabs->setBounds(getLocalBounds());
}

void MainPannerComponent::changeListenerCallback(juce::ChangeBroadcaster* src)
{
  if (src == nullptr) return;
  if (src == autopan.get() || src == lfos.get())
  {
    syncParamsUpstream();
    //proc.setAutoPanEnabled(autopan->getAutoPanEnabledState());
    //proc.getDecoder().enableGainTruncation(autopan->getDecoderTruncationEnabledState());
    //proc.getEncoder().enableGainTruncation(autopan->getEncoderTruncationEnabledState());
    //proc.setModRate(autopan->getRateSetting());
    return;
  }
  if (src == &proc)
  {
    syncParamsDownstream();
    return;
  }
}

void MainPannerComponent::syncParamsUpstream()
{
  auto params = proc.getAutoPanParameters();
  jassert(params);
  if (params == nullptr) return;
  jassert(autopan);
  jassert(lfos);
  /////////////
  // Pan Basis 
  /////////////
  auto panPos = autopan->getPanPosition();
  proc.setPanPositionBasis(panPos);
  ////////////
  //Sync LFOS
  ////////////
  //1
  auto lfoControl1 = lfos->getLfoController(0);
  jassert(lfoControl1);
  auto lfoParams1 = params->getLFO1();
  jassert(lfoParams1);
  auto rate1 = lfoParams1->getRate();
  auto wf1 = lfoParams1->getWaveform();
  auto en1 = lfoParams1->getEnabled();
  jassert(rate1);
  *rate1 = lfoControl1->getRate();
  jassert(wf1);
  *wf1 = lfoControl1->getWaveform();
  jassert(en1);
  *en1 = lfoControl1->getEnabled();
  //2
  auto lfoControl2 = lfos->getLfoController(1);
  jassert(lfoControl2);
  auto lfoParams2 = params->getLFO2();
  jassert(lfoParams2);
  auto rate2 = lfoParams2->getRate();
  auto wf2 = lfoParams2->getWaveform();
  auto en2 = lfoParams2->getEnabled();
  jassert(rate2);
  *rate2 = lfoControl2->getRate();
  jassert(wf2);
  *wf2 = lfoControl2->getWaveform();
  jassert(en2);
  *en2 = lfoControl2->getEnabled();
  //3 
  auto lfoControl3 = lfos->getLfoController(2);
  jassert(lfoControl3);
  auto lfoParams3 = params->getLFO3();
  jassert(lfoParams3);
  auto rate3 = lfoParams3->getRate();
  auto wf3 = lfoParams3->getWaveform();
  auto en3 = lfoParams3->getEnabled();
  jassert(rate3);
  *rate3 = lfoControl3->getRate();
  jassert(wf3);
  *wf3 = lfoControl3->getWaveform();
  jassert(en3);
  *en3 = lfoControl3->getEnabled();
  ///////////
  //Sync Mod 
  ///////////
  auto& modControlGroup = autopan->getModGroup();
  auto modParams = params->getPanMod();
  jassert(modParams);
  //X
  auto modX = modParams->getX();
  jassert(modX);
  *modX = modControlGroup.getFaderValue(BasicModGroup::FaderModX);
  auto xLFO = modParams->getXLFO();
  jassert(xLFO);
  *xLFO = modControlGroup.getFaderLFOSelection(BasicModGroup::FaderModX);
  //Y
  auto modY = modParams->getY();
  jassert(modY);
  *modY = modControlGroup.getFaderValue(BasicModGroup::FaderModY);
  auto yLFO = modParams->getYLFO();
  jassert(yLFO);
  *yLFO = modControlGroup.getFaderLFOSelection(BasicModGroup::FaderModY);
  //Z
  auto modZ = modParams->getZ();
  jassert(modZ);
  *modZ = modControlGroup.getFaderValue(BasicModGroup::FaderModZ);
  auto zLFO = modParams->getZLFO();
  jassert(zLFO);
  *zLFO = modControlGroup.getFaderLFOSelection(BasicModGroup::FaderModZ);
  //R
  auto modR = modParams->getRadius();
  jassert(modR);
  *modR = modControlGroup.getFaderValue(BasicModGroup::FaderModR);
  auto rLFO = modParams->getRadiusLFO();
  jassert(rLFO);
  *rLFO = modControlGroup.getFaderLFOSelection(BasicModGroup::FaderModR);
  //Spin
  auto modSpin = modParams->getSpin();
  jassert(modSpin);
  *modSpin = modControlGroup.getFaderValue(BasicModGroup::FaderModRadial);
  auto sLFO = modParams->getSpinLFO();
  jassert(sLFO);
  *sLFO = modControlGroup.getFaderLFOSelection(BasicModGroup::FaderModRadial);
  //Enabled
  auto enabled = modParams->getEnabled();
  jassert(enabled);
  *enabled = autopan->getAutoPanEnabledState();
}

void MainPannerComponent::syncParamsDownstream()
{
  auto params = proc.getAutoPanParameters();
  jassert(params);
  if (params == nullptr) return;
  jassert(autopan);
  jassert(lfos);
  ////////////
  //Sync LFOS
  ////////////
  //1
  auto lfoControl1 = lfos->getLfoController(0);
  jassert(lfoControl1);
  auto lfoParams1 = params->getLFO1();
  jassert(lfoParams1);
  auto rate1 = lfoParams1->getRate();
  auto wf1 = lfoParams1->getWaveform();
  auto en1 = lfoParams1->getEnabled();
  jassert(rate1);
  lfoControl1->setRate(*rate1, dontSendNotification);
  jassert(wf1);
  lfoControl1->setWaveform(*wf1, dontSendNotification);
  jassert(en1);
  lfoControl1->setEnabled(*en1, dontSendNotification);
  //2
  auto lfoControl2 = lfos->getLfoController(1);
  jassert(lfoControl2);
  auto lfoParams2 = params->getLFO2();
  jassert(lfoParams2);
  auto rate2 = lfoParams2->getRate();
  auto wf2 = lfoParams2->getWaveform();
  auto en2 = lfoParams2->getEnabled();
  jassert(rate2);
  lfoControl2->setRate(*rate2, dontSendNotification);
  jassert(wf2);
  lfoControl2->setWaveform(*wf2, dontSendNotification);
  jassert(en2);
  lfoControl2->setEnabled(*en2, dontSendNotification);
  //3 
  auto lfoControl3 = lfos->getLfoController(2);
  jassert(lfoControl3);
  auto lfoParams3 = params->getLFO3();
  jassert(lfoParams3);
  auto rate3 = lfoParams3->getRate();
  auto wf3 = lfoParams3->getWaveform();
  auto en3 = lfoParams3->getEnabled();
  jassert(rate3);
  lfoControl3->setRate(*rate3, dontSendNotification);
  jassert(wf3);
  lfoControl3->setWaveform(*wf3, dontSendNotification);
  jassert(en3);
  lfoControl3->setEnabled(*en3, dontSendNotification);
  ///////////
  //Sync Mod 
  ///////////
  auto &modControlGroup = autopan->getModGroup();
  auto modParams = params->getPanMod();
  jassert(modParams);
  //X
  auto modX = modParams->getX();
  jassert(modX);
  modControlGroup.setFaderValue(BasicModGroup::FaderModX, 
                                *modX, dontSendNotification);
  auto xlfo = modParams->getXLFO();
  jassert(xlfo);
  modControlGroup.setFaderLFOSelection(BasicModGroup::FaderModX,
                                *xlfo, dontSendNotification);
  //Y
  auto modY = modParams->getY();
  jassert(modY);
  modControlGroup.setFaderValue(BasicModGroup::FaderModY,
                                *modY, dontSendNotification);
  auto ylfo = modParams->getYLFO();
  jassert(ylfo);
  modControlGroup.setFaderLFOSelection(BasicModGroup::FaderModY,
    *ylfo, dontSendNotification);
  //Z
  auto modZ = modParams->getZ();
  jassert(modZ);
  modControlGroup.setFaderValue(BasicModGroup::FaderModZ,
                                *modZ, dontSendNotification);
  auto zlfo = modParams->getZLFO();
  jassert(zlfo);
  modControlGroup.setFaderLFOSelection(BasicModGroup::FaderModZ,
    *zlfo, dontSendNotification);
  //R
  auto modR = modParams->getRadius();
  jassert(modR);
  modControlGroup.setFaderValue(BasicModGroup::FaderModR,
                                *modR, dontSendNotification);
  auto rlfo = modParams->getRadiusLFO();
  jassert(rlfo);
  modControlGroup.setFaderLFOSelection(BasicModGroup::FaderModR,
    *rlfo, dontSendNotification);
  //Spin
  auto modSpin = modParams->getSpin();
  jassert(modSpin);
  modControlGroup.setFaderValue(BasicModGroup::FaderModRadial,
                                *modSpin, dontSendNotification);
  auto slfo = modParams->getSpinLFO();
  jassert(slfo);
  modControlGroup.setFaderLFOSelection(BasicModGroup::FaderModRadial,
    *slfo, dontSendNotification);
  //Enabled
  auto enabled = modParams->getEnabled();
  jassert(enabled);
  autopan->setAutoPanEnabledState(*enabled, dontSendNotification);
}