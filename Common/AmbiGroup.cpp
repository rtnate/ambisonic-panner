/*
  ==============================================================================

    AmbiGroup.cpp
    Created: 5 Nov 2019 6:01:24pm
    Author:  chris

  ==============================================================================
*/

#include "AmbiGroup.h"

AmbiGroup::AmbiGroup(XmlElement* xmlElement, OwnedArray<AmbiSource>* pSources) : AmbiPoint(xmlElement)
{
	XmlElement* subPointsElement = xmlElement->getChildByName(XML_TAG_SUBPOINTS);
	groupPoints.clear();
	if (subPointsElement != nullptr)
	{
		XmlElement* xmlSubPoint = subPointsElement->getChildByName(XML_TAG_SUBPOINT);
		while (xmlSubPoint != nullptr)
		{
			String idStr = xmlSubPoint->getStringAttribute(XML_ATTRIBUTE_GROUP_ID);
			for (int i = 0; i < pSources->size(); i++)
			{
				if (pSources->getUnchecked(i)->getId() == idStr)
				{
					groupPoints.add(pSources->getUnchecked(i));
					break;
				}
			}

			xmlSubPoint = xmlSubPoint->getNextElement();
		}
	}
}

float AmbiGroup::getDisplayScaler()
{
	return 0.8f;
}

XmlElement* AmbiGroup::getAsXmlElement(String tagName)
{
	XmlElement* element = getBaseXmlElement(tagName);
	XmlElement* subPoints = element->createNewChildElement(XML_TAG_SUBPOINTS);
	for(int i = 0; i < groupPoints.size(); i++)
	{
		XmlElement* xmlPt = subPoints->createNewChildElement(XML_TAG_SUBPOINT);
		xmlPt->setAttribute(XML_ATTRIBUTE_GROUP_ID, groupPoints.getUnchecked(i)->getId());
	}
	return element;
}

void AmbiGroup::moveXYZ(double dx, double dy, double dz, bool moveSubElements)
{
	Point3D<double> p = *getPoint();
	getPoint()->setXYZ(p.getX() + dx, p.getY() + dy, p.getZ() + dz);

	if(moveSubElements)
	{
		for(AmbiPoint* sp : groupPoints)
		{
			sp->getPoint()->setXYZ(sp->getPoint()->getX() + dx, sp->getPoint()->getY() + dy, sp->getPoint()->getZ() + dz);
		}
	}
}

void AmbiGroup::setXYZ(double newX, double newY, double newZ, bool moveSubElements)
{
	double dx = newX - getPoint()->getX();
	double dy = newY - getPoint()->getY();
	double dz = newZ - getPoint()->getZ();

	getPoint()->setXYZ(newX, newY, newZ);

	if(moveSubElements)
	{
		for (AmbiPoint* p : groupPoints)
		{
			p->getPoint()->setXYZ(p->getPoint()->getX() + dx, p->getPoint()->getY() + dy, p->getPoint()->getZ() + dz);
		}
	}
}
