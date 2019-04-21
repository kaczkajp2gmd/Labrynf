#pragma once

#include <cassert>
#include "CObjectOrb.h"
#include "CObjectRune.h"
#include "CCharacter.h"
#include "CNPCGoatman.h"


class GameObjectFactory
{
	private:
		IrrlichtDevice* device;

	public:
		GameObjectFactory(IrrlichtDevice* device_);
		~GameObjectFactory();


		GameObject* instantiateGameObject(io::path filename, IGUIElement* parent = NULL, s32 ID = -1);
};