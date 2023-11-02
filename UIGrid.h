#pragma once
#include "GameUI.h"

class UIGrid : public GameUI
{
private:
	int row;
	int maxItems;
	float margin;
	int selectedChildIndex;

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row = 1, float margin = 0, int maxItems = 12);
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual GameUI* AddChildUI(GameUI* lpChild) final;
	virtual void RemoveChildUI(GameUI* lpChild) override;

	virtual ~UIGrid() {}
};
