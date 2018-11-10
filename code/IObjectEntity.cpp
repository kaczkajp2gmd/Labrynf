#include "IObjectEntity.h"


ObjectEntity::ObjectEntity(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent, s32 id)
	:	GameObject(device, ((parent)? parent : device->getGUIEnvironment()->getRootGUIElement()), id, core::rect<s32>(0, 0, dimension.Width, dimension.Height), type, animfile.c_str())
{

}

ObjectEntity::~ObjectEntity()
{

}

void ObjectEntity::setMovementSpeed(u32 milisecs_per_mv)
{
	movement_speed = milisecs_per_mv;
}

u32 ObjectEntity::getMovementSpeed() const
{
	return movement_speed;
}

u32 ObjectEntity::getSize() const
{
	return image->getAbsolutePosition().getWidth();
}