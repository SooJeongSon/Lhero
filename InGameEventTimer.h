#pragma once
#include "GameUI.h"

class UIProgressBar;
struct EventData;
class InGameEventTimer : public GameUI
{
private:
	Image* lpBackground;

	float dayTime;
	float bossTime;

	UIProgressBar* lpDayTimer;
	UIProgressBar* lpBossTimer;
	EventData* eventData;

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height) override;
	virtual void Render(HDC hdc) override;
	virtual void Update(float deltaTime) override;

	virtual float GetDailyTimer() { return this->dayTime; };
};

