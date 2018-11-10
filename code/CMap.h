#pragma once

#include <irrlicht.h>
#include <cmath>
#include "CField.h"
#include "CDimer.h"
#include "CCharacter.h"
#include "IEventHandler.h"
#include "CMapGenerator.h"
#include "IDebugObject.h"
#include "CObjectRune.h"

using namespace irr;
using namespace video;

class Dimer;

class Map : public IGUIElement, public EventHandler, public DebugObject
{
	IGUIStaticText* __debug_position;
	IGUIStaticText* __debug_runes;
	IGUIStaticText* __debug_orbs;

	IVideoDriver* _driver;
	IGUIEnvironment* _guienv;

	T_MAP map;
	IGUIElement* Tiles;

	position2d<s32> delta_moved;
	position2d<s32> pos_on_map;
	u32 _field_pixel_size;

	dimension2d<u32> screen_size;

	Dimer* dimer;
	Character* character;
	MapGenerator* mapgen;
       
	public:

		enum MOVE_DIRECTION
		{
			MD_NONE,
			MD_UP,
			MD_DOWN,
			MD_LEFT,
			MD_RIGHT,
			MD_DOWN_RIGHT,
			MD_DOWN_LEFT,
			MD_UP_RIGHT,
			MD_UP_LEFT
		};

	private:
		MOVE_DIRECTION mv_direction;
	
	public:
		Map(u32 fov_radius, u32 field_pixel_size, IrrlichtDevice* device, dimension2d<u32>& screen_size_);
		~Map();

		void setCharacter(Character* character_);

		void moveToCenter();
		void move(MOVE_DIRECTION dir);

		virtual void react(CEventReceiver* receiver);
		virtual void showDebugInfo();

		Dimer*	getDimer() const;
		u32		getMapSize() const;
		
private:
		void refreshMap();
		
		bool characterToWallCollision();
		void handleGOCollision();
		
		bool hasField(int x, int y);
		position2d<s32> mapFieldPosToPosOnMap(int x, int y);
};