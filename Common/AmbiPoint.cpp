/*
  ==============================================================================

    AmbiPoint.cpp
    Created: 15 Oct 2018 5:46:32am
    Author:  Christian Schweizer

  ==============================================================================
*/

#include "AmbiPoint.h"
#include "LabelCreator.h"

AmbiPoint::AmbiPoint(AmbiPoint* other, bool copyImage): id(other->id), point(other->point), color(other->color), name(other->name), gain(other->gain), lastUpdate(other->lastUpdate)
{
	if (copyImage)
	{
		other->ensureLabelImage();
		if (other->labelImage != Image())
		{
			this->labelImage = Image(other->labelImage);
			this->labelImage.duplicateIfShared();
		}
	}
}

AmbiPoint::AmbiPoint(): color(Colour()), gain(1.0)
{
}

AmbiPoint::AmbiPoint(String id, Point3D<double> point, String name, Colour color, double gain):
	id(id),
	point(point),
	color(color),
	name(name),
	gain(gain)
{
}

AmbiPoint::AmbiPoint(XmlElement* element):
	id(Uuid().toString()),
	point(Point3D<double>(element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_X),
	                      element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_Y),
	                      element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_Z))),
	color(Colour(uint32(element->getIntAttribute(XML_ATTRIBUTE_PRESET_POINT_COLOR))).withAlpha(1.0f)),
	name(element->getStringAttribute(XML_ATTRIBUTE_PRESET_POINT_NAME)),
	gain(element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_GAIN, 1.0))
{
}

AmbiPoint::AmbiPoint(XmlElement* element, AudioParameterSet audioParams):
	id(Uuid().toString()),
	point(Point3D<double>(element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_X),
	                      element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_Y),
	                      element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_Z),
	                      audioParams)),
	color(Colour(uint32(element->getIntAttribute(XML_ATTRIBUTE_PRESET_POINT_COLOR))).withAlpha(1.0f)),
	name(element->getStringAttribute(XML_ATTRIBUTE_PRESET_POINT_NAME)),
	gain(element->getDoubleAttribute(XML_ATTRIBUTE_PRESET_POINT_GAIN, 1.0))
{
}

AmbiPoint::~AmbiPoint()
{
}

Point3D<double>* AmbiPoint::getPoint()
{
	return &point;
}

Colour AmbiPoint::getColor() const
{
	return color;
}

String AmbiPoint::getName() const
{
	return name;
}

void AmbiPoint::setName(String newName)
{
	if (name != newName)
	{
		labelImage = LabelCreator::createNewLabel(newName, color, FONT_SIZE);
	}

	name = newName;
}

double AmbiPoint::getGain() const
{
	return gain;
}

XmlElement* AmbiPoint::getAsXmlElement(String tagName)
{
	XmlElement* element = new XmlElement(tagName);
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_ID, getId());
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_X, getPoint()->getX());
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_Y, getPoint()->getY());
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_Z, getPoint()->getZ());
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_NAME, getName());
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_COLOR, int(getColor().getARGB()));
	element->setAttribute(XML_ATTRIBUTE_PRESET_POINT_GAIN, getGain());
	return element;
}

void AmbiPoint::setGain(double newGain)
{
	gain = newGain;
}

String AmbiPoint::getId()
{
	if (id.isEmpty())
	{
		id = Uuid().toString();
	}

	return id;
}

void AmbiPoint::setColor(Colour newColor)
{
	if (color != newColor)
	{
		labelImage = LabelCreator::createNewLabel(name, newColor, FONT_SIZE);
	}

	color = newColor;
}

bool AmbiPoint::checkAlive(int64 referenceTime, int timeout) const
{
	return (lastUpdate == 0 || referenceTime - lastUpdate < timeout);
}

void AmbiPoint::setAlive(int64 currentTimeMillis)
{
	lastUpdate = currentTimeMillis;
}

Image* AmbiPoint::getLabelImage()
{
	ensureLabelImage();
	return &labelImage;
}

void AmbiPoint::ensureLabelImage()
{
	if (labelImage == Image())
	{
		labelImage = LabelCreator::createNewLabel(name, color, FONT_SIZE);
		labelImage.duplicateIfShared();
	}
}
