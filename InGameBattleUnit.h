#pragma once
#include "GameUI.h"

class UISprite;
class InGameBattleUnit : public GameUI
{
public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
};

