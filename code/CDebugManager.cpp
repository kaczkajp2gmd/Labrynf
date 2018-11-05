#include "CDebugManager.h"

irr::core::array<DebugObject*> DebugManager::objects;

DebugManager::DebugManager()
{

}

DebugManager::~DebugManager()
{
	objects.clear();
}

void DebugManager::registerObject(DebugObject* obj)
{
	objects.push_back(obj);
}

void DebugManager::unregisterObject(DebugObject* obj)
{
	int index = objects.linear_search(obj);

	if (index != -1)
		objects.erase(index);
}


void DebugManager::displayDebugInfo()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->showDebugInfo();
}