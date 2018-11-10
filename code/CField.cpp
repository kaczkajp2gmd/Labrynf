#include "CField.h"

Field::Field(u32 pixel_size, vector2d<s32> pos, ITexture* texture_, IGUIEnvironment* guienv_, IGUIElement* parent)
    : IGUIElement(EGUIET_IMAGE, guienv_, parent, -1, rect<s32>(pos.X, pos.Y, pos.X + pixel_size, pos.Y + pixel_size)), PIXEL_SIZE(pixel_size), object(NULL)
{
	texture = texture_;
	image = guienv_->addImage(rect<s32>(0, 0, this->getAbsolutePosition().getWidth(), this->getAbsolutePosition().getWidth()), this);
	
	image->setImage(texture);
	image->setScaleImage(true);
}

Field::Field(u32 pixel_size, FieldCache cache, vector2d<s32> pos, IVideoDriver* driver_, IGUIEnvironment* guienv_, IGUIElement* parent)
	: IGUIElement(EGUIET_IMAGE, guienv_, parent, -1, rect<s32>(pos.X, pos.Y, pos.X + pixel_size, pos.Y + pixel_size)), PIXEL_SIZE(pixel_size), object(NULL)
{
	texture = cache.texture;
	image = guienv_->addImage(rect<s32>(pos.X, pos.Y, pos.X + PIXEL_SIZE, pos.Y + PIXEL_SIZE), this);

	image->setImage(texture);
	image->setScaleImage(true);
}

Field::~Field()
{
    
}

void Field::setCache(FieldCache cache, IVideoDriver* driver_, IGUIEnvironment* guienv_)
{
	texture = cache.texture;
	image->setImage(texture);

	image->setVisible(!cache.blank);


	if(object && object->getParent() == this)
	{
		object->setVisible(false);
		object->setParent(NULL);
		object = NULL;
	}
	
	if (cache.object)
	{
		object = cache.object;

		object->setVisible(true);
		object->setParent(this);
		this->bringToFront(object);
	}
}

bool Field::isBlank() const
{
	return !image->isVisible();
}

GameObject* Field::getObject() const
{
	return object;
}

position2d<s32> Field::getPos() const
{
	return image->getAbsolutePosition().UpperLeftCorner;
}

u32 Field::getSize() const
{
	return PIXEL_SIZE;
}

rect<s32> Field::getRect() const
{
	return image->getAbsolutePosition();
}