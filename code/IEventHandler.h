#pragma once

#include "CEventReceiver.h"
#include <irrlicht.h>

class CEventReceiver;

class EventHandler
{
	protected:
		ITimer*	timer;
		u32 time_last;

	public:
		EventHandler(ITimer* timer_);
		~EventHandler();

		virtual void react(CEventReceiver* receiver) = 0;
};