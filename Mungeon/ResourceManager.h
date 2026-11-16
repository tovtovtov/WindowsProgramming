#pragma once

#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

#include <unordered_map>

using namespace std;
using namespace Gdiplus;

class ResourceManager
{
private:
    // 이미지 저장
    unordered_map<string, Bitmap*> m_images;

public:
    // 이미지 로드
    void LoadImage(string name, const wchar_t* path);

    // 이미지 출력
    void DrawImage(
        HDC hdc,
        string name,
        int x, int y, // 출력 좌표
        int scaleX, int scaleY, // 이미지 width, height 확대 배율
        int sourceX, int sourceY, // 이미지에서 출력할 부분의 좌표
        int sourceWidth, int sourceHeight // 원본 이미지 크기
    );

    // 이미지 해제
    void Release();
};
