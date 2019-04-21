#pragma once

#include "IObjectEntity.h"
//#include "CAITrailer.h"

class NPCGoatman : public ObjectEntity
{
	public:
		NPCGoatman(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent, s32 id);
		~NPCGoatman();

		virtual void ai_update();
};