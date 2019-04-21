#include "CAnimatedObject.h"

AnimatedObject::AnimatedObject(io::path filename, IVideoDriver* driver_, io::IFileSystem* fs)
	: last_time(0), delta_frame(0), TEXTURE_COUNT(0), tex_index(-1), anim_index(-1)
{
	io::path folder = "media/";
	core::stringw tmp = folder;
	tmp += filename;

	io::IReadFile* file = fs->createAndOpenFile(tmp.c_str());
	assert(file);

	io::IXMLReader* xml = fs->createXMLReader(file);
	assert(xml);

	core::stringw tex_file, ext;
	
	core::stringw currentSection;
	core::stringw buff;

	while (xml->read())
	{
		switch (xml->getNodeType())
		{
			case io::EXN_ELEMENT:

				currentSection = xml->getNodeName();

				if (currentSection == L"file")
				{
					tex_file = xml->getAttributeValueSafe(L"filename");
					assert(!tex_file.empty());

					ext = xml->getAttributeValueSafe(L"extension");
					assert(!ext.empty());
					
					TEXTURE_COUNT = xml->getAttributeValueAsInt(L"image_count");
					assert(TEXTURE_COUNT != 0);
				}
				else if (currentSection == L"anim")
				{
					Animation a;

					buff = xml->getAttributeValueSafe(L"tag");
					assert(!buff.empty());

					a.anim_tag = buff.c_str();

					a.start_frame = xml->getAttributeValueAsInt(L"start_frame");
					a.end_frame = xml->getAttributeValueAsInt(L"end_frame");
					a.delta_frame = xml->getAttributeValueAsInt(L"delta_frame");

					anims.push_back(a);
				}
			
			break;

			case io::EXN_ELEMENT_END:
				currentSection = L"";
				break;
		}
	}

	for (int i = 0; i < TEXTURE_COUNT; i++)
	{
		buff = folder;
		buff += tex_file;
		buff += i;
		buff += ext;

		ITexture* t = driver_->getTexture(buff.c_str());
		assert(t);

		texture.push_back(t);
	}


	xml->drop();

	if(anims.size())
		setAnim(anims[0].anim_tag);

	Animator::registerObject(this);
}

AnimatedObject::~AnimatedObject()
{
	Animator::unregisterObject(this);
}

void AnimatedObject::setAnim(core::stringc anim_tag)
{
	for (int i = 0; i < anims.size(); i++)
	{
		if (anims[i].anim_tag == anim_tag)
		{
			if (anim_index == i)
				return;

			anim_index = i;
			tex_index = anims[i].start_frame;
			delta_frame = anims[i].delta_frame;

			break;
		}
	}

	anim_update();
}

void AnimatedObject::setDeltaFrame(unsigned int df)
{
	delta_frame = df;
}

u32 AnimatedObject::getDeltaFrame() const
{
	return delta_frame;
}

void AnimatedObject::anim_update()
{
	if (tex_index > anims[anim_index].end_frame)
		tex_index = anims[anim_index].start_frame;

	if(image)
		image->setImage(texture[tex_index]);

	tex_index++;
}