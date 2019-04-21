#pragma once

#include "IArtificialIntelligence.h"

class AITrailer : public ArtificialIntelligence
{
	public:
		AITrailer(Character*& character_, T_MAP_CACHE*& map, ITimer* timer_);
		~AITrailer();

		virtual MOVE_DIRECTION plan_move(position2d<s32> from);
		virtual MOVE_DIRECTION stroll();
};