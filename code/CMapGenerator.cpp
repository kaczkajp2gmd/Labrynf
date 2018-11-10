#include "CMapGenerator.h"

MapGenerator::MapGenerator(IrrlichtDevice* device)
	: _device(device)
{
	srand(time(0));
}

MapGenerator::~MapGenerator()
{

}

void MapGenerator::createMap(u32 size, bool serialize, io::path path)
{
	assert(size >= 10);		// To aviod empty map. Check the generation algorithm.

	current_map.clear();

	core::array<FieldCache> arr;
	
	ITexture* texture = _device->getVideoDriver()->getTexture("media/plane.png");
	assert(texture);

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			FieldCache field;
			
			field.texture = texture;
			
			arr.push_back(field);
		}

		current_map.push_back(arr);
		arr.clear();
	}


	generate(current_map);
	setRunesAndOrbs(1);

	if (serialize)
		serializeCurrentMap(path);
}

void MapGenerator::serializeCurrentMap(io::path path)
{
	if (path == "")
	{
		std::ostringstream buff;
		buff << "map0.map";
		std::ifstream test_file(buff.str().c_str());
		int i = 0;

		while(test_file.is_open())
		{
			i++;
			buff.clear();
			buff.str("");
			buff << "map" << i << ".map";
			test_file.close();
			test_file.open(buff.str().c_str());
		}

		path = buff.str().c_str();
	}

	std::ofstream file(path.c_str(), std::ios::out);

	if (!file.good())
	{
		std::cout << "(!) ERROR : Failed to save file: " << path.c_str() << std::endl;
		return;
	}

	for (int y = 0; y < current_map.size(); y++)
	{
		for (int x = 0; x < current_map[0].size(); x++)
			file << current_map[y][x].blank << " ";

		file << std::endl;
	}

	file << "Runes: " << std::endl;

	for (int i = 0; i < runes.size(); i++)
		file << runes[i].X << ", " << runes[i].Y << std::endl;

	file << "Orbs: " << std::endl;

	for (int i = 0; i < runes.size(); i++)
		file << orbs[i].X << ", " << orbs[i].Y << std::endl;

	file.close();
}

void MapGenerator::deleteOrb(position2d<s32> orbpos)
{
	int index = orbs.linear_search(orbpos);

	if (index == -1)
		return;

	delete current_map[orbpos.Y][orbpos.X].object;
	current_map[orbpos.Y][orbpos.X].object = NULL;

	orbs.erase(index);
}

void MapGenerator::activateRune(position2d<s32> runepos)
{
	int index = runes.linear_search(runepos);

	if (index == -1)
		return;

	((ObjectRune*) current_map[runepos.Y][runepos.X].object)->activate(true);
}

bool MapGenerator::hasField(int x, int y)
{
	return checkBorder(x, y, current_map);
}

FieldCache MapGenerator::getFieldCache(int x, int y)
{
	assert(checkBorder(x, y, current_map));

	return current_map[y][x];
}

position2d<s32> MapGenerator::getStartPoint()
{
	for (int y = 0; y < current_map.size(); y++)
		for (int x = 0; x < current_map[0].size(); x++)
			if (!current_map[y][x].blank)
				return position2d<s32>(x, y);

	return position2d<s32>(0, 0);
}

core::array<position2d<s32>> MapGenerator::getRunesPosArr()
{
	return runes;
}

core::array<position2d<s32>> MapGenerator::getOrbsPosArr()
{
	return orbs;
}

void MapGenerator::generate(T_MAP_CACHE& map)
{
	for (int y = 0; y < current_map.size(); y++)
	{
		for (int x = 0; x < current_map[0].size(); x++)
		{
			if (!hasNeighbourWall(x, y, current_map))
			{
				int wallsize = rand() % (int)(MAX_WALLSIZE * current_map[0].size());

				for (int i = 0; i < wallsize; i++)
					if (checkBorder(x + i, y, current_map))
						current_map[y][x + i].blank = true;
			}
		}
	}

	
	for (int x = 0; x < current_map[0].size(); x++)
	{
		for (int y = 0; y < current_map.size(); y++)
		{
			if (!hasNeighbourWall(x, y, current_map))
			{
				int wallsize = rand() % (int)(MAX_WALLSIZE * current_map.size()) + 1;

				for (int i = 0; i < wallsize; i++)
					if (checkBorder(x, y + i, current_map))
						current_map[y + i][x].blank = true;
			}
		}
	}

	// SQUARE REMOVAL PROCEDURE:

	for (int y = 1; y < current_map.size(); y++)
		for (int x = 0; x < current_map[0].size() - 1; x++)
			if (!current_map[y][x].blank &&
				!current_map[y][x + 1].blank &&
				!current_map[y - 1][x].blank &&
				!current_map[y - 1][x + 1].blank)
			{
				//	Pick random field of a square:
				int dx = rand() % 2;
				int dy = rand() % 2;

				//	And set a wall there:
				current_map[y - dy][x + dx].blank = true;
			}


	//	Here should be the procedure of deleting isolated fields:
}

void MapGenerator::setRunesAndOrbs(u32 howMany)
{
	runes.clear();
	orbs.clear();

	u32 counter = 0;

	for (int y = 0; y < current_map.size(); y++)
	{
		for (int x = 0; x < current_map[0].size(); x++)
		{
			if (!current_map[y][x].blank)
				counter++;
		}
	}

	assert(counter >= 4 * howMany);

	core::array<u32> indices;

	for (int i = 0; i < 2 * howMany; i++)
	{
		bool exists = false;
		int n = rand() % counter + 1;
		
		for(int x = 0; x < indices.size(); x++)
			if (indices[x] == n)
			{
				exists = true;
				break;
			}
		
		if (exists)
		{
			i--;
			continue;
		}

		indices.push_back(n);
	}

	counter = 0;

	for (int y = 0; y < current_map.size(); y++)
		for (int x = 0; x < current_map[0].size(); x++)
		{
			if (current_map[y][x].blank)
				continue;

			counter++;
			
			for (int c = 0; c < indices.size(); c++)
				if(counter == indices[c])
				{
					if (c >= howMany)
					{
						GameObjectFactory f(_device);

						current_map[y][x].object = f.instantiateGameObject("media/rune_green.gobj");
						runes.push_back(position2d<s32>(x, y));
					}
					else
					{
						GameObjectFactory f(_device);
						current_map[y][x].object = f.instantiateGameObject("media/orb_green.gobj");
						orbs.push_back(position2d<s32>(x, y));
					}
				}
		}
}

bool MapGenerator::checkBorder(int x, int y, T_MAP_CACHE& map) const
{
	return (x >= 0 && x < map[0].size() && y >= 0 && y < map.size());
}

bool MapGenerator::hasNeighbourWall(int x, int y, T_MAP_CACHE& map)
{
	for (int _y = y - 1; _y <= y + 1; _y++)
		for (int _x = x - 1; _x <= x + 1; _x++)
			if (checkBorder(_x, _y, current_map) && current_map[_y][_x].blank)
				return true;

	return false;
}