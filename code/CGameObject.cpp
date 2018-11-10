#include "CGameObject.h"

GameObject::GameObject(IrrlichtDevice* device, IGUIElement* parent, s32 id, core::rect<s32> rect, core::stringc go_type_, const char* animfile)
	: IGUIElement(EGUIET_IMAGE, device->getGUIEnvironment(), parent, id, rect), AnimatedObject(animfile, device->getVideoDriver(), device->getFileSystem()), go_type(go_type_)
{

}

GameObject::~GameObject()
{
	remove();
}

void GameObject::setParent(IGUIElement* parent)
{
	this->grab();

	if (Parent && Parent != parent)
		this->remove();

	Parent = parent;

	if (Parent != NULL)
		Parent->addChild(this);
	
	this->drop();
}

core::stringc GameObject::getGOType() const
{
	return go_type;
}