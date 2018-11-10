#include "SFieldCache.h"

FieldCache::FieldCache(bool blank_)
{
	blank = blank_;							//	Think of a "blank" field as a wall
	pathf = 0;								//	Defined for pathfinding needs
	texture = NULL;
	object = NULL;
}