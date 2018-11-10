#pragma once

#include <irrlicht.h>
#include "CAnimatedObject.h"

using namespace irr;

class AnimatedObject;

class Animator
{
	static core::array<AnimatedObject*> objects;

	static ITimer* timer;

	public:
		Animator();
		~Animator();

		static void setTimer(ITimer* t);
		static void registerObject(AnimatedObject* obj);
		static void unregisterObject(AnimatedObject* obj);
		static void update();
};