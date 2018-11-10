#pragma once

#include <irrlicht.h>
#include <sstream>
#include <cassert>
#include "IObjectEntity.h"
#include "IEventHandler.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;

class Character : public ObjectEntity, public EventHandler
{
	private:
		IGUIStaticText* __debug_inventory;

		array<core::stringc> inventory;

		IVideoDriver* _driver;

	public:
		Character(u32 pixel_size, u32 milisecs_per_mv, IrrlichtDevice* device);
		~Character();


		virtual void react(CEventReceiver* receiver);
		virtual void showDebugInfo();

		void	giveObject(core::stringc go);
		void	removeObject(core::stringc go);
		bool	hasObject(core::stringc go) const;
};