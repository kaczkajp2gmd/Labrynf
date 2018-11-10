#pragma once

#include <irrlicht.h>
#include "CGameObject.h"

struct FieldCache
{
	FieldCache(bool blank_ = false);

	irr::video::ITexture*	texture;
	GameObject* object;
	bool blank;
	int pathf;
};