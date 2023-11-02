#include "UIButton.h"
#include "Image.h"

void UIButton::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);
	state = BUTTON_STATE::UP;
	targetFunc = nullptr;
	this->pos = pos;
	lpImage = ImageManager::GetInstance()->FindImage("EXITBUTTON");
	SetRect(&rc, pos.x - width / 2, pos.y - height / 2, pos.x + width / 2, pos.y + height / 2);
	
}

void UIButton::Release()
{
}

void UIButton::Update(float deltaTime)
{

	GameUI::Update(deltaTime);
}

void UIButton::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	if (lpImage)
	{
		lpImage->FrameRender(hdc, rc.left, rc.top, 0, (int)state, false, 1, true, RGB(0, 170, 255));
	}
	GameUI::Render(hdc);
}
