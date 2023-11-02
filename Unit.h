#pragma once
#include "GameObject.h"

class Image;
class Unit : public GameObject
{
protected:
	float maxHp;
	float hp;
	float attackDmg;
	float defenseValue;
	float vampValue;
	float conterValue;
	float splashDmg;
	float evasion;
	float attackSpeed;
	Image* lpImage;
	float moveSpeed;
	string name;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual float GetMoveSpeed() { return this->moveSpeed; }
	virtual string GetName() { return this->name; }
	virtual float GetHp() { return this->hp; }
	virtual void SetHp(float hp) { this->hp = hp; }
	virtual float GetMaxHp() { return this->maxHp; }

	virtual float GetDmg() { return this->attackDmg; }

	virtual ~Unit() {};
};

