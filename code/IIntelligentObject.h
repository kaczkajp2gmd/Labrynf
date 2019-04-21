#pragma once

#include "CAIManager.h"

//class ArtificialIntelligence;

class IntelligentObject
{
	protected:
		//ArtificialIntelligence* ai;

	public:
		IntelligentObject();
		~IntelligentObject();

		virtual void ai_update() = 0;
};