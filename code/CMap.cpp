#include "CMap.h"

Map::Map(u32 fov_radius, u32 field_pixel_size, IrrlichtDevice* device, dimension2d<u32>& screen_size_)
	: IGUIElement(EGUIET_IMAGE, device->getGUIEnvironment(), device->getGUIEnvironment()->getRootGUIElement(), -1,
		rect<s32>(0, 0, (fov_radius)* field_pixel_size, (fov_radius)* field_pixel_size)), DebugObject(), EventHandler(device->getTimer()), _driver(device->getVideoDriver()), _guienv(device->getGUIEnvironment()), screen_size(screen_size_), _field_pixel_size(field_pixel_size),
	delta_moved(0, 0), pos_on_map(0, 0), mv_direction(MD_NONE)
{

	__debug_position	= _guienv->addStaticText(L"", rect<s32>(0, 0, 200, 20));
	__debug_runes		= _guienv->addStaticText(L"", rect<s32>(0, 20, 100, 200));
	__debug_orbs		= _guienv->addStaticText(L"", rect<s32>(100, 20, 200, 200));

	__debug_position->setOverrideColor(SColor(255, 255, 0, 0));
	__debug_runes->setOverrideColor(SColor(255, 200, 200, 0));
	__debug_orbs->setOverrideColor(SColor(255, 200, 200, 0));


	#ifndef __DEBUG_MODE__
		__debug_position->setVisible(false);
		__debug_runes->setVisible(false);
		__debug_orbs->setVisible(false);
	#endif


	assert(fov_radius % 2 == 1);								//	Has to be unpair to provide symetrical vision

	Tiles = _guienv->addTab(rect<s32>(), this);					// "Used to group elements" - check the description of IGUIEnvironment::addTab(...)
	assert(Tiles);

	mapgen = new MapGenerator(device);
	mapgen->createMap(10, true, "map0.map");
	
	pos_on_map = mapgen->getStartPoint();
	
	for (int y = 0; y < fov_radius + 2; y++)
	{
		core::array<Field*> arr;

		for (int x = 0; x < fov_radius + 2; x++)
		{
			arr.push_back(new Field(field_pixel_size, vector2d<s32>(x * field_pixel_size, y * field_pixel_size), NULL, _guienv, Tiles));
		}

		map.push_back(arr);
	}

	refreshMap();

	Tiles->setRelativePosition(rect<s32>(-(s32)field_pixel_size, -(s32)field_pixel_size, getMapSize() + field_pixel_size, getMapSize() + field_pixel_size));
	moveToCenter();

	dimer = new Dimer(this, device);
}

Map::~Map()
{
	map.clear();

	delete dimer;
	delete mapgen;
}

void Map::moveToCenter()
{
	this->setRelativePosition(position2d<s32>((screen_size.Width / 2) - (getMapSize() / 2), (screen_size.Height / 2) - (getMapSize() / 2)));
}

void Map::setCharacter(Character* character_)
{
	character = character_;

	character->setRelativePosition(position2d<s32>((screen_size.Width / 2) - (character->getSize() / 2), (screen_size.Height / 2) - (character->getSize() / 2)));
}

void Map::move(MOVE_DIRECTION dir)
{
	position2d<s32> pos, final(0, 0);

	if (dir == MD_NONE)
		return;
	else if (dir == MD_RIGHT)
		pos.set(1, 0);
	else if (dir == MD_LEFT)
		pos.set(-1, 0);
	else if (dir == MD_UP)
		pos.set(0, -1);
	else if (dir == MD_DOWN)
		pos.set(0, 1);
	else if (dir == MD_DOWN_LEFT)
		pos.set(-1, 1);
	else if (dir == MD_DOWN_RIGHT)
		pos.set(1, 1);
	else if (dir == MD_UP_LEFT)
		pos.set(-1, -1);
	else if (dir == MD_UP_RIGHT)
		pos.set(1, -1);

	Tiles->move(position2d<s32>(pos.X, 0));
	
	if (!characterToWallCollision())
		final.X = pos.X;
	else
		Tiles->move(position2d<s32>(-pos.X, 0));

	Tiles->move(position2d<s32>(0, pos.Y));

	if (!characterToWallCollision())
		final.Y = pos.Y;
	else
		Tiles->move(position2d<s32>(0, -pos.Y));

	if (final == position2d<s32>(0, 0))
		return;

	handleGOCollision();


	delta_moved += final;


	if (abs(delta_moved.X) >= _field_pixel_size)
	{
		Tiles->move(position2d<s32>(-delta_moved.X, 0));

		position2d<s32> norm((delta_moved.X < 0)? 1 : -1, 0);

		if (mapgen->hasField(pos_on_map.X + norm.X, pos_on_map.Y + norm.Y))
			pos_on_map += norm;

		delta_moved.X = 0;

		refreshMap();
	}
	if (abs(delta_moved.Y) >= _field_pixel_size)
	{
		Tiles->move(position2d<s32>(0, -delta_moved.Y));

		position2d<s32> norm(0, (delta_moved.Y < 0) ? 1 : -1);

		if (mapgen->hasField(pos_on_map.X + norm.X, pos_on_map.Y + norm.Y))
			pos_on_map += norm;

		delta_moved.Y = 0;

		refreshMap();
	}
}

