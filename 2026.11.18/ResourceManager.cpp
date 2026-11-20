#include "ResourceManager.h"

void ResourceManager::LoadImageFile(string name, const wchar_t* path, int frameSize)
{
	Bitmap* image = new Bitmap(path);

	if (image->GetLastStatus() != Ok)
	{
		delete image;
		return;
	}

	Resource* r = new Resource;
	r->bitmap = image;
	r->name = name;
	r->frameSize = frameSize;

	resource.push_back(r);
}

void ResourceManager::DrawImage(int x, int y, int frameCount)
{


}





