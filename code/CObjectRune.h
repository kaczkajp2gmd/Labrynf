#pragma once

#include <cassert>
#include <sstream>
#include <irrlicht.h>
#include "CGameObject.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;


class ObjectRune : public GameObject
{
	private:
		bool activated;
		IVideoDriver* _driver;

	public:
		ObjectRune(rect<s32> rect, IrrlichtDevice* device, IGUIElement* parent, s32 id, const char* animfile);
		~ObjectRune();

		void activate(bool b);

		virtual void showDebugInfo();

		bool isActive() const;
};