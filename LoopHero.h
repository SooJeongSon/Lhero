#pragma once

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "msimg32.lib")

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <functional>

using namespace std;

#define WIN_STARTX		50
#define WIN_STARTY		50

#define WINSIZE_WIDTH	1280
#define WINSIZE_HEIGHT	720

#define TILESIZE		50
#define TILE_X			21 
#define TILE_Y			12

#define PI 3.1415926f
#define RADIAN 180/PI
#define DegToRad(x)	((x) * PI / 180.0f)
#define RadToDeg(x)	((x) * 180.0f / PI )

#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern POINT g_ptMouse;
extern bool isDebugMode;

enum class UI_ANCHOR
{
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	LEFT_MIDDLE,
	TOP_MIDDLE,
	RIGHT_MIDDLE,
	BOTTOM_MIDDLE,
	MIDDLE,
	NONE
};

#include "KeyManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "FileManager.h"
#include "GameData.h" 
#include "EventHandler.h"
#include "EventSystem.h"