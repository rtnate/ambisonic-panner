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

#include "EncoderSettingsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EncoderSettingsComponent::EncoderSettingsComponent (EncoderSettings* pSettings)
    : pEncoderSettings(pSettings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupOscReceive = new GroupComponent ("groupOscReceive",
                                                             TRANS("OSC Receive")));

    addAndMakeVisible (toggleReceiveOsc = new ToggleButton ("toggleReceiveOsc"));
    toggleReceiveOsc->setButtonText (TRANS("Enable"));
    toggleReceiveOsc->addListener (this);

    addAndMakeVisible (textOscReceivePort = new TextEditor ("textOscReceivePort"));
    textOscReceivePort->setMultiLine (false);
    textOscReceivePort->setReturnKeyStartsNewLine (false);
    textOscReceivePort->setReadOnly (false);
    textOscReceivePort->setScrollbarsShown (true);
    textOscReceivePort->setCaretVisible (true);
    textOscReceivePort->setPopupMenuEnabled (true);
    textOscReceivePort->setText (String());

    addAndMakeVisible (labelOscPort = new Label ("labelOscPort",
                                                 TRANS("OSC-Port:\n")));
    labelOscPort->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelOscPort->setJustificationType (Justification::centredLeft);
    labelOscPort->setEditable (false, false, false);
    labelOscPort->setColour (TextEditor::textColourId, Colours::black);
    labelOscPort->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupOscSend = new GroupComponent ("groupOscSend",
                                                          TRANS("OSC Send")));

    addAndMakeVisible (toggleSendOsc = new ToggleButton ("toggleSendOsc"));
    toggleSendOsc->setButtonText (TRANS("Enable"));
    toggleSendOsc->addListener (this);

    addAndMakeVisible (textOscSendIp = new TextEditor ("textOscSendIp"));
    textOscSendIp->setMultiLine (false);
    textOscSendIp->setReturnKeyStartsNewLine (false);
    textOscSendIp->setReadOnly (false);
    textOscSendIp->setScrollbarsShown (true);
    textOscSendIp->setCaretVisible (true);
    textOscSendIp->setPopupMenuEnabled (true);
    textOscSendIp->setText (String());

    addAndMakeVisible (labelOscSendIp = new Label ("labelOscSendIp",
                                                   TRANS("Target Host:")));
    labelOscSendIp->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelOscSendIp->setJustificationType (Justification::centredLeft);
    labelOscSendIp->setEditable (false, false, false);
    labelOscSendIp->setColour (TextEditor::textColourId, Colours::black);
    labelOscSendIp->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textOscSendPort = new TextEditor ("textOscSendPort"));
    textOscSendPort->setMultiLine (false);
    textOscSendPort->setReturnKeyStartsNewLine (false);
    textOscSendPort->setReadOnly (false);
    textOscSendPort->setScrollbarsShown (true);
    textOscSendPort->setCaretVisible (true);
    textOscSendPort->setPopupMenuEnabled (true);
    textOscSendPort->setText (String());

    addAndMakeVisible (labelOscSendPort = new Label ("labelOscSendPort",
                                                     TRANS("OSC-Port:\n")));
    labelOscSendPort->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelOscSendPort->setJustificationType (Justification::centredLeft);
    labelOscSendPort->setEditable (false, false, false);
    labelOscSendPort->setColour (TextEditor::textColourId, Colours::black);
    labelOscSendPort->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textOscSendInterval = new TextEditor ("textOscSendInterval"));
    textOscSendInterval->setMultiLine (false);
    textOscSendInterval->setReturnKeyStartsNewLine (false);
    textOscSendInterval->setReadOnly (false);
    textOscSendInterval->setScrollbarsShown (true);
    textOscSendInterval->setCaretVisible (true);
    textOscSendInterval->setPopupMenuEnabled (true);
    textOscSendInterval->setText (String());

    addAndMakeVisible (labelOscSendInterval = new Label ("labelOscSendInterval",
                                                         TRANS("Interval [ms]:")));
    labelOscSendInterval->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelOscSendInterval->setJustificationType (Justification::centredLeft);
    labelOscSendInterval->setEditable (false, false, false);
    labelOscSendInterval->setColour (TextEditor::textColourId, Colours::black);
    labelOscSendInterval->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (500, 400);


    //[Constructor] You can add your own custom stuff here..
	textOscReceivePort->addListener(this);
	textOscSendPort->addListener(this);
	textOscSendIp->addListener(this);
	textOscSendInterval->addListener(this);

	toggleReceiveOsc->setToggleState(pEncoderSettings->oscReceiveFlag, dontSendNotification);
	toggleSendOsc->setToggleState(pEncoderSettings->oscSendFlag, dontSendNotification);
	textOscSendIp->setText(String(pEncoderSettings->oscSendTargetHost));
	textOscSendPort->setText(String(pEncoderSettings->oscSendPort));
	textOscReceivePort->setText(String(pEncoderSettings->oscReceivePort));
	textOscSendInterval->setText(String(pEncoderSettings->oscSendIntervalMs));
    //[/Constructor]
}

