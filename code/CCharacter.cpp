#include "CCharacter.h"

Character::Character(u32 pixel_size, u32 milisecs_per_mv, IVideoDriver* driver_, IGUIEnvironment* guienv_)
	:  GameObject(EGUIET_IMAGE, guienv_, guienv_->getRootGUIElement(), GO_CHARACTER, rect<s32>(0, 0, pixel_size, pixel_size), 1500, GOT_CHARACTER), EventHandler(), _driver(driver_), tex_index(0), movement_speed(milisecs_per_mv)
{

	__debug_inventory = guienv_->addStaticText(L"", rect<s32>(0, 200, 100, 400));
	__debug_inventory->setOverrideColor(SColor(255, 0, 200, 0));
	
	#ifndef __DEBUG_MODE__
		__debug_inventory->setVisible(false);
	#endif
	
	io::path path = "media/character";
	std::ostringstream buff;

	for (int i = 0; i < ANIM_IMAGES_COUNT_CHARACTER; i++)
	{
		buff.str("");
		buff.clear();
		buff << i;

		texture[i] = driver_->getTexture(path + buff.str().c_str() + ".png");

		assert(texture[i]);
	}

	image = guienv_->addImage(rect<s32>(0, 0, this->getAbsolutePosition().getWidth(), this->getAbsolutePosition().getHeight()), this, -1);
	image->setImage(texture[0]);
	image->setScaleImage(true);

	setAnim(A_IDLE);
}

Character::~Character()
{

}

void Character::anim_update()
{
	if (anim == A_IDLE)
	{
		if (tex_index >= 2)
			tex_index %= 2;
	}

	else if (anim == A_WALK_R)
	{
		if (tex_index >= 14)
		{
			tex_index %= 14;
			tex_index += 2;
		}
	}

	else if (anim == A_WALK_L)
	{
		if (tex_index >= 25)
		{
			tex_index %= 25;
			tex_index += 14;
		}
	}

	image->setImage(texture[tex_index]);
	tex_index++;
}

void Character::react(CEventReceiver* receiver)
{	
	if (receiver->IsKeyDown(KEY_KEY_W))
	{
		this->setAnim(A_WALK_R);
	}
	else if (receiver->IsKeyDown(KEY_KEY_S))
	{
		this->setAnim(A_WALK_R);
	}
	else if (receiver->IsKeyDown(KEY_KEY_A))
	{
		this->setAnim(A_WALK_L);
	}
	else if (receiver->IsKeyDown(KEY_KEY_D))
	{
		this->setAnim(A_WALK_R);
	}
	else
		this->setAnim(A_IDLE);

}

void Character::showDebugInfo()
{
	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), SColor(255, 200, 200, 0));

	stringw txt = L"Inventory:\n";

	for (int i = 0; i < inventory.size(); i++)
		txt += inventory[i];

	__debug_inventory->setText(txt.c_str());
}

void Character::setMovementSpeed(u32 milisecs_per_mv)
{
	movement_speed = milisecs_per_mv;
}

void Character::setAnim(ANIM_CHARACTER anim_)
{
	if (anim == anim_)
		return;

	anim = anim_;
	last_time = 0;

	if (anim == A_IDLE)
	{
		setDeltaFrame(1500);
		tex_index = 0;
	}

	else if (anim == A_WALK_R)
	{
		setDeltaFrame(60);
		tex_index = 2;
	}

	else if (anim == A_WALK_L)
	{
		setDeltaFrame(60);
		tex_index = 14;
	}
}

void Character::giveObject(GAME_OBJECT go)
{
	inventory.push_back(go);
}

void Character::removeObject(GAME_OBJECT go)
{
	int index = inventory.linear_search(go);

	if(index != -1)
		inventory.erase(index);
}

bool Character::hasObject(GAME_OBJECT go) const
{
	return (inventory.linear_search(go) != -1);
}

u32 Character::getMovementSpeed() const
{
	return movement_speed;
}

u32 Character::getSize() const
{
	return image->getAbsolutePosition().getWidth();
}