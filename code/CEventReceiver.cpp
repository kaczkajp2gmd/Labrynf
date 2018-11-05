#include "CEventReceiver.h"

CEventReceiver::CEventReceiver(IrrlichtDevice* device)
{
    _device = device;

    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool CEventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    if(event.EventType == EET_KEY_INPUT_EVENT)
    {
        bool ctrl = event.KeyInput.Control;
        bool shift = event.KeyInput.Shift;

		if (IsKeyDown(KEY_ESCAPE) && shift)
			_device->closeDevice();

		return true;
    }

    return false;
}

bool CEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}