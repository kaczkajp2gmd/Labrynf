#pragma once

#include <irrlicht.h>
#include "CAnimatedObject.h"
#include "IDebugObject.h"

using namespace irr;
using namespace gui;


class GameObject : public IGUIElement, public AnimatedObject, public DebugObject
{
	private:
		core::stringc go_type;

	public:
		GameObject(IrrlichtDevice* device, IGUIElement* parent, s32 id, core::rect<s32> rect, core::stringc go_type_, const char* animfile);
		~GameObject();

		void setParent(IGUIElement* parent);

		core::stringc getGOType() const;
};