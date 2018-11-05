#include "CAnimatedObject.h"

AnimatedObject::AnimatedObject(unsigned int delta_frame_)
	: delta_frame(delta_frame_), last_time(0)
{

}

AnimatedObject::~AnimatedObject()
{

}

void AnimatedObject::setDeltaFrame(unsigned int df)
{
	delta_frame = df;
}

unsigned int AnimatedObject::getDeltaFrame() const
{
	return delta_frame;
}