#include "IDebugObject.h"

DebugObject::DebugObject()
{
	DebugManager::registerObject(this);
}

DebugObject::~DebugObject()
{
	DebugManager::unregisterObject(this);
}