#include "App.h"

#define scaleX 1
#define scaleY 1

void App::Init()
{
	// GDI+ 초기화
	GdiplusStartupInput startupInput;
	GdiplusStartup(&gdiplusToken, &startupInput, nullptr);
	
	// 리소스 로드
	resource.LoadImage("player", L"resource/player/players.png");
	resource.LoadImage("monster", L"resource/monster/monsters.png");
	resource.LoadImage("maptile", L"resource/map/tiles.png");

	// 미로 맵 생성
	map.GenerateMaze(31, 31, EASY, 1234);
}

void App::Update()
{
	// input 입력 감지 후 플레이어, 몹 데이터 업데이트
	// 코드 작성 예정
}

void App::Render(HDC hdc)
{
	map.Render(hdc, &resource);
	resource.DrawImage(hdc, "player", 1, 1, scaleX, scaleY, 3, 3, 32, 32);
	//resource.DrawImage(hdc, "monster", 200, 100, scaleX, scaleY, 7, 7, 32, 32);
}

void App::Destroy()
{
	// 이미지 리소스 해제
	resource.Release();

	// GDI+ 종료
	GdiplusShutdown(gdiplusToken);
}
