#include "CGameObject.h"

GameObject::GameObject(EGUI_ELEMENT_TYPE EGUIET_IMAGE, IGUIEnvironment* guienv, IGUIElement* parent, s32 id, core::rect<s32> rect, u32 anim_delta_frame, GAME_OBJECT_TYPE go_type_)
	: IGUIElement(EGUIET_IMAGE, guienv, parent, id, rect), AnimatedObject(anim_delta_frame), go_type(go_type_)
{

}

GameObject::~GameObject()
{

}

GAME_OBJECT_TYPE GameObject::getGOType() const
{
	return go_type;
}