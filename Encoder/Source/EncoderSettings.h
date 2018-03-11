/*
  ==============================================================================

    EncoderSettings.h
    Created: 26 Dec 2017 11:55:01pm
    Author:  Christian Schweizer

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#define DEFAULT_RECEIVE_FLAG		false
#define DEFALUT_RECEIVE_PORT		50001
#define DEFALUT_SEND_FLAG			true
#define DEFAULT_SEND_PORT			50000
#define DEFAULT_SEND_HOST			"127.0.0.1"
#define DEFAULT_SEND_INTERVAL		50
#define DEFAULT_DIST_ENC_FLAG		true
#define DEFAULT_UNIT_CIRCLE_SIZE	0.1f

class EncoderSettings
{
public:
	EncoderSettings();
	~EncoderSettings();
	XmlElement* getAsXmlElement(String tagName) const;
	void loadFromXml(XmlElement* xml_element);

public:
	bool oscReceiveFlag;
	int oscReceivePort;

	bool oscSendFlag;
	int oscSendPort;
	String oscSendTargetHost;
	int oscSendIntervalMs;

	bool distanceEncodingFlag;
	float unitCircleRadius;
};
