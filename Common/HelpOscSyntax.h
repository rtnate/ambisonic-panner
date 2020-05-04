/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class HelpOscSyntax  : public Component
{
public:
    //==============================================================================
    HelpOscSyntax ();
    ~HelpOscSyntax() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void showInfo(String info);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void broughtToFront() override;
    void mouseUp (const MouseEvent& e) override;

    // Binary resources:
    static const char* osc_syntax_xml;
    static const int osc_syntax_xmlSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<XmlElement> treeXml;
    std::unique_ptr<TreeViewItem> rootItem;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TreeView> treeViewOscSyntax;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpOscSyntax)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

