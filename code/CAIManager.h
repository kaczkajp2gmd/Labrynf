#pragma once

#include <irrlicht.h>
#include "IIntelligentObject.h"

class IntelligentObject;

class AIManager
{
	private:
		static irr::core::array<IntelligentObject*> objects;

	public:
		AIManager();
		~AIManager();


		static void registerObject(IntelligentObject* obj);
		static void unregisterObject(IntelligentObject* obj);

		static void update();
};