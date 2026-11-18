#include "ResourceManager.h"

void ResourceManager::LoadImageFile(string name, const wchar_t* path)
{
	Bitmap* image = new Bitmap(path);

	if (image->GetLastStatus() != Ok)
	{
		delete image;
		return;
	}

	m_images[name] = image;
}

void ResourceManager::MakeFrame(int row, int col, int width, int height)
{
	for (int y = 0; y < row; y++)
	{
		for (int x = 0; x < col; x++)
		{
			Rect frame = { x, y, (x * width), (y * height) };
			m_frames[y][x] = frame;
		}
	}
}
