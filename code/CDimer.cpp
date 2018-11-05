#include "CDimer.h"

Dimer::Dimer(Map* map, IVideoDriver* driver_, IGUIEnvironment* guienv_)
	: AnimatedObject(200), tex_index(0)
{
	irr::io::path path = "media/dim";
	std::ostringstream buff;

	for (int i = 0; i < ANIM_IMAGES_COUNT_DIMER; i++)
	{
		buff.str("");
		buff.clear();
		buff << i;

		texture[i] = driver_->getTexture(path + buff.str().c_str() + ".png");

		assert(texture[i]);
	}

	u32 x = texture[0]->getSize().Width;
	u32 y = texture[0]->getSize().Height;

	image = guienv_->addImage(rect<s32>(0, 0, map->getMapSize(), map->getMapSize()), map);
	image->setScaleImage(true);

	image->setImage(texture[tex_index]);
}

Dimer::~Dimer()
{

}

void Dimer::setVisible(bool v)
{
	image->setVisible(v);
}

bool Dimer::isVisible() const
{
	return image->isVisible();
}

void Dimer::anim_update()
{
	if (++tex_index >= ANIM_IMAGES_COUNT_DIMER)
		tex_index %= ANIM_IMAGES_COUNT_DIMER;

	image->setImage(texture[tex_index]);
}