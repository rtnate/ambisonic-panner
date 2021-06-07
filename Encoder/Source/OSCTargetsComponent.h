/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "EncoderSettings.h"
#include "CustomOscTableListModel.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OSCTargetsComponent  : public juce::Component,
                             public ChangeBroadcaster,
                             public TextEditor::Listener,
                             public ActionListener,
                             public juce::Slider::Listener,
                             public juce::Button::Listener
{
public:
    //==============================================================================
    OSCTargetsComponent (ChangeListener* pChangeListener, EncoderSettings* pSettings);
    ~OSCTargetsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged(TextEditor&) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

    // Binary resources:
    static const char* help_png;
    static const int help_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void controlDimming();
    void actionListenerCallback(const String& message) override;
    EncoderSettings* pSettings;
    std::unique_ptr<CustomOscTableListModel> customOscTableModel;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> groupTargets;
    std::unique_ptr<TableListBox> targetList;
    std::unique_ptr<juce::Slider> sliderInterval;
    std::unique_ptr<juce::Label> labelInterval;
    std::unique_ptr<juce::TextButton> btnAdd;
    std::unique_ptr<juce::TextButton> btnDelete;
    std::unique_ptr<juce::ImageButton> btnInfo;
    std::unique_ptr<juce::ToggleButton> toggleSendContinuous;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCTargetsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

