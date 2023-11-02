#include "UISprite.h"
#include "Image.h"
#include "Card.h"
#include "GameObject.h"

void UISprite::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);
}

void UISprite::Release()
{
	if (lpObject)
	{
		SAFE_RELEASE(lpObject);
	}
}

void UISprite::Update(float deltaTime)
{
	if (lpObject)
	{
		lpObject->SetPos({ (rc.right + rc.left) / 2.0f, (rc.top + rc.bottom) / 2.0f });
		lpObject->Update(deltaTime);		
	}
	GameUI::Update(deltaTime);
}

void UISprite::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

	if (lpObject)
	{
		lpObject->Render(hdc);
	}

	GameUI::Render(hdc);
}

void UISprite::SetObject(GameObject* lpObject)
{
	this->lpObject = lpObject;
}
