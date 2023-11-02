#pragma once
#include "GameObject.h"

class UIObject : public GameObject
{
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

