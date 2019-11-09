/*
  ==============================================================================

    AmbiGroup.h
    Created: 5 Nov 2019 6:01:24pm
    Author:  chris

  ==============================================================================
*/

#pragma once
#include "AmbiPoint.h"
#include "AmbiSource.h"
#define XML_TAG_SUBPOINTS "SubPoints"
#define XML_TAG_SUBPOINT "SubPoint"
#define XML_ATTRIBUTE_GROUP_ID "Id"


class AmbiGroup : public AmbiPoint
{
public:
	AmbiGroup(String id, Point3D<double> point, String name, Colour color) : AmbiPoint(id, point, name, color) {}
	AmbiGroup(XmlElement* xmlElement, OwnedArray<AmbiSource>* pSources);
	virtual ~AmbiGroup() = default;

	float getDisplayScaler() override;
	XmlElement* getAsXmlElement(String tagName) override;
	void moveXYZ(double dx, double dy, double dz, bool moveSubElements);
	void setXYZ(double newX, double newY, double newZ, bool moveSubElements);

	Array<AmbiPoint*> groupPoints;
};
