#include <iostream>
#include <irrlicht.h>
#include "CEventReceiver.h"
#include "CMap.h"
#include "CAnimator.h"
#include "CCharacter.h"
#include "CSoundPlayer.h"

using namespace std;

using namespace irr;
using namespace gui;
using namespace scene;
using namespace core;
using namespace video;

int main()
{
	IrrlichtDevice* setup_device = createDevice(EDT_NULL);
	dimension2d<u32> screen_size = setup_device->getVideoModeList()->getDesktopResolution();
    
	setup_device->drop();
    
	IrrlichtDevice* device = createDevice(EDT_OPENGL, screen_size, 32, true);
    
	ISceneManager*   smgr   = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	IVideoDriver*    driver = device->getVideoDriver();

	guienv->getSkin()->setFont(guienv->getFont("media/fontcourier.bmp"));

	#ifdef __DEBUG_MODE__
		IGUIStaticText* fps = guienv->addStaticText(L"FPS: ", rect<s32>(screen_size.Width - 100, 5, screen_size.Width, 20));
		fps->setTextAlignment(EGUIA_LOWERRIGHT, EGUIA_CENTER);
		fps->setOverrideColor(SColor(255, 255, 255, 255));
		stringw fps_txt;
	#endif

	Animator::setTimer(device->getTimer());

	Map map(5, 128, device, screen_size);

	GameObjectFactory f(device);

	Character* character = (Character*) f.instantiateGameObject("media/character.gobj");
	map.setCharacter(character);

    CEventReceiver receiver(device);
	device->setEventReceiver(&receiver);

	SoundPlayer sound;
	sound.playTheme("media/theme0.mp3");


	while(device->run())
	{
		driver->beginScene(true, false, SColor(255, 0, 0, 0));
        
		Animator::update();

		character->react(&receiver);
		map.react(&receiver);

		guienv->drawAll();
		smgr->drawAll();

		#ifdef __DEBUG_MODE__
			DebugManager::displayDebugInfo();
			fps_txt = L"FPS: ";
			fps_txt += driver->getFPS();
			fps->setText(fps_txt.c_str());
		#endif
        
		driver->endScene();
	}
    
	device->drop();
    
	return 0;
}