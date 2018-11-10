#include "CDimer.h"

Dimer::Dimer(Map* map, IrrlichtDevice* device)
	: AnimatedObject("dimer.anim", device->getVideoDriver(), device->getFileSystem())
{
	setAnim("DIM");

	image = device->getGUIEnvironment()->addImage(rect<s32>(0, 0, map->getMapSize(), map->getMapSize()), map);
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