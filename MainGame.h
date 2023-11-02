#pragma once
#include "LoopHero.h"

class Timer;
class MainGame
{
private:
	HDC hdc;
	Timer* lpTimer;
	HANDLE hTimer;

	bool isInited;
	char szText[128] = "";
	Image* backBuffer;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

