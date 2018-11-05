#include "CSoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	audiodevice = OpenDevice();

	assert(audiodevice);
}

SoundPlayer::~SoundPlayer()
{

}

void SoundPlayer::playTheme(irr::io::path path)
{
	theme = OpenSound(audiodevice, path.c_str(), true);

	assert(theme);

	theme->setVolume(0.3);

	theme->setRepeat(true);

	theme->play();
}