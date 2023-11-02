#include "BattleUnit.h"
#include "Unit.h"
#include "Animation.h"

HRESULT BattleUnit::Init()
{
	return S_OK;
}

void BattleUnit::Release()
{
}

void BattleUnit::Update(float deltaTime)
{
	mLpAnimations[state]->Update(deltaTime);
}

void BattleUnit::Render(HDC hdc)
{
	if (position == UNIT_POSITION::LEFT)
	{
		mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 300, WINSIZE_HEIGHT / 2);
	}
	else
	{
		if (unitIndex == 0)
		{
			mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 50, WINSIZE_HEIGHT / 2);
		}
		else if (unitIndex == 1)
		{
			mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 50, WINSIZE_HEIGHT / 2 - unitIndex * 100);
		}
		else if (unitIndex == 2)
		{
			mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 50, WINSIZE_HEIGHT / 2 + (unitIndex / 2) * 100);
		}
		else if (unitIndex == 3)
		{
			mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 50 + 100, WINSIZE_HEIGHT / 2 + 50);
		}
		else
		{
			mLpAnimations[state]->Render(hdc, WINSIZE_WIDTH / 2 - 50 + 100, WINSIZE_HEIGHT / 2 - 50);
		}
	}
}

void BattleUnit::SetUnit(Unit* lpUnit, UNIT_POSITION position, int unitIndex)
{
	this->lpUnit = lpUnit;
	this->action = 0;
	this->isAtkReady = false;
	this->position = position;
	this->unitIndex = unitIndex;

	string id = lpUnit->GetName();
	mLpAnimations.insert(make_pair(UNIT_STATE::INTRO, new Animation()));
	mLpAnimations[UNIT_STATE::INTRO]->Change(id + "_intro", 5, true, true);
	mLpAnimations[UNIT_STATE::INTRO]->SetCallBack(bind(&BattleUnit::Intro, this));

	mLpAnimations.insert(make_pair(UNIT_STATE::IDLE, new Animation()));
	mLpAnimations[UNIT_STATE::IDLE]->Change(id + "_idle", 5, false, true);
	mLpAnimations[UNIT_STATE::IDLE]->SetCallBack(bind(&BattleUnit::Idle, this));

	mLpAnimations.insert(make_pair(UNIT_STATE::ATTACK, new Animation()));
	mLpAnimations[UNIT_STATE::ATTACK]->Change(id + "_attack", 5, true, true);
	mLpAnimations[UNIT_STATE::ATTACK]->SetCallBack(bind(&BattleUnit::Attack, this));

	mLpAnimations.insert(make_pair(UNIT_STATE::DEATH, new Animation()));
	mLpAnimations[UNIT_STATE::DEATH]->Change(id + "_death", 5, true, true);
	mLpAnimations[UNIT_STATE::DEATH]->SetCallBack(bind(&BattleUnit::Death, this));

	mLpAnimations.insert(make_pair(UNIT_STATE::HURT, new Animation()));
	mLpAnimations[UNIT_STATE::HURT]->Change(id + "_hurt", 5, true, true);
	mLpAnimations[UNIT_STATE::HURT]->SetCallBack(bind(&BattleUnit::Hurt, this));

	mLpAnimations.insert(make_pair(UNIT_STATE::REVIVE, new Animation()));
	mLpAnimations[UNIT_STATE::REVIVE]->Change(id + "_revive", 5, true, true);
	mLpAnimations[UNIT_STATE::REVIVE]->SetCallBack(bind(&BattleUnit::Revive, this));

}

void BattleUnit::Intro()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::INTRO;
	mLpAnimations[state]->Play();
}

void BattleUnit::Idle()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::IDLE;
	mLpAnimations[state]->Play();
}

void BattleUnit::Attack()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::ATTACK;
	mLpAnimations[state]->Play();
}

void BattleUnit::Death()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::DEATH;
	mLpAnimations[state]->Play();
}

void BattleUnit::Hurt()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::HURT;
	mLpAnimations[state]->Play();
}

void BattleUnit::Revive()
{
	mLpAnimations[state]->Stop();
	state = UNIT_STATE::REVIVE;
	mLpAnimations[state]->Play();
}
