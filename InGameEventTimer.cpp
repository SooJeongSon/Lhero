#include "InGameEventTimer.h"
#include "Image.h"
#include "UIProgressBar.h"

void InGameEventTimer::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);

	lpBackground = ImageManager::GetInstance()->FindImage("INGAMETIMER");

	lpDayTimer = GameUI::CreateUI<UIProgressBar>(this);
	lpDayTimer->Init(UI_ANCHOR::LEFT_TOP, { 17*2, 5*2 }, 200, 6);
	this->AddChildUI(lpDayTimer);
	//누구의 멤버함수인지 미리 할당시켜서 보내줌
	lpDayTimer->SetTargetFunc(bind(&InGameEventTimer::GetDailyTimer, this), 3.0f);

	lpBossTimer = GameUI::CreateUI<UIProgressBar>(this);
	lpBossTimer->Init(UI_ANCHOR::LEFT_TOP, { 17*2, 20*2 }, 200, 6);
	this->AddChildUI(lpBossTimer);
	lpBossTimer->SetTargetFunc(&bossTime, 20.0f);

	this->dayTime = 0.0f;
	this->bossTime = 0.0f;
}

void InGameEventTimer::Render(HDC hdc)
{
	if (lpBackground)
	{
		lpBackground->Render(hdc, rc.left, rc.top);
	}
	if (lpDayTimer)
	{
		lpDayTimer->Render(hdc);
	}
	if (lpBossTimer)
	{
		lpBossTimer->Render(hdc);
	}	
}

void InGameEventTimer::Update(float deltaTime)
{

	dayTime = EventHandler::GetInstance()->GetDayElapsedTime();
	bossTime += 1.0f * deltaTime;
	if (bossTime > 20.0f)
	{
		bossTime = 20.0f;
	}

	if (lpDayTimer)
	{
		lpDayTimer->Update(deltaTime);
	}
	if (lpBossTimer)
	{
		lpBossTimer->Update(deltaTime);
	}
}

