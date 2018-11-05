#pragma once

#include "CDebugManager.h"

class DebugObject
{
	public:
		DebugObject();
		~DebugObject();

		virtual void showDebugInfo() = 0;
};