/*
  ==============================================================================

    EncoderSettings.cpp
    Created: 26 Dec 2017 11:55:01pm
    Author:  Christian Schweizer

  ==============================================================================
*/

#include "EncoderSettings.h"
#define XML_TAG_OSC_RECEIVE	"OscReceive"
#define XML_TAG_OSC_SEND "OscSend"
#define XML_TAG_OSC_SEND_EXT "OscSendExt"
#define XML_TAG_DISTANCE_ENCODING "DistanceEncoding"
#define XML_TAG_DOPPLER_ENCODING "DopplerEncoding"
#define XML_TAG_ORIENTATION "Orientation"
#define XML_ATTRIBUTE_ENABLE "Enable"
#define XML_ATTRIBUTE_PORT "Port"
#define XML_ATTRIBUTE_IP "Ip"
#define XML_ATTRIBUTE_INTERVAL "Interval"
#define XML_ATTRIBUTE_UNIT_CIRCLE_RADIUS "UnitCircleRadius"
#define XML_ATTRIBUTE_DIRECTION_FLIP "DirectionFlip"
#define XML_ATTRIBUTE_DISTANCE_SCALER "DistanceScaler"

EncoderSettings::EncoderSettings():
	oscReceiveFlag(DEFAULT_RECEIVE_FLAG),
	oscReceivePort(DEFALUT_RECEIVE_PORT),
	oscSendFlag(DEFALUT_SEND_FLAG),
	oscSendPort(DEFAULT_SEND_PORT),
	oscSendTargetHost(DEFAULT_SEND_HOST),
	oscSendIntervalMs(DEFAULT_SEND_INTERVAL),
	oscSendExtFlag(DEFALUT_SEND_EXT_FLAG), 
	oscSendExtPort(DEFAULT_SEND_EXT_PORT),
	oscSendExtTargetHost(DEFAULT_SEND_EXT_HOST),
	distanceEncodingFlag(DEFAULT_DIST_ENC_FLAG),
	dopplerEncodingFlag(DEFAULT_DOPPLER_ENC_FLAG),
	unitCircleRadius(DEFAULT_UNIT_CIRCLE_SIZE),
	AmbiBasicSettings(DEFAULT_DISTANCE_SCALER, DEFAULT_DIRECTION_FLIP)
{
}

EncoderSettings::~EncoderSettings()
{
}

XmlElement* EncoderSettings::getAsXmlElement(String tagName) const
{
	XmlElement* element = new XmlElement(tagName);

	XmlElement* oscReceive = new XmlElement(XML_TAG_OSC_RECEIVE);
	oscReceive->setAttribute(XML_ATTRIBUTE_ENABLE, oscReceiveFlag);
	oscReceive->setAttribute(XML_ATTRIBUTE_PORT, oscReceivePort);
	element->addChildElement(oscReceive);

	XmlElement* oscSend = new XmlElement(XML_TAG_OSC_SEND);
	oscSend->setAttribute(XML_ATTRIBUTE_ENABLE, oscSendFlag);
	oscSend->setAttribute(XML_ATTRIBUTE_PORT, oscSendPort);
	oscSend->setAttribute(XML_ATTRIBUTE_IP, oscSendTargetHost);
	oscSend->setAttribute(XML_ATTRIBUTE_INTERVAL, oscSendIntervalMs);
	element->addChildElement(oscSend);

	XmlElement* oscSendExt = new XmlElement(XML_TAG_OSC_SEND_EXT);
	oscSendExt->setAttribute(XML_ATTRIBUTE_ENABLE, oscSendExtFlag);
	oscSendExt->setAttribute(XML_ATTRIBUTE_PORT, oscSendExtPort);
	oscSendExt->setAttribute(XML_ATTRIBUTE_IP, oscSendExtTargetHost);
	element->addChildElement(oscSendExt);

	XmlElement* distanceEncoding = new XmlElement(XML_TAG_DISTANCE_ENCODING);
	distanceEncoding->setAttribute(XML_ATTRIBUTE_ENABLE, distanceEncodingFlag);
	distanceEncoding->setAttribute(XML_ATTRIBUTE_UNIT_CIRCLE_RADIUS, unitCircleRadius);
	element->addChildElement(distanceEncoding);

	XmlElement* dopplerEncoding = new XmlElement(XML_TAG_DOPPLER_ENCODING);
	dopplerEncoding->setAttribute(XML_ATTRIBUTE_ENABLE, dopplerEncodingFlag);
	dopplerEncoding->setAttribute(XML_ATTRIBUTE_DISTANCE_SCALER, getDistanceScaler());
	element->addChildElement(dopplerEncoding);

	XmlElement* orientation = new XmlElement(XML_TAG_ORIENTATION);
	orientation->setAttribute(XML_ATTRIBUTE_DIRECTION_FLIP, getDirectionFlip());
	element->addChildElement(orientation);

	return element;
}

