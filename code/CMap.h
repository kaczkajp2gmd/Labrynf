#pragma once

#include <irrlicht.h>
#include <cmath>
#include "EGameObject.h"
#include "CField.h"
#include "CDimer.h"
#include "CCharacter.h"
#include "CEventHandler.h"
#include "CMapGenerator.h"
#include "CDebugObject.h"
#include "CObjectRune.h"

using namespace irr;
using namespace video;

class Dimer;

class Map : public IGUIElement, public EventHandler, public AnimatedObject, public DebugObject
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
	Animator* animator;
	Character* character;
	MapGenerator* mapgen;
       
	public:

		enum MOVE_DIRECTION
		{
			MD_NONE,
			MD_UP,
			MD_DOWN,
			MD_LEFT,
			MD_RIGHT
		};

	private:
		MOVE_DIRECTION mv_direction;
	
	public:
		Map(u32 fov_radius, u32 field_pixel_size, Animator* animator_, IVideoDriver* driver_, IGUIEnvironment* guienv_, dimension2d<u32>& screen_size_);
		~Map();

		void setCharacter(Character* character_);

		void moveToCenter();
		void move(MOVE_DIRECTION dir);

		virtual void react(CEventReceiver* receiver);
		virtual void anim_update();
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