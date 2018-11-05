#pragma once

#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <irrlicht.h>
#include "SFieldCache.h"
#include "CField.h"
#include "EExceptions.h"

// MAP GENERATION ALGORITM PARAMETERS:

#define MAX_WALLSIZE 0.2	// AS PROPORTION TO MAP SIZE



typedef irr::core::array<irr::core::array<Field*>> T_MAP;

typedef irr::core::array<irr::core::array<FieldCache>> T_MAP_CACHE;

class MapGenerator
{
	private:
		T_MAP_CACHE current_map;
		core::array<position2d<s32>> runes;
		core::array<position2d<s32>> orbs;

	public:
		MapGenerator();
		~MapGenerator();

		void createMap(u32 size, bool serialize = false, io::path path = "");
		void serializeCurrentMap(io::path path);
		
		void deleteOrb(position2d<s32> orbpos);
		void activateRune(position2d<s32> runepos);
		
		bool							hasField(int x, int y);
		FieldCache						getFieldCache(int x, int y);
		position2d<s32>					getStartPoint();
		core::array<position2d<s32>>	getRunesPosArr();
		core::array<position2d<s32>>	getOrbsPosArr();

	private:
		void generate(T_MAP_CACHE& map);
		void setRunesAndOrbs(u32 howMany);

		inline bool checkBorder(int x, int y, T_MAP_CACHE& map) const;
		inline bool hasNeighbourWall(int x, int y, T_MAP_CACHE& map);
};