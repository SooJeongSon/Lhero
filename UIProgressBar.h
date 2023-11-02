#pragma once
#include "GameUI.h"

enum class UI_BAR_TYPE
{
	HORIZONTAL,
	VERTICAL
};

class Image;
class UIProgressBar : public GameUI
{
private:
	Image* lpBackground;
	Image* lpBar;

	UI_BAR_TYPE barType;

	function<float()> lpTargetFunc;
	float* lpTargetVar;
	float maxVar;
	float lastVar;

public:
	virtual ~UIProgressBar() {};
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual void SetTargetFunc(function<float()> lpTargetFunc, float maxVar);
	virtual void SetTargetFunc(float* lpTargetVar, float maxVar);
	virtual void SetBarImg(string key);
};

