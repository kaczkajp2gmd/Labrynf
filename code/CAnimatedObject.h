#pragma once

#include <irrlicht.h>
#include <cassert>
#include <iostream>
#include <string>
#include "CAnimator.h"

using namespace irr;
using namespace video;

class AnimatedObject
{
	private:
		struct Animation
		{
			core::stringc anim_tag;
			u32 start_frame;
			u32 end_frame;
			u32 delta_frame;
		};

	protected:
		u32 TEXTURE_COUNT;
		u32 delta_frame;
		core::array<ITexture*> texture;
		core::array<Animation> anims;

		s32 tex_index;
		s32 anim_index;

		gui::IGUIImage* image;
		
	public:
		AnimatedObject(io::path filename, IVideoDriver* driver_, io::IFileSystem* fs);
		~AnimatedObject();

		void anim_update();

		void	setAnim(core::stringc anim_tag);
		void	setDeltaFrame(unsigned int df);
		u32		getDeltaFrame() const;
		
		u32		last_time;
};