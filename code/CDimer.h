#pragma once

#include <irrlicht.h>
#include <sstream>
#include "CMap.h"
#include "CAnimatedObject.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::video;
using namespace irr::core;

#define ANIM_IMAGES_COUNT_DIMER 4

class Map;

class Dimer : public AnimatedObject
{
	ITexture* texture[ANIM_IMAGES_COUNT_DIMER];
	u32 tex_index;

	IGUIImage* image;

	public:
		Dimer(Map* map, IVideoDriver* driver_, IGUIEnvironment* guienv_);
		~Dimer();

		virtual void anim_update();

		void setVisible(bool v);
		bool isVisible() const;
};