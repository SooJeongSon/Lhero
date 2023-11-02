#pragma once
#include "GameUI.h"


class UIItemSlot : public GameUI
{
private:
	int maxItems;
	int row;

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row=3, int maxItems=12);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
};

