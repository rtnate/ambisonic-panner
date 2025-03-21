/*
================================================================================
    This file is part of the ICST AmbiPlugins.

    ICST AmbiPlugins are free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ICST AmbiPlugins are distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the ICSTAmbiPlugins.  If not, see <http://www.gnu.org/licenses/>.
================================================================================
*/



#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../../Common/AmbiSourceSet.h"

#define CHECKBOX_HEIGHT 25
#define COMPONENT_WIDTH 200


class SpeakerSelectionComponent    : public Component, public ToggleButton::Listener, ChangeBroadcaster
{
public:
    SpeakerSelectionComponent(AmbiDataSet* _pSources, uint64_t* _pSpeakerMask, ChangeListener* pListener): pSources(_pSources), pSpeakerMask(_pSpeakerMask)
    {
	    // In your constructor, you should add any child components, and
	    // initialise any special settings that your component needs.
		
    	this->addChangeListener(pListener);
		
        columnCount = (int)std::ceil(pSources->size() / 16.0);
        rowCount = columnCount > 0 ?  (int)(std::ceil(pSources->size() / (double)columnCount)) : 0;
        
		for (int i = 0; i < pSources->size(); i++)
		{
            AmbiPoint* s = pSources->get(i);
            String label = String(i+1) + (s->getName() != String(i + 1) ? (": " + s->getName()) : "");
			ToggleButton* b = new ToggleButton(label);
            bool enabled = s->getEnabled();
            b->setEnabled(enabled);
            b->setToggleState(enabled && ((*pSpeakerMask) & (static_cast<unsigned long long>(1) << (i))), dontSendNotification);
            b->addListener(this);
			toggleButtons.add(b);
			addAndMakeVisible(b);
		}

		setSize(COMPONENT_WIDTH * columnCount, rowCount * CHECKBOX_HEIGHT);
    }

	~SpeakerSelectionComponent() override
    {
		deleteAllChildren();
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    }

    void resized() override
    {
        int index = 0;

		for(ToggleButton* b : toggleButtons)
		{
			b->setBounds((int)(std::floor(index / rowCount) * COMPONENT_WIDTH), (index % rowCount) * CHECKBOX_HEIGHT , COMPONENT_WIDTH, CHECKBOX_HEIGHT);
            index++;
		}
    }

	void buttonClicked(Button* b) override
	{
		int index = toggleButtons.indexOf(static_cast<ToggleButton*>(b));
		
		if(index >= 0)
		{
            *pSpeakerMask = *pSpeakerMask ^ (static_cast<unsigned long long>(1) << index);

			sendChangeMessage();
		}
	}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpeakerSelectionComponent)

	AmbiDataSet* pSources;
	Array<ToggleButton*> toggleButtons;
    uint64_t* pSpeakerMask;
    int columnCount;
    int rowCount;
};
