#pragma once

#include <irrlicht.h>
#include <cmath>
#include "EMoveDirection.h"
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
	u32 _field_pixel_size;

	dimension2d<u32> screen_size;

	Dimer* dimer;
	Character* character;
	MapGenerator* mapgen;

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
		void refreshMap(position2d<s32> centerpos);
		
		bool objectToWallCollision(IGUIElement* obj);
		void handleGOCollision();
		
		bool hasField(int x, int y);
		position2d<s32> mapFieldPosToPosOnMap(int x, int y);
};