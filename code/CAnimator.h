#pragma once

#include <irrlicht.h>
#include "CAnimatedObject.h"

using namespace irr;

class Animator
{
	core::array<AnimatedObject*> objects;

	ITimer* timer;

	public:
		Animator(ITimer* timer_);
		~Animator();

		void registerObject(AnimatedObject* obj);
		void unregisterObject(AnimatedObject* obj);
		void update();
};