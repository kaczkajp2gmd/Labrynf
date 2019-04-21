#include "IArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence(Character*& character_, T_MAP_CACHE*& map_, ITimer* timer_)
	: timer(timer_)
{
	character = character_;
	map = map_;
	player_pos.set(-1, -1);
}

ArtificialIntelligence::~ArtificialIntelligence()
{

}

void ArtificialIntelligence::hearPlayer(position2d<s32> pos)
{
	player_pos = pos;
}

MOVE_DIRECTION ArtificialIntelligence::goTo(position2d<s32> from, position2d<s32> pos)
{
	findPath(from, pos);

	int dist = map->operator[](pos.Y)[pos.X].pathf;

	if (from.Y - 1 >= 0 && map->operator[](from.Y - 1)[from.X].pathf == dist - 1)
		return MD_UP;
	if (from.X - 1 >= 0 && map->operator[](from.Y)[from.X - 1].pathf == dist - 1)
		return MD_LEFT;
	if (from.X + 1 < map->operator[](0).size() && map->operator[](from.Y)[from.X + 1].pathf == dist - 1)
		return MD_RIGHT;
	if (from.Y + 1 < map->size() && map->operator[](from.Y + 1)[from.X].pathf == dist - 1)
		return MD_DOWN;

	return MD_NONE;
}

void ArtificialIntelligence::findPath(position2d<s32> from, position2d<s32> to)
{
	prepareForPathfinding(from);

	core::array<std::pair<position2d<s32>, int>> junction;
	position2d<s32> next;

	bool junctionflag;
	int i = 0;
	int j_index = -1;

	do
	{
		next = _pf_whereTo(from, junctionflag);

		if (junctionflag)
			junction.push_back(std::pair<position2d<s32>, int> (from, i));

		if (next == position2d<s32>(0, 0))
		{
			if (j_index != -1)
				junction.erase(j_index);

			from = junction.getLast().first;
			i = junction.getLast().second;
			j_index = junction.size() - 1;
		}
		else
		{
			i++;
			from += next;
			map->operator[](from.Y)[from.X].pathf = i;
		}

	} while (junction.size());

}

void ArtificialIntelligence::prepareForPathfinding(position2d<s32> from)
{
	for (int y = 0; y < map->size(); y++)
		for (int x = 0; x < map[0].size(); x++)
			map->operator[](y)[x].pathf = (!map->operator[](y)[x].blank)? -1 : -2;		// Set -2 for walls and -1 for each another field


	assert(from != position2d<s32>(-1, -1));

	map->operator[](from.Y)[from.X].pathf = 0;
}

position2d<s32> ArtificialIntelligence::_pf_whereTo(position2d<s32> from, bool& junctionflag)
{
	int curr_val = map->operator[](from.Y)[from.X].pathf + 1;
	position2d<s32> pos(0, 0);

	junctionflag = false;

	if (from.Y - 1 >= 0 && (map->operator[](from.Y - 1)[from.X].pathf == -1 || map->operator[](from.Y - 1)[from.X].pathf > curr_val))
		if(pos == position2d<s32>(0, 0))
			pos = position2d<s32>(0, -1);

	if (from.X - 1 >= 0 && (map->operator[](from.Y)[from.X - 1].pathf == -1 || map->operator[](from.Y)[from.X - 1].pathf > curr_val))
		if (pos == position2d<s32>(0, 0))
			pos = position2d<s32>(-1, 0);
		else junctionflag = true;

	if (from.X + 1 < map->operator[](0).size() && (map->operator[](from.Y)[from.X + 1].pathf == -1 || map->operator[](from.Y)[from.X + 1].pathf > curr_val))
		if (pos == position2d<s32>(0, 0))
			pos = position2d<s32>(1, 0);
		else junctionflag = true;


	if (from.Y + 1 < map->size() && (map->operator[](from.Y + 1)[from.X].pathf == -1 || map->operator[](from.Y + 1)[from.X].pathf > curr_val))
		if (pos == position2d<s32>(0, 0))
			pos = position2d<s32>(0, 1);
		else junctionflag = true;

	return pos;
}