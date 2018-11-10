#pragma once

#include <cassert>
#include <sstream>
#include <irrlicht.h>
#include "CGameObject.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;


class ObjectOrb : public GameObject
{
private:
	IVideoDriver* _driver;

public:
	ObjectOrb(rect<s32> rect, IrrlichtDevice* device, IGUIElement* parent, s32 id, const char* animfile);
	~ObjectOrb();

	virtual void showDebugInfo();
};
