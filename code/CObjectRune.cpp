#include "CObjectRune.h"

ObjectRune::ObjectRune(rect<s32> rect, IVideoDriver* driver_, IGUIEnvironment* guienv, IGUIElement* parent, s32 id)
	: GameObject(EGUIET_IMAGE, guienv, parent, id, rect, 100, GOT_RUNE), _driver(driver_), anim(A_IDLE),
	activated(false), tex_index(0)
{
	io::path path = "media/rune_green_";
	std::ostringstream buff;

	for (int i = 0; i < ANIM_IMAGES_COUNT_RUNE; i++)
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

ObjectRune::~ObjectRune()
{
	
}

void ObjectRune::activate(bool b)
{
	if (b)
	{
		setAnim(A_ACTIVATED);
		activated = true;
	}
	else
	{
		setAnim(A_IDLE);
		activated = false;
	}
}

void ObjectRune::setAnim(ANIM_RUNE anim_)
{
	if (anim == anim_)
		return;

	anim = anim_;

	if (anim == A_IDLE)
		tex_index = 0;
	else if (anim == A_ACTIVATED)
		tex_index = 1;

}

void ObjectRune::anim_update()
{
	if (anim == A_IDLE)
	{
		tex_index = 0;
	}
	else if (anim == A_ACTIVATED)
	{
		if (tex_index >= 4)
		{
			tex_index %= 4;
			tex_index += 1;
		}
	}

	image->setImage(texture[tex_index]);
	tex_index++;

}

void ObjectRune::showDebugInfo()
{
	SColor color;
	
	if (activated)
		color.set(255, 200, 0, 0);
	else
		color.set(255, 0, 200, 0);

	_driver->draw2DRectangleOutline(this->getAbsolutePosition(), color);
}

bool ObjectRune::isActive() const
{
	return activated;
}