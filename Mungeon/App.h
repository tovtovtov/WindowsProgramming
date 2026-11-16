#pragma once

#include "framework.h"

class App
{
public: 
	void Init();
	void Update();
	void Render(HDC hdc);
	void Destroy();

	ResourceManager resource;
	Map map;

private:
	ULONG_PTR gdiplusToken;
};

