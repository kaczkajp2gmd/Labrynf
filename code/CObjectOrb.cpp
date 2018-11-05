#include "CObjectOrb.h"

ObjectOrb::ObjectOrb(rect<s32> rect, IVideoDriver* driver_, IGUIEnvironment* guienv, IGUIElement* parent, s32 id)
	: GameObject(EGUIET_IMAGE, guienv, parent, id, rect, 100, GOT_ORB), _driver(driver_), anim(A_IDLE),
	tex_index(0)
{
	io::path path = "media/orb_green_";
	std::ostringstream buff;

	for (int i = 0; i < ANIM_IMAGES_COUNT_ORB; i++)
	{
		buff.str("");
		buff.clear();
		buff << i;

		texture[i] = driver_->getTexture(path + buff.str().c_str() + ".png");

		assert(texture[i]);
	}

	image = guienv->addImage(rect, this);

	assert(image);

	image->setImage(texture[0]);

	image->setUseAlphaChannel(true);
	image->setScaleImage(true);

}

ObjectOrb::~ObjectOrb()
{

}

void ObjectOrb::setAnim(ANIM_ORB anim_)
{
	if (anim == anim_)
		return;

	anim = anim_;

	if (anim == A_IDLE)
		tex_index = 0;

}

void ObjectOrb::anim_update()
{
		if (tex_index >= 3)
			tex_index %= 3;

	image->setImage(texture[tex_index]);
	tex_index++;

}

void ObjectOrb::showDebugInfo()
{
	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), SColor(255, 0, 200, 0));
}