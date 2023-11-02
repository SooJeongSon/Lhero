#pragma once
#include "GameObject.h"

enum class UNIT_STATE
{
	INTRO,
	IDLE,
	ATTACK,
	DEATH,
	HURT,
	REVIVE,
	NONE
};

enum class UNIT_POSITION
{
	LEFT,
	RIGHT
};

class Unit;
class Animation;
class BattleUnit : public GameObject
{
private:
	UNIT_STATE state;
	UNIT_POSITION position;
	Unit* lpUnit;
	float action;
	bool isAtkReady;
	int unitIndex;

	map<UNIT_STATE, Animation*> mLpAnimations;

public:
	virtual ~BattleUnit() {};
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual void SetUnit(Unit* lpUnit, UNIT_POSITION position = UNIT_POSITION::LEFT, int unitIndex = 0);
	virtual Unit* GetUnit() { return this->lpUnit; }

	void SetState(UNIT_STATE state) { this->state = state; }
	void GetState() { this->state; }

	void Intro();
	void Idle();
	void Attack();
	void Death();
	void Hurt();
	void Revive();

};

