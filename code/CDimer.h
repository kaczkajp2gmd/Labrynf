#pragma once

#include <irrlicht.h>
#include <sstream>
#include "CMap.h"
#include "CAnimatedObject.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::video;
using namespace irr::core;


class Map;

class Dimer : public AnimatedObject
{
	public:
		Dimer(Map* map, IrrlichtDevice* device);
		~Dimer();

		void setVisible(bool v);
		bool isVisible() const;
};