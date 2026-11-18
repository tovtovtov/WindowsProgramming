#pragma once

#include <objidl.h>
#include <gdiplus.h>
#include <unordered_map>
#include <string>

#pragma comment(lib, "gdiplus.lib")


using namespace std;
using namespace Gdiplus;

class ResourceManager
{
public:
	// 비트맵에 이미지 리소스 로드
	void LoadImageFile(string name, const wchar_t* path);

	// 로드된 비트맵을 프레임별로 재단
	void MakeFrame(int row, int col, int width, int height);

	void DrawFrame(); // 작성 필요

	void Release();

private:
	// 스프라이트 이미지 리소스 관리용 해시 테이블
	unordered_map<string, Bitmap*> m_images;

	// 행별로 프레임을 관리할 2차원 vector
	vector<vector<Rect>> m_frames;

};

