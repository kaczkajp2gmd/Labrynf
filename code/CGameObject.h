#pragma once

#include <irrlicht.h>
#include "EGameObject.h"
#include "CAnimatedObject.h"
#include "CDebugObject.h"

using namespace irr;
using namespace gui;


class GameObject : public IGUIElement, public AnimatedObject, public DebugObject
{
	private:
		GAME_OBJECT_TYPE go_type;

	public:
		GameObject(EGUI_ELEMENT_TYPE EGUIET_IMAGE, IGUIEnvironment* guienv, IGUIElement* parent, s32 id, core::rect<s32> rect, u32 anim_delta_frame, GAME_OBJECT_TYPE go_type_);
		~GameObject();

		GAME_OBJECT_TYPE getGOType() const;
};