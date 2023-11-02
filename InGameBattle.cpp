#include "InGameBattle.h"
#include "Image.h"
#include "BattleUnit.h"
#include "Unit.h"
#include "Mob.h"

void InGameBattle::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);
	lpBackground = ImageManager::GetInstance()->FindImage("BATTLEBACKGROUND");
	lpBattleHero = new BattleUnit();
}

void InGameBattle::Release()
{
	if (lpBattleHero)
	{
		SAFE_RELEASE(lpBattleHero);
	}

	if (!vLpBattleMob.empty())
	{
		for (int i = 0; i < vLpBattleMob.size(); ++i)
		{
			SAFE_RELEASE(vLpBattleMob[i]);
		}
	}
}

void InGameBattle::Update(float deltaTime)
{
	lpBattleHero->Update(deltaTime);
	if (!vLpBattleMob.empty())
	{
		for (int i = 0; i < vLpBattleMob.size(); ++i)
		{
			vLpBattleMob[i]->Update(deltaTime);
			lpBattleHero->GetUnit()->SetHp(lpBattleHero->GetUnit()->GetHp() - vLpBattleMob[i]->GetUnit()->GetDmg());
			vLpBattleMob[i]->GetUnit()->SetHp(vLpBattleMob[i]->GetUnit()->GetHp() - GameData::GetInstance()->GetAttackDmg());
			if (vLpBattleMob[i]->GetUnit()->GetHp() <= 0)
			{
				vLpBattleMob[i]->Death();
				vLpBattleMob.erase(vLpBattleMob.begin() + i);
				EventHandler::GetInstance()->SetIsMobDead(true);
				EventHandler::GetInstance()->SetIsMobDeadE(true);
			}
			if (vLpBattleMob.size() == 0)
			{
				EventHandler::GetInstance()->SetIsBattleWin(true);
				lpBattleHero->Idle();
				break;
			}
		}		
	}	
	GameUI::Update(deltaTime);
}

void InGameBattle::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}	
	if (lpBackground)
	{
		lpBackground->Render(hdc, rc.left, rc.top, false, true, RGB(0, 170, 255));
	}	
	if (lpBattleHero)
	{
		lpBattleHero->Render(hdc);
	}
	if (!vLpBattleMob.empty())
	{
		for (int i = 0; i < vLpBattleMob.size(); ++i)
		{
			vLpBattleMob[i]->Render(hdc);
		}
	}
	GameUI::Render(hdc);
}

void InGameBattle::SetBattleHero(Unit* lpHero)
{
	lpBattleHero->SetUnit(lpHero);
	lpBattleHero->SetState(UNIT_STATE::ATTACK);
	lpBattleHero->Attack();
}

void InGameBattle::SetBattleMob(vector<Mob*> vMobs)
{
	if (!vMobs.empty())
	{
		for (int i = 0; i < vMobs.size(); ++i)
		{
			vLpBattleMob.push_back(new BattleUnit());
		}
		for (int i = 0; i < vLpBattleMob.size(); ++i)
		{
			vLpBattleMob[i]->SetUnit((Unit*)vMobs[i], UNIT_POSITION::RIGHT, i);
			vLpBattleMob[i]->SetState(UNIT_STATE::ATTACK);
		}		
	}
}
