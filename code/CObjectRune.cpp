#include "CObjectRune.h"

ObjectRune::ObjectRune(rect<s32> rect, IrrlichtDevice* device, IGUIElement* parent, s32 id, const char* animfile)
	: GameObject(device, parent, id, rect, "GOT_RUNE", animfile), _driver(device->getVideoDriver()), activated(false)
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

ObjectRune::~ObjectRune()
{
	
}

void ObjectRune::activate(bool b)
{
	if (b)
	{
		setAnim("ACTIVATED");
		activated = true;
	}
	else
	{
		setAnim("IDLE");
		activated = false;
	}
}

void ObjectRune::showDebugInfo()
{
	if (!IsVisible)
		return;

	SColor color;
	
	if (activated)
		color.set(255, 200, 0, 0);
	else
		color.set(255, 0, 200, 0);

	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), color);
}

bool ObjectRune::isActive() const
{
	return activated;
}