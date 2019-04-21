#include "CCharacter.h"

Character::Character(u32 pixel_size, f32 milisecs_per_field, IrrlichtDevice* device)
	:  ObjectEntity(device, dimension2d<s32>(pixel_size, pixel_size), "GOT_CHARACTER", "character.anim", device->getGUIEnvironment()->getRootGUIElement(), -1),
	EventHandler(device->getTimer())
{
	setAnim("IDLE");
	setTimePerField(milisecs_per_field);

	__debug_inventory = device->getGUIEnvironment()->addStaticText(L"", rect<s32>(0, 200, 100, 400));
	__debug_inventory->setOverrideColor(SColor(255, 0, 200, 0));
	
	#ifndef __DEBUG_MODE__
		__debug_inventory->setVisible(false);
	#endif

	image = device->getGUIEnvironment()->addImage(rect<s32>(0, 0, this->getAbsolutePosition().getWidth(), this->getAbsolutePosition().getHeight()), this, -1);
	image->setImage(texture[0]);
	image->setScaleImage(true);
}

Character::~Character()
{

}

void Character::react(CEventReceiver* receiver)
{	
	if (!receiver->IsKeyDown(KEY_KEY_W) &&
		!receiver->IsKeyDown(KEY_KEY_S) &&
		!receiver->IsKeyDown(KEY_KEY_A) &&
		!receiver->IsKeyDown(KEY_KEY_D))
		this->setAnim("IDLE");

}

void Character::showDebugInfo()
{
	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), SColor(255, 200, 200, 0));

	stringw txt = L"Inventory:\n";

	for (int i = 0; i < inventory.size(); i++)
		txt += inventory[i];

	__debug_inventory->setText(txt.c_str());
}

void Character::giveObject(core::stringc go)
{
	inventory.push_back(go);
}

void Character::removeObject(core::stringc go)
{
	int index = inventory.linear_search(go);

	if(index != -1)
		inventory.erase(index);
}

bool Character::hasObject(core::stringc go) const
{
	return (inventory.linear_search(go) != -1);
}