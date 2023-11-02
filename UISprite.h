#pragma once
#include "GameUI.h"

class Image;
class GameObject;
class UISprite : public GameUI
{
private:
	GameObject* lpObject;

public:
	virtual ~UISprite() {};

	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	void SetObject(GameObject* lpObject);
	GameObject* GetObjectPointer() { return this->lpObject; }	
};

