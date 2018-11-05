#pragma once

#include <irrlicht.h>
#include "CDebugObject.h"

class DebugObject;

class DebugManager
{
private:
	static irr::core::array<DebugObject*> objects;

public:
	DebugManager();
	~DebugManager();

	static void registerObject(DebugObject* obj);
	static void unregisterObject(DebugObject* obj);
	static void displayDebugInfo();
};