#pragma once
#include "GameUI.h"

enum class BUTTON_STATE
{
	UP,
	DOWN,
	NONE
};

class Image;
class UIButton : public GameUI
{
private:
	Image* lpImage;
	function<void()> targetFunc;
	BUTTON_STATE state;

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual void SetTargetFunc(function<void()> func) { this->targetFunc = func; }
	virtual void SetState(BUTTON_STATE state) { this->state = state; }
	virtual BUTTON_STATE GetState() { return state; }
	virtual ~UIButton() {}
};

