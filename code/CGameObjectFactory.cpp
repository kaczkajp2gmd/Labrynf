#include "CGameObjectFactory.h"

GameObjectFactory::GameObjectFactory(IrrlichtDevice* device_)
	: device(device_)
{

}

GameObjectFactory::~GameObjectFactory()
{

}

GameObject* GameObjectFactory::instantiateGameObject(io::path filename, IGUIElement* parent, s32 ID)
{
	GameObject* obj = NULL;

	io::IFileSystem* fs = device->getFileSystem();
	assert(fs);
	
	io::IReadFile* file = fs->createAndOpenFile(filename);
	assert(file);
	
	io::IXMLReader* xml = fs->createXMLReader(file);
	assert(xml);

	core::stringc animfile;
	core::stringc type;
	core::stringc name;
	s32 x = -1, y = -1;
	s32 mv_speed = -1;

	core::stringw currentSection;

	while (xml->read())
	{
		switch (xml->getNodeType())
		{
		case io::EXN_ELEMENT:

			currentSection = xml->getNodeName();

			if (currentSection == L"animfile")
			{
				animfile = xml->getAttributeValueSafe(L"filename");
				assert(!animfile.empty());
			}
			else if (currentSection == L"gameobject")
			{
				type = xml->getAttributeValueSafe(L"type");
				assert(!type.empty());


				name = xml->getAttributeValueSafe(L"name");
				assert(!name.empty());

				x = xml->getAttributeValueAsInt(L"width");
				y = xml->getAttributeValueAsInt(L"height");
				assert(x != -1 && x != -1);
			}
			else if (currentSection == L"entity")
			{
				mv_speed = xml->getAttributeValueAsInt(L"movement_speed");
				assert(mv_speed != -1);
			}

			break;

		case io::EXN_ELEMENT_END:
			currentSection = L"";
			break;
		}
	}

	if (type == "GOT_RUNE")
		obj = new ObjectRune(rect<s32>(0, 0, x, y), device, parent, ID, animfile.c_str());
	else if (type == "GOT_ORB")
		obj = new ObjectOrb(rect<s32>(0, 0, x, y), device, parent, ID, animfile.c_str());
	else if (type == "GOT_CHARACTER")
		obj = new Character(x, mv_speed, device);

	obj->setName(name);

	return obj;
}