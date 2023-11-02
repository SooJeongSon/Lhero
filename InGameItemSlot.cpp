#include "InGameItemSlot.h"
#include "UIGrid.h"
#include "Equipment.h"
#include "UISprite.h"
#include "Hero.h"
#include "InGameRightMenu.h"

void InGameItemSlot::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);

	lpUIGrid = GameUI::CreateUI<UIGrid>(this);
	lpUIGrid->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ 0.0f, 0.0f }, 105 * 2, 78 * 2);
	this->AddChildUI(lpUIGrid);
	
	SetRect(&rc, pos.x, pos.y, pos.x + width, pos.y + height);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == 0)
			{
				isOpenSlot[j][i] = true;
			}
			else if (i == 1 && j == 2)
			{
				isOpenSlot[j][i] = true;
			}
			else
			{
				isOpenSlot[j][i] = false;
			}
		}
	}

	lpEquipTable = new EquipTable();
	lpEquipTable->Init();

	lpSelectedEquip = nullptr;
	
	index = -1;
}

void InGameItemSlot::Update(float deltaTime)
{
	GameUI::Update(deltaTime);
}

void InGameItemSlot::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	if (lpUIGrid)
	{
		lpUIGrid->Render(hdc);
	}
	GameUI::Render(hdc);
}

GameUI* InGameItemSlot::GetSelectedEquip()
{
	return lpUIGrid->GetChildUI()[index];
}

void InGameItemSlot::OnClick(EventData& eventData)
{
}

void InGameItemSlot::OnDrag(EventData& eventData)
{
}

void InGameItemSlot::Drop(EventData& eventData)
{
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - 1062) / 52;
	int y = (mPoint.y - 26*2) / 50;
	//장비
	if (typeid(*eventData.lpDragTarget) == typeid(UISprite))
	{
		UISprite* lpTarget = (UISprite*)eventData.lpDragTarget;
		if (typeid(*(lpTarget->GetObjectPointer())) == typeid(Equipment))
		{
			Equipment* lpEquip = (Equipment*)lpTarget->GetObjectPointer();
			lpSelectedEquip = lpEquipTable->GetEquip(lpEquip->GetEquipId());
			if (isOpenSlot[y][x])
			{
				if (lpEquip->GetEquipId() == "weapons" && (y==0 && x ==0))
				{
					UISprite* lpSprite = GameUI::CreateUI<UISprite>(lpUIGrid);
					lpSprite->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 0.0f }, 26 * 2, 25 * 2);
					lpSprite->SetObject(lpEquip);
					lpUIGrid->AddChildUI(lpSprite);
					lpEquip->SetPos({ (float)lpUIGrid->GetRect().left + 0.0f + 26.0f, (float)lpUIGrid->GetRect().top + 0.0f + 25.0f });
					float dmg = lpEquip->GetAbilityValue()["DMG"];
					GameData::GetInstance()->SetAttackDmg(dmg);
					
					GameData::GetInstance()->SetIsEquiped(true);
				}

				if (lpEquip->GetEquipId() == "rings" && (y == 1 && x == 0))
				{
					UISprite* lpSprite = GameUI::CreateUI<UISprite>(lpUIGrid);
					lpSprite->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 53.0f }, 26 * 2, 25 * 2);
					lpSprite->SetObject(lpEquip);
					lpUIGrid->AddChildUI(lpSprite);
					lpEquip->SetPos({ (float)lpUIGrid->GetRect().left + 0.0f + 26.0f, (float)lpUIGrid->GetRect().top + 53.0f + 25.0f });
					GameData::GetInstance()->SetIsEquiped(true);

				}

				if (lpEquip->GetEquipId() == "shields" && (y == 2 && x == 0))
				{
					UISprite* lpSprite = GameUI::CreateUI<UISprite>(lpUIGrid);
					lpSprite->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 106.0f }, 26 * 2, 25 * 2);
					lpSprite->SetObject(lpEquip);
					lpUIGrid->AddChildUI(lpSprite);
					lpEquip->SetPos({ (float)lpUIGrid->GetRect().left + 0.0f + 26.0f, (float)lpUIGrid->GetRect().top + 106.0f + 25.0f });
					GameData::GetInstance()->SetIsEquiped(true);

				}
				if (lpEquip->GetEquipId() == "armors" && (y == 2 && x == 1))
				{
					UISprite* lpSprite = GameUI::CreateUI<UISprite>(lpUIGrid);
					lpSprite->Init(UI_ANCHOR::LEFT_TOP, {56.0f, 106.0f }, 26 * 2, 25 * 2);
					lpSprite->SetObject(lpEquip);
					lpUIGrid->AddChildUI(lpSprite);
					lpEquip->SetPos({ (float)lpUIGrid->GetRect().left + 56.0f + 26.0f, (float)lpUIGrid->GetRect().top + 106.0f + 25.0f });
					GameData::GetInstance()->SetIsEquiped(true);

				}
			}
			else
			{
				//장비 장착 실패
				GameData::GetInstance()->SetIsEquiped(false);
			}
		}
	}
}

void InGameItemSlot::EndDrag(EventData& eventData)
{
}

void InGameItemSlot::BeginDrag(EventData& eventData)
{
}

void InGameItemSlot::MouseEnter(EventData& eventData)
{
}

void InGameItemSlot::MouseOver(EventData& eventData)
{
	//정보 출력
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - 1062) / 52;
	int y = (mPoint.y - 26 * 2) / 50;

	for (int i = 0; i < lpUIGrid->GetChildUI().size(); ++i)
	{
		if (PtInRect(lpUIGrid->GetChildUI()[i]->GetRectPointer(), g_ptMouse))
		{
			if (typeid(*lpUIGrid->GetChildUI()[i]) == typeid(UISprite))
			{
				UISprite* lpUI = (UISprite*)lpUIGrid->GetChildUI()[i];
				if (lpUI->GetObjectPointer())
				{
					if (typeid(*lpUI->GetObjectPointer()) == typeid(Equipment))
					{
						Equipment* lpEq = (Equipment*)lpUI->GetObjectPointer();
						EventHandler::GetInstance()->SetAbilityValue(lpEq->GetAbilityValue());
						EventHandler::GetInstance()->SetTextData(lpEq->GetEquipId(), lpEq->GetAbilityValue());
						EventHandler::GetInstance()->SetEquipMouseOver(true);
						break;
					}
				}			
			}			
		}
	}
}

void InGameItemSlot::MouseOut(EventData& eventData)
{
	map<string, float> map;
	EventHandler::GetInstance()->SetAbilityValue(map);
	EventHandler::GetInstance()->SetTextData("", map);
	EventHandler::GetInstance()->SetEquipMouseOver(false);
}
