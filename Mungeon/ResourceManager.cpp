#include "ResourceManager.h"

void ResourceManager::LoadImage(string name, const wchar_t* path)
{
	Bitmap* image = new Bitmap(path);

	if (image->GetLastStatus() != Ok)
	{
		delete image;
		return;
	}

	m_images[name] = image;
}

void ResourceManager::DrawImage(
	HDC hdc,
	string name,
	int x, int y, // 출력 좌표
	int scaleX, int scaleY, // 이미지 width, height 확대 배율
	int sourceX, int sourceY, // 이미지에서 출력할 부분의 좌표
	int sourceWidth, int sourceHeight // 원본 이미지 크기
)
{
	auto it = m_images.find(name);

	if (it == m_images.end())
		return;

	Bitmap* image = it->second;

	Graphics graphics(hdc);

	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor); // 이미지 확대 시 픽셀 보정

	graphics.DrawImage(
		image,
		Rect(x*32, y*32, (scaleX*32), (scaleY*32)),
		(sourceX*32), (sourceY*32), 
		sourceWidth, sourceHeight,
		UnitPixel
	);
}

void ResourceManager::Release()
{
	for (auto image : m_images)
	{
		delete image.second;
	}

	m_images.clear();
}
