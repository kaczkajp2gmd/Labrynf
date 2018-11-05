#pragma once

#include <assert.h>
#include <audiere.h>
#include <irrlicht.h>

using namespace audiere;

class SoundPlayer
{
	private:
		AudioDevicePtr audiodevice;
		OutputStreamPtr theme;

	public:
		SoundPlayer();
		~SoundPlayer();

		void playTheme(irr::io::path path);
};