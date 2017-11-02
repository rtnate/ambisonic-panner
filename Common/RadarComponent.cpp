/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "RadarComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RadarComponent::RadarComponent (Array<AmbiPoint>* pSpeakerArray, Array<AmbiPoint>* pMovingPointsArray, PointSelection* pPointSelection)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (radar = new Radar3D (pSpeakerArray, pMovingPointsArray, &zoomSettings, pPointSelection));
    radar->setName ("radar");

    addAndMakeVisible (pointInfo = new PointInfoControl (pSpeakerArray, pPointSelection));
    pointInfo->setName ("pointInfo");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

RadarComponent::~RadarComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    radar = nullptr;
    pointInfo = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RadarComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff505050));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RadarComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    radar->setBounds (0, 0 + 100, proportionOfWidth (1.0000f), getHeight() - 100);
    pointInfo->setBounds (0, 0, proportionOfWidth (1.0000f), 100);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RadarComponent" componentName=""
                 parentClasses="public Component" constructorParams="Array&lt;AmbiPoint&gt;* pSpeakerArray, Array&lt;AmbiPoint&gt;* pMovingPointsArray, PointSelection* pPointSelection"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff505050"/>
  <GENERICCOMPONENT name="radar" id="bb1556089d26688f" memberName="radar" virtualName=""
                    explicitFocusOrder="0" pos="0 0R 100% 100M" posRelativeY="328b0557e3704175"
                    class="Radar3D" params="pSpeakerArray, pMovingPointsArray, &amp;zoomSettings, pPointSelection"/>
  <GENERICCOMPONENT name="pointInfo" id="328b0557e3704175" memberName="pointInfo"
                    virtualName="" explicitFocusOrder="0" pos="0 0 100% 100" class="PointInfoControl"
                    params="pSpeakerArray, pPointSelection"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
