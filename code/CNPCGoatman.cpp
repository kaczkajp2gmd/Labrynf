#include "CNPCGoatman.h"

NPCGoatman::NPCGoatman(IrrlichtDevice* device, core::dimension2d<s32> dimension, core::stringc type, io::path animfile, IGUIElement* parent, s32 id)
	: ObjectEntity(device, dimension, type, animfile, parent, id)
{
	setAnim("IDLE");

	//ai = new AITrailer(device->getTimer());
}

NPCGoatman::~NPCGoatman()
{

}

void NPCGoatman::ai_update()
{

}