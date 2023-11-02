#include "UIGrid.h"

void UIGrid::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row, float margin,int maxItems)
{
	GameUI::Init(anchor, pos, width, height);
}

void UIGrid::Update(float deltaTime)
{
}

void UIGrid::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	for (int i = 0; i < vChildUI.size(); ++i)
	{
		vChildUI[i]->Render(hdc);
	}
	GameUI::Render(hdc);
}

GameUI* UIGrid::AddChildUI(GameUI* lpChild)
{
	GameUI::AddChildUI(lpChild);
	return lpChild;
}

void UIGrid::RemoveChildUI(GameUI* lpChild)
{
	auto it = find(vChildUI.begin(), vChildUI.end(), lpChild);
	vChildUI.erase(it);
}