void EncoderSettings::loadFromXml(XmlElement* element)
{
	if (element == nullptr)
		return;

	XmlElement* oscReceive = element->getChildByName(XML_TAG_OSC_RECEIVE);
	oscReceiveFlag = oscReceive->getBoolAttribute(XML_ATTRIBUTE_ENABLE, DEFAULT_RECEIVE_FLAG);
	oscReceivePort = oscReceive->getIntAttribute(XML_ATTRIBUTE_PORT, DEFALUT_RECEIVE_PORT);
	
	XmlElement* oscSend = element->getChildByName(XML_TAG_OSC_SEND);
	oscSendFlag = oscSend->getBoolAttribute(XML_ATTRIBUTE_ENABLE, DEFALUT_SEND_FLAG);
	oscSendPort = oscSend->getIntAttribute(XML_ATTRIBUTE_PORT, DEFAULT_SEND_PORT);
	oscSendTargetHost = oscSend->getStringAttribute(XML_ATTRIBUTE_IP, DEFAULT_SEND_HOST);
	oscSendIntervalMs = oscSend->getIntAttribute(XML_ATTRIBUTE_INTERVAL, DEFAULT_SEND_INTERVAL);

	XmlElement* oscSendExt = element->getChildByName(XML_TAG_OSC_SEND_EXT);
	if (oscSendExt != nullptr)
	{
		oscSendExtFlag = oscSendExt->getBoolAttribute(XML_ATTRIBUTE_ENABLE, DEFALUT_SEND_EXT_FLAG);
		oscSendExtPort = oscSendExt->getIntAttribute(XML_ATTRIBUTE_PORT, DEFAULT_SEND_EXT_PORT);
		oscSendExtTargetHost = oscSendExt->getStringAttribute(XML_ATTRIBUTE_IP, DEFAULT_SEND_EXT_HOST);
	}

	XmlElement* distanceEncoding = element->getChildByName(XML_TAG_DISTANCE_ENCODING);
	if(distanceEncoding != nullptr)
	{
		distanceEncodingFlag = distanceEncoding->getBoolAttribute(XML_ATTRIBUTE_ENABLE, DEFAULT_DIST_ENC_FLAG);
		unitCircleRadius = float(distanceEncoding->getDoubleAttribute(XML_ATTRIBUTE_UNIT_CIRCLE_RADIUS, DEFAULT_UNIT_CIRCLE_SIZE));
	}

	XmlElement* dopplerEncoding = element->getChildByName(XML_TAG_DOPPLER_ENCODING);
	if(dopplerEncoding != nullptr)
	{
		dopplerEncodingFlag = dopplerEncoding->getBoolAttribute(XML_ATTRIBUTE_ENABLE, DEFAULT_DOPPLER_ENC_FLAG);
		setDistanceScaler(float(dopplerEncoding->getDoubleAttribute(XML_ATTRIBUTE_DISTANCE_SCALER, DEFAULT_DISTANCE_SCALER)));
	}

	XmlElement* orientation = element->getChildByName(XML_TAG_ORIENTATION);
	if(orientation != nullptr)
	{
		setDirectionFlip(orientation->getBoolAttribute(XML_ATTRIBUTE_DIRECTION_FLIP, DEFAULT_DIRECTION_FLIP));
	}
}