EncoderSettingsComponent::~EncoderSettingsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupOscReceive = nullptr;
    toggleReceiveOsc = nullptr;
    textOscReceivePort = nullptr;
    labelOscPort = nullptr;
    groupOscSend = nullptr;
    toggleSendOsc = nullptr;
    textOscSendIp = nullptr;
    labelOscSendIp = nullptr;
    textOscSendPort = nullptr;
    labelOscSendPort = nullptr;
    textOscSendInterval = nullptr;
    labelOscSendInterval = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EncoderSettingsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff505050));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EncoderSettingsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupOscReceive->setBounds (2, 5, getWidth() - 8, 64);
    toggleReceiveOsc->setBounds (18, 29, 150, 24);
    textOscReceivePort->setBounds (2 + (getWidth() - 8) - 20 - 105, 5 + 24, 105, 24);
    labelOscPort->setBounds (2 + (getWidth() - 8) - 141 - 109, 29, 109, 24);
    groupOscSend->setBounds (1, 77, getWidth() - 8, 131);
    toggleSendOsc->setBounds (17, 101, 150, 24);
    textOscSendIp->setBounds (2 + (getWidth() - 8) - 21 - 136, 5 + 96, 136, 24);
    labelOscSendIp->setBounds (2 + (getWidth() - 8) - 165 - 86, 101, 86, 24);
    textOscSendPort->setBounds (2 + (getWidth() - 8) - 21 - 104, 5 + 132, 104, 24);
    labelOscSendPort->setBounds (2 + (getWidth() - 8) - 141 - 110, 137, 110, 24);
    textOscSendInterval->setBounds (2 + (getWidth() - 8) - 21 - 104, 5 + 167, 104, 24);
    labelOscSendInterval->setBounds (2 + (getWidth() - 8) - 141 - 110, 172, 110, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EncoderSettingsComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleReceiveOsc)
    {
        //[UserButtonCode_toggleReceiveOsc] -- add your button handler code here..
		pEncoderSettings->oscReceiveFlag = toggleReceiveOsc->getToggleState();
        //[/UserButtonCode_toggleReceiveOsc]
    }
    else if (buttonThatWasClicked == toggleSendOsc)
    {
        //[UserButtonCode_toggleSendOsc] -- add your button handler code here..
		pEncoderSettings->oscSendFlag = toggleSendOsc->getToggleState();
        //[/UserButtonCode_toggleSendOsc]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void EncoderSettingsComponent::textEditorTextChanged(TextEditor& textEditor)
{
	if (&textEditor == textOscReceivePort)
		checkForNumbers(&textEditor, &pEncoderSettings->oscReceivePort);
	else if (&textEditor == textOscSendPort)
		checkForNumbers(&textEditor, &pEncoderSettings->oscSendPort);
	else if (&textEditor == textOscSendInterval)
		checkForNumbers(&textEditor, &pEncoderSettings->oscSendIntervalMs);
	else if(&textEditor == textOscSendIp)
	{
		pEncoderSettings->oscSendTargetHost = textEditor.getText();
	}
}

void EncoderSettingsComponent::showAsDialog(EncoderSettings* pSettings)
{
	EncoderSettingsComponent *p = new EncoderSettingsComponent(pSettings);
	p->setSize(500, 400);

	DialogWindow::LaunchOptions options;
	options.content.setOwned(p);
	options.dialogTitle = "Encoder-Plugin settings";
	options.dialogBackgroundColour = Colours::white;
	options.escapeKeyTriggersCloseButton = false;
	options.useNativeTitleBar = false;
	options.resizable = true;
	options.runModal();
}

void EncoderSettingsComponent::checkForNumbers(TextEditor* pEditor, int* pParameter) const
{
	if (pEditor->getText().containsOnly("0123456789"))
	{
		*pParameter = pEditor->getText().getIntValue();
	}
	else
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, JucePlugin_Name, "Invalid number");
		pEditor->undo();
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="EncoderSettingsComponent"
                 componentName="" parentClasses="public Component, public TextEditorListener"
                 constructorParams="EncoderSettings* pSettings" variableInitialisers="pEncoderSettings(pSettings)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="500" initialHeight="400">
  <BACKGROUND backgroundColour="ff505050"/>
  <GROUPCOMPONENT name="groupOscReceive" id="f4cf3a53a6ef0d87" memberName="groupOscReceive"
                  virtualName="" explicitFocusOrder="0" pos="2 5 8M 64" title="OSC Receive"/>
  <TOGGLEBUTTON name="toggleReceiveOsc" id="8d9b70b5bf27a026" memberName="toggleReceiveOsc"
                virtualName="" explicitFocusOrder="0" pos="18 29 150 24" buttonText="Enable"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="textOscReceivePort" id="ef3c7d2594795ec7" memberName="textOscReceivePort"
              virtualName="" explicitFocusOrder="0" pos="20Rr 24 105 24" posRelativeX="f4cf3a53a6ef0d87"
              posRelativeY="f4cf3a53a6ef0d87" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="labelOscPort" id="646c42f30e7e37d7" memberName="labelOscPort"
         virtualName="" explicitFocusOrder="0" pos="141Rr 29 109 24" posRelativeX="f4cf3a53a6ef0d87"
         edTextCol="ff000000" edBkgCol="0" labelText="OSC-Port:&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" kerning="0" bold="0" italic="0"
         justification="33"/>
  <GROUPCOMPONENT name="groupOscSend" id="6e42d11d1b0564d7" memberName="groupOscSend"
                  virtualName="" explicitFocusOrder="0" pos="1 77 8M 131" title="OSC Send"/>
  <TOGGLEBUTTON name="toggleSendOsc" id="309574c60d08c55e" memberName="toggleSendOsc"
                virtualName="" explicitFocusOrder="0" pos="17 101 150 24" buttonText="Enable"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="textOscSendIp" id="f5d167c87a68db4c" memberName="textOscSendIp"
              virtualName="" explicitFocusOrder="0" pos="21Rr 96 136 24" posRelativeX="f4cf3a53a6ef0d87"
              posRelativeY="f4cf3a53a6ef0d87" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="labelOscSendIp" id="ba6c86d4711d8bd0" memberName="labelOscSendIp"
         virtualName="" explicitFocusOrder="0" pos="165Rr 101 86 24" posRelativeX="f4cf3a53a6ef0d87"
         edTextCol="ff000000" edBkgCol="0" labelText="Target Host:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="textOscSendPort" id="c2dff2f42ed301d1" memberName="textOscSendPort"
              virtualName="" explicitFocusOrder="0" pos="21Rr 132 104 24" posRelativeX="f4cf3a53a6ef0d87"
              posRelativeY="f4cf3a53a6ef0d87" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="labelOscSendPort" id="3a8b128e5f4be049" memberName="labelOscSendPort"
         virtualName="" explicitFocusOrder="0" pos="141Rr 137 110 24"
         posRelativeX="f4cf3a53a6ef0d87" edTextCol="ff000000" edBkgCol="0"
         labelText="OSC-Port:&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="textOscSendInterval" id="2c20c78495fbd07c" memberName="textOscSendInterval"
              virtualName="" explicitFocusOrder="0" pos="21Rr 167 104 24" posRelativeX="f4cf3a53a6ef0d87"
              posRelativeY="f4cf3a53a6ef0d87" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="labelOscSendInterval" id="104391e6ca4d3f12" memberName="labelOscSendInterval"
         virtualName="" explicitFocusOrder="0" pos="141Rr 172 110 24"
         posRelativeX="f4cf3a53a6ef0d87" edTextCol="ff000000" edBkgCol="0"
         labelText="Interval [ms]:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
