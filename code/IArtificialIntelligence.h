#pragma once

#include <cassert>
#include <utility>
#include <irrlicht.h>
#include "EMoveDirection.h"
#include "CMapGenerator.h"
#include "CCharacter.h"

using namespace irr;
using namespace core;

class ArtificialIntelligence
{
	protected:
		ITimer* timer;
		position2d<s32> player_pos;
		Character* character;
		T_MAP_CACHE* map;

	public:
		ArtificialIntelligence(Character*& character, T_MAP_CACHE*& map_, ITimer* timer_);
		~ArtificialIntelligence();

			virtual void hearPlayer(position2d<s32> pos);
			virtual MOVE_DIRECTION plan_move(position2d<s32> from) = 0;
			virtual MOVE_DIRECTION goTo(position2d<s32> from, position2d<s32> pos);

	private:
		void findPath(position2d<s32> from, position2d<s32> to);
		void prepareForPathfinding(position2d<s32> from);
		
		position2d<s32> _pf_whereTo(position2d<s32> from, bool& junctionflag);
};