#include "CAnimator.h"

core::array<AnimatedObject*> Animator::objects;
ITimer* Animator::timer = NULL;

Animator::Animator()
{

}

Animator::~Animator()
{
	objects.clear();
}

void Animator::setTimer(ITimer* t)
{
	timer = t;
}

void Animator::registerObject(AnimatedObject* obj)
{
	objects.push_back(obj);
}

void Animator::unregisterObject(AnimatedObject* obj)
{
	s32 index = objects.linear_search(obj);

	if(index != -1)
		objects.erase(index);
}

void Animator::update()
{
	if (!timer)
		return;

	u32 time_now = timer->getTime();
	
	for (int i = 0; i < objects.size(); i++)
	{
		if (time_now - objects[i]->last_time >= objects[i]->getDeltaFrame())
		{
			objects[i]->anim_update();

			objects[i]->last_time = time_now;
		}
	}
}