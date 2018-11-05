#pragma once

#include <cassert>
#include <sstream>
#include <irrlicht.h>
#include "CGameObject.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;


#define ANIM_IMAGES_COUNT_RUNE 5

class ObjectRune : public GameObject
{
	private:
		enum ANIM_RUNE
		{
			A_IDLE,
			A_ACTIVATED
		};

		ANIM_RUNE anim;
		bool activated;

		IVideoDriver* _driver;
		IGUIImage* image;

		ITexture* texture[ANIM_IMAGES_COUNT_RUNE];
		u32 tex_index;

	public:
		ObjectRune(rect<s32> rect, IVideoDriver* driver_, IGUIEnvironment* guienv, IGUIElement* parent, s32 id);
		~ObjectRune();

		void activate(bool b);
		void setAnim(ANIM_RUNE anim_);

		virtual void anim_update();
		virtual void showDebugInfo();

		bool isActive() const;
};