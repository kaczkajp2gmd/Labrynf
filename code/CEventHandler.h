#pragma once

#include "CEventReceiver.h"

class CEventReceiver;

class EventHandler
{
	public:
		EventHandler();
		~EventHandler();

		virtual void react(CEventReceiver* receiver) = 0;
};