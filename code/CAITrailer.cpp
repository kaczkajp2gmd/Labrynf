#include "CAITrailer.h"

AITrailer::AITrailer(Character*& character_, T_MAP_CACHE*& map_, ITimer* timer_)
	: ArtificialIntelligence(character_, map_, timer_)
{

}

AITrailer::~AITrailer()
{

}

MOVE_DIRECTION AITrailer::plan_move(position2d<s32> from)
{
	if (player_pos != position2d<s32>(-1, -1))
		return stroll();
	else
		return goTo(from, player_pos);
}

MOVE_DIRECTION AITrailer::stroll()
{
	return MD_NONE;
}