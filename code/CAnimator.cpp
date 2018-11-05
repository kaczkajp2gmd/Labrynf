#include "CAnimator.h"

Animator::Animator(ITimer* timer_)
	: timer(timer_)
{

}

Animator::~Animator()
{
	objects.clear();
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