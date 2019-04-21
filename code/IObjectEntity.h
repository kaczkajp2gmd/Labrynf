#pragma once

#include "CGameObject.h"
#include <irrlicht.h>

using namespace irr;
using namespace core;

class ObjectEntity : public GameObject
{
	protected:
		IVideoDriver* _driver;

		f32 milisecs_per_field;
		position2d<s32> pos_on_map;

	public:	
		ObjectEntity(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent = NULL,  s32 id = -1);
		~ObjectEntity();

		void	setPosOnMap(position2d<s32> pos);
		void	setTimePerField(f32 milisecs_per_field_);

		f32				getTimePerField() const;
		u32				getSize() const;
		position2d<s32> getPosOnMap() const;

		virtual void showDebugInfo();
};