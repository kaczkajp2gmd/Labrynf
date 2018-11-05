#pragma once

#include <irrlicht.h>
#include <sstream>
#include <cassert>
#include "EGameObject.h"
#include "CGameObject.h"
#include "CEventHandler.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;

#define ANIM_IMAGES_COUNT_CHARACTER 26

class Character : public GameObject, public EventHandler
{
	private:
		IGUIStaticText* __debug_inventory;

		enum ANIM_CHARACTER
		{
			A_IDLE,
			A_WALK_R,
			A_WALK_L
		};

		array<GAME_OBJECT> inventory;

		IVideoDriver* _driver;

		ITexture* texture[ANIM_IMAGES_COUNT_CHARACTER];
		ANIM_CHARACTER anim;

		IGUIImage* image;
		u32 tex_index;
		u32 movement_speed;

	public:
		Character(u32 pixel_size, u32 milisecs_per_mv, IVideoDriver* driver_, IGUIEnvironment* guienv_);
		~Character();

		virtual void anim_update();
		virtual void react(CEventReceiver* receiver);
		virtual void showDebugInfo();

		void setMovementSpeed(u32 milisecs_per_mv);
		void setAnim(ANIM_CHARACTER anim);

		void	giveObject(GAME_OBJECT go);
		void	removeObject(GAME_OBJECT go);

		bool	hasObject(GAME_OBJECT go) const;
		u32		getMovementSpeed() const;
		u32		getSize() const;
};