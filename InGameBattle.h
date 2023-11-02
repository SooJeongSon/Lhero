#pragma once
#include "GameUI.h"

class Image;
class BattleUnit;
class Mob;
class Unit;
class InGameBattle : public GameUI
{
private:
	Image* lpBackground;
	BattleUnit* lpBattleHero;
	vector<BattleUnit*> vLpBattleMob;

public:
	virtual ~InGameBattle() {};

	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual void SetBattleHero(Unit* lpHero);
	virtual void SetBattleMob(vector<Mob*> vMobs);	
};

