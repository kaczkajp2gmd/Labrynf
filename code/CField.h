#pragma once

#include <cassert>
#include <irrlicht.h>
#include "CAnimator.h"
#include "SFieldCache.h"
#include "CGameObject.h"
#include "CObjectRune.h"
#include "CObjectOrb.h"

using namespace irr;
using namespace video;
using namespace gui;
using namespace core;

class Field : public IGUIElement
{ 
	ITexture* texture;
	const u32 PIXEL_SIZE;

	IGUIImage* image;
	GameObject* object;
    
	public:
		Field(u32 pixel_size, vector2d<s32> pos, ITexture* texture_, IGUIEnvironment* guienv_, IGUIElement* parent = NULL);
		Field(u32 pixel_size, FieldCache cache, vector2d<s32> pos, IVideoDriver* driver_, IGUIEnvironment* guienv_, IGUIElement* parent = NULL);
		~Field();
    
		void setCache(FieldCache cache, IVideoDriver* driver_, IGUIEnvironment* guienv_);

		bool				isBlank() const;
		GameObject*			getObject() const;
		u32					getSize() const;
		position2d<s32>		getPos() const;
		rect<s32>			getRect() const;
};