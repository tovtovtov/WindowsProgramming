#pragma once
#include <Windows.h>
#include <vector>


class CharacterAni
{
public:
	CharacterAni();

public:
	void Init(int p_spritecount);

	HBITMAP GetCurrentHBitMap();

	void Render(HWND hWnd, HDC hdc);

	void Update();

public:
	std::vector< HBITMAP > m_CharacterBitmap;

	int m_AniIndex = 0;
	

};

