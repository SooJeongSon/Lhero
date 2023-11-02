#pragma once
#include "UIObject.h"

enum class ButtonState
{
	NONE, DOWN, UP
};

typedef void (*func_t)(int); //func_t 가 타입이 되는 것

class Image;
class Button : public UIObject
{
private:
	ButtonState buttonState;
	Image* lpImage;
	RECT rcButton;
	POINT pos;

	func_t func;
	int funcArg;

public:
	HRESULT Init(const char* fileName, int posX, int posY);
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetFunc(func_t func, int funcArg) { this->func = func;  this->funcArg = funcArg; }
	void SetFuncArg(int funcArg) { this->funcArg = funcArg; }

	virtual ~Button() {};
};

