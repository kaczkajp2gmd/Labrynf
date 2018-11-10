#include "CObjectOrb.h"

ObjectOrb::ObjectOrb(rect<s32> rect, IrrlichtDevice* device, IGUIElement* parent, s32 id, const char* animfile)
	: GameObject(device, parent, id, rect, "GOT_ORB", animfile), _driver(device->getVideoDriver())
{
	setAnim("IDLE");

	image = device->getGUIEnvironment()->addImage(rect, this);

	assert(image);
	assert(texture[0]);

	image->setImage(texture[0]);

	image->setUseAlphaChannel(true);
	image->setScaleImage(true);

	this->setVisible(false);
}

ObjectOrb::~ObjectOrb()
{

}


void ObjectOrb::showDebugInfo()
{
	if (!IsVisible)
		return;

	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), SColor(255, 0, 200, 0));
}