#pragma once

#include "CGameObject.h"
#include <irrlicht.h>

using namespace irr;

class ObjectEntity : public GameObject
{
	protected:
		u32 movement_speed;

	public:	
		ObjectEntity(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent = NULL,  s32 id = -1);
		~ObjectEntity();

		void	setMovementSpeed(u32 milisecs_per_mv);

		u32		getMovementSpeed() const;
		u32		getSize() const;
};