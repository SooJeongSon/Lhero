#pragma once
#include "UIObject.h"

class Image;
class InGameUI : public UIObject
{
private:
	Image* lpGameInfoImg;
	Image* lpDayAndBossTimerImg;
	Image* lpTimerSpeedImg;
	Image* lpPlayStateImg;
	Image* lpLootInvenImg; 

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

