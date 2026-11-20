#pragma once

#include <objidl.h>
#include <gdiplus.h>
#include <unordered_map>
#include <string>

#pragma comment(lib, "gdiplus.lib")


using namespace std;
using namespace Gdiplus;

struct Resource
{
	// 저장할 bitmap
	Bitmap* bitmap;
	// 이미지명
	string name;
	// 프레임 한칸의 크기 ex) 32 * 32
	int frameSize;
};

class ResourceManager
{
public:
	// 리소스 로드
	void LoadImageFile(string name, const wchar_t* path, int frameSize);

	// 로드된 이미지의 특정 부분 그리기
	void DrawImage(int x, int y, int frameCount);
	
	void Release();

private:

	// bitmap 이미지 저장용 vector
	vector<Resource*> resource;

};

