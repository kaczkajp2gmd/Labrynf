#include "IEventHandler.h"

EventHandler::EventHandler(ITimer* timer_)
	: timer(timer_), time_last(0)
{

}

EventHandler::~EventHandler()
{

}