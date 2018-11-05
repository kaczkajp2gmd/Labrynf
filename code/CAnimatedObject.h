#pragma once

class AnimatedObject
{
		unsigned int delta_frame;
		
	public:
		AnimatedObject(unsigned int delta_frame_);
		~AnimatedObject();

		virtual void anim_update() = 0;

		virtual void setDeltaFrame(unsigned int df);
		virtual unsigned int getDeltaFrame() const;
		
		unsigned int last_time;
};