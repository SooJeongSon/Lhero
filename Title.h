#pragma once
#include "GameScene.h"

class Image;
class Title : public GameScene
{
private:
	Image* lpBackground;
	Image* lpBackBuffer;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual ~Title() {}
};

