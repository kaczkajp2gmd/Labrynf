#include "IIntelligentObject.h"


IntelligentObject::IntelligentObject()
{
	AIManager::registerObject(this);
}

IntelligentObject::~IntelligentObject()
{
	AIManager::unregisterObject(this);
}