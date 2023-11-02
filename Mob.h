#pragma once
#include "Unit.h"

class Breed;
class Image;
class Animation;
class Mob : public Unit
{
	friend class Breed;
private:
	Mob(Breed& breed, float maxHp);
	int frameCnt;
	int motionCnt;
	Animation* lpIconAni;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual ~Mob() {};	
};

