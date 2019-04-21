#include "IObjectEntity.h"


ObjectEntity::ObjectEntity(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent, s32 id)
	:	GameObject(device, ((parent)? parent : device->getGUIEnvironment()->getRootGUIElement()), id, core::rect<s32>(0, 0, dimension.Width, dimension.Height), type, animfile.c_str()),
		_driver(device->getVideoDriver()), pos_on_map(0, 0)
{

}

ObjectEntity::~ObjectEntity()
{

}

void ObjectEntity::setPosOnMap(position2d<s32> pos)
{
	pos_on_map = pos;
}

void ObjectEntity::setTimePerField(f32 milisecs_per_field_)
{
	milisecs_per_field = milisecs_per_field_;
}

f32 ObjectEntity::getTimePerField() const
{
	return milisecs_per_field;
}

u32 ObjectEntity::getSize() const
{
	return image->getAbsolutePosition().getWidth();
}

position2d<s32> ObjectEntity::getPosOnMap() const
{
	return pos_on_map;
}

void ObjectEntity::showDebugInfo()
{
	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), SColor(255, 200, 200, 0));
}