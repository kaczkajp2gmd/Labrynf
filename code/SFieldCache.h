#pragma once

#include <irrlicht.h>

struct FieldCache
{
	FieldCache(bool blank_ = false)
	{
		blank = blank_;							//	Think of a "blank" field as a wall
		pathf = 0;								//	Defined for pathfinding needs
		texture_path = "media/plane.png";
		rune = false;
		activated = false;
		orb = false;
	}


	irr::io::path texture_path;
	bool blank;
	bool rune;
	bool activated;
	bool orb;
	int pathf;
};