#ifndef CEVENTRECEIVER_H
#define CEVENTRECEIVER_H

#include <irrlicht.h>

using namespace irr;
using namespace gui;
using namespace scene;
using namespace core;
using namespace video;


class CEventReceiver : public IEventReceiver
{
public:
    CEventReceiver(IrrlichtDevice* device);
    
    virtual bool OnEvent(const SEvent& event);
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    
    IrrlichtDevice* _device;
};


#endif

