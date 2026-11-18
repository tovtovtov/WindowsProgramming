#include "framework.h"
#include "CharacterAni.h"


CharacterAni::CharacterAni()
{
	Init(10);
}

void CharacterAni::Init( int p_spritecount )
{
	HBITMAP bitmap = NULL;
	tstring loadpage = _T("");
	for (size_t i = 0; i < p_spritecount; i++)
	{

		loadpage = _T("Images/run0");
		loadpage += ('0' + i);
		loadpage += _T(".bmp");
		//loadpage = _T("Images/run00.bmp");
		//loadpage = string_format("Images/run0%d.bmp", i);


		bitmap = (HBITMAP)LoadImage(NULL,
			//_T("Images/run00.bmp"), 
			loadpage.c_str(),
			IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		m_CharacterBitmap.push_back(bitmap);
	}

}

HBITMAP CharacterAni::GetCurrentHBitMap()
{
	return m_CharacterBitmap[m_AniIndex];
}

void CharacterAni::Render(HWND hWnd, HDC hdc)
{
	HBITMAP currbitmap = GetCurrentHBitMap();

	HDC charhdc = CreateCompatibleDC(hdc);

	SelectObject(charhdc, currbitmap); // bmp ->bit HDC 선택적용

	BitBlt(hdc, 0, 0, 240, 180, charhdc, 0, 0, SRCCOPY);


	DeleteDC(charhdc);
}

void CharacterAni::Update()
{
	m_AniIndex = (m_AniIndex + 1) % m_CharacterBitmap.size();
}
