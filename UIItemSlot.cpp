#include "UIItemSlot.h"
#include "Equipment.h"

void UIItemSlot::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row, int maxItems)
{
	GameUI::Init(anchor, pos, width, height);
	this->row = row;
	this->maxItems = maxItems;

}

void UIItemSlot::Release()
{
	for (int i = 0; i < vChildUI.size(); ++i)
	{
		vChildUI[i]->Release();
	}
}

void UIItemSlot::Update(float deltaTime)
{
	GameUI::Update(deltaTime);
}

void UIItemSlot::Render(HDC hdc)
{
	GameUI::Render(hdc);
}
