#include "InGameBattleUnit.h"
#include "UISprite.h"
#include "BattleUnit.h"
#include "Hero.h"

void InGameBattleUnit::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);	
}

void InGameBattleUnit::Release()
{
}

void InGameBattleUnit::Update(float deltaTime)
{
	GameUI::Update(deltaTime);
}

void InGameBattleUnit::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}	
	GameUI::Render(hdc);
}