void Map::refreshMap()
{
	int dx = map[0].size() / 2;
	int dy = map.size() / 2;

	for (int y = 0; y < map.size(); y++)
		for (int x = 0; x < map[0].size(); x++)
		{
			FieldCache cache;

			if (!mapgen->hasField(x + pos_on_map.X - dx, y + pos_on_map.Y - dy))
				cache.blank = 1;
			else
				cache = mapgen->getFieldCache(x + pos_on_map.X - dx, y + pos_on_map.Y - dy);
			
			map[y][x]->setCache(cache, _driver, _guienv);
		}
}

bool Map::hasField(int x, int y)
{
	if (!map.size())
		return false;

	return (x >= 0 && x < map[0].size() && y >= 0 && y < map.size());
}

bool Map::characterToWallCollision()
{
	if (!character || !map.size())
		return false;

	int x = map[0].size() / 2;
	int y = map.size() / 2;

	for (int _y = y - 1; _y <= y + 1; _y++)
		for (int _x = x - 1; _x <= x + 1; _x++)
			if (hasField(_x, _y) && map[_y][_x]->isBlank() && character->getAbsolutePosition().isRectCollided(map[_y][_x]->getRect()))
				return true;

	return false;
}

void Map::handleGOCollision()
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			GameObject* go = map[y][x]->getObject();

			if (go && go->getAbsolutePosition().isRectCollided(character->getAbsolutePosition()))
			{
				if (go->getGOType() == "GOT_RUNE")
				{
					if (character->hasObject("Green Orb"))
					{
						mapgen->activateRune(mapFieldPosToPosOnMap(x, y));
						character->removeObject("Green Orb");
					}
				}
				else if (go->getGOType() == "GOT_ORB")
				{
					character->giveObject(go->getName());
					mapgen->deleteOrb(mapFieldPosToPosOnMap(x, y));
					break;
				}

				refreshMap();
			}
		}
	}
}

void Map::react(CEventReceiver* receiver)
{
	if (receiver->IsKeyDown(KEY_KEY_W))
	{
		if (receiver->IsKeyDown(KEY_KEY_A))
		{
			mv_direction = MD_DOWN_RIGHT;
		}
		else if (receiver->IsKeyDown(KEY_KEY_D))
		{
			mv_direction = MD_DOWN_LEFT;
		}
		else
			mv_direction = MD_DOWN;
	}
	else if (receiver->IsKeyDown(KEY_KEY_S))
	{
		if (receiver->IsKeyDown(KEY_KEY_A))
		{
			mv_direction = MD_UP_RIGHT;
		}
		else if (receiver->IsKeyDown(KEY_KEY_D))
		{
			mv_direction = MD_UP_LEFT;
		}
		else
			mv_direction = MD_UP;
	}
	else if (receiver->IsKeyDown(KEY_KEY_A))
	{
		mv_direction = MD_RIGHT;
	}
	else if (receiver->IsKeyDown(KEY_KEY_D))
	{
		mv_direction = MD_LEFT;
	}
	else
		mv_direction = MD_NONE;


	if (timer->getTime() - time_last >= character->getMovementSpeed())
	{
		this->move(mv_direction);
		time_last = timer->getTime();
	}
}

void Map::showDebugInfo()
{
	if (!map.size())
		return;

	for(int x = 0; x < map[0].size(); x++)
		for(int y = 0; y < map.size(); y++)
			_driver->draw2DRectangleOutline(map[y][x]->getRect(), SColor(255, 200, 0, 0));

	std::wostringstream buff;
	buff << "Player: " <<  pos_on_map.X << ", " << pos_on_map.Y;

	__debug_position->setText(buff.str().c_str());

	buff.str(L"");
	buff << "Runes: " << std::endl;

	for (int i = 0; i < mapgen->getRunesPosArr().size(); i++)
		buff << mapgen->getRunesPosArr()[i].X << ", " << mapgen->getRunesPosArr()[i].Y << std::endl;

	__debug_runes->setText(buff.str().c_str());

	buff.str(L"");
	buff << "Orbs: " << std::endl;

	for (int i = 0; i < mapgen->getOrbsPosArr().size(); i++)
		buff << mapgen->getOrbsPosArr()[i].X << ", " << mapgen->getOrbsPosArr()[i].Y << std::endl;

	__debug_orbs->setText(buff.str().c_str());
}

position2d<s32> Map::mapFieldPosToPosOnMap(int x, int y)
{
	position2d<s32> pos(0, 0);

	if (!map.size())
		return pos;

	int lx = map[0].size() / 2;
	int ly = map.size() / 2;

	pos.set(x + pos_on_map.X - lx, y + pos_on_map.Y - ly);

	return pos;
}

Dimer* Map::getDimer() const
{
	return dimer;
}

u32 Map::getMapSize() const
{
	return this->getAbsolutePosition().getWidth();
}