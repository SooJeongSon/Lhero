#pragma once
#include "Unit.h"

enum class HERO_STATE
{
	LOOP,
	BATTLE
};

class Animation;
class Hero : public Unit
{
private:
	Animation* lpIconAni;
	HERO_STATE state;

public:
	virtual ~Hero() {};
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual void SetState(HERO_STATE state) { this->state = state; }
	virtual HERO_STATE GetState() { return this->state; }

};

