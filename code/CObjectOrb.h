#pragma once

#include <cassert>
#include <sstream>
#include <irrlicht.h>
#include "CGameObject.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;


#define ANIM_IMAGES_COUNT_ORB 3

class ObjectOrb : public GameObject
{
private:
	enum ANIM_ORB
	{
		A_IDLE
	};

	ANIM_ORB anim;

	IVideoDriver* _driver;
	IGUIImage* image;

	ITexture* texture[ANIM_IMAGES_COUNT_ORB];
	u32 tex_index;

public:
	ObjectOrb(rect<s32> rect, IVideoDriver* driver_, IGUIEnvironment* guienv, IGUIElement* parent, s32 id);
	~ObjectOrb();

	void setAnim(ANIM_ORB anim_);

	virtual void anim_update();
	virtual void showDebugInfo();
};
