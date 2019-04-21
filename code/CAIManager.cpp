#include "CAIManager.h"

irr::core::array<IntelligentObject*> AIManager::objects;

AIManager::AIManager()
{

}

AIManager::~AIManager()
{

}

void AIManager::registerObject(IntelligentObject* object)
{
	if (object)
		objects.push_back(object);
}

void AIManager::unregisterObject(IntelligentObject* object)
{
	int index = objects.linear_search(object);

	if (index != -1)
		objects.erase(index);
}

void AIManager::update()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->ai_update();
}