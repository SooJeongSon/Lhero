#include "UIProgressBar.h"
#include "Image.h"

void UIProgressBar::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	lpBar = ImageManager::GetInstance()->FindImage("STATUSBAR");
	GameUI::Init(anchor, pos, width, height);
}

void UIProgressBar::Init()
{
}

void UIProgressBar::Release()
{
}

void UIProgressBar::Update(float deltaTime)
{
	if (lpTargetFunc)
	{
		lastVar = lpTargetFunc();
	}
	else
	{
		if (lpTargetVar)
		{
			lastVar = *lpTargetVar;
		}
	}
	GameUI::Update(deltaTime);
}

void UIProgressBar::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	GameUI::Render(hdc);
	lpBar->SetWidth(width * (lastVar / maxVar));
	lpBar->Render(hdc, rc.left, rc.top);
}

void UIProgressBar::SetTargetFunc(function<float()> lpTargetFunc, float maxVar)
{
	this->lpTargetFunc = lpTargetFunc;
	this->maxVar = maxVar;
}

void UIProgressBar::SetTargetFunc(float* lpTargetVar, float maxVar)
{
	this->lpTargetVar = lpTargetVar;
	this->maxVar = maxVar;
}

void UIProgressBar::SetBarImg(string key)
{
	lpBar = ImageManager::GetInstance()->FindImage(key);
}
