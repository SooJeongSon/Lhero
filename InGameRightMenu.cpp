#include "InGameRightMenu.h"
#include "Image.h"
#include "InGameEventTimer.h"
#include "UIHorizontalScroll.h"
#include "UISprite.h"
#include "Equipment.h"
#include "UIItemSlot.h"
#include "UITextInfo.h"
#include "UIProgressBar.h"
#include "Unit.h"
#include "UISprite.h"
#include "UIButton.h"

void InGameRightMenu::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);

	lpBackground = ImageManager::GetInstance()->FindImage("INGAMEINFO");

	GameUI* lpEvent = GameUI::CreateUI<InGameEventTimer>();
	lpEvent->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ WINSIZE_WIDTH - 121.0f * 2, 0.0f }, 121 * 2, 27 * 2);
	this->AddChildUI(lpEvent);

	lpItemHScroll = GameUI::CreateUI<UIHorizontalScroll>(this);
	lpItemHScroll->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ 16, 129*2 }, 98 * 2, 73*2, 3, 4.0f, MULTILINE_TYPE::ZIGZAG, HSCROLL_ALIGN::LEFT, 12);
	this->AddChildUI(lpItemHScroll); 

	lpTextInfo = GameUI::CreateUI<UITextInfo>(this);
	lpTextInfo->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ 7 * 2, 210 * 2 }, 100 * 2, 144 * 2);
	this->AddChildUI(lpTextInfo);

	lpHeroHpBar = GameUI::CreateUI<UIProgressBar>(this);
	lpHeroHpBar->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ 20*2, 116 * 2 }, 75 * 2, 7 * 2);
	this->AddChildUI(lpHeroHpBar);
	lpHeroHpBar->SetBarImg("HEROHPBAR");

	lpUIButton = GameUI::CreateUI<UIButton>(this);
	lpUIButton->Init(UI_ANCHOR::RIGHT_TOP, POINTFLOAT{ 110*2, 720-33*2 }, 35 * 2, 29 * 2);
	this->AddChildUI(lpUIButton);

	index = -1;
}

void InGameRightMenu::Update(float deltaTime)
{
	if (EventHandler::GetInstance()->GetIsMobDeadE())
	{
		UISprite* lpSprite = GameUI::CreateUI<UISprite>();
		lpSprite->Init(UI_ANCHOR::RIGHT_TOP, { 0.0f, 0.0f }, 23 * 2, 23 * 2);
		lpSprite->SetObject(GameData::GetInstance()->PickEquip());
		lpItemHScroll->AddChildUI(lpSprite);
		EventHandler::GetInstance()->SetIsMobDeadE(false);
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown('T'))
	{
		UISprite* lpSprite = GameUI::CreateUI<UISprite>();
		lpSprite->Init(UI_ANCHOR::RIGHT_TOP, { 0.0f, 0.0f }, 23 * 2, 23 * 2);
		lpSprite->SetObject(GameData::GetInstance()->PickEquip());
		lpItemHScroll->AddChildUI(lpSprite);
		EventHandler::GetInstance()->SetIsMobDeadE(false);
	}

	if (EventHandler::GetInstance()->GetIsHeroExist())
	{
		heroHp = GameData::GetInstance()->GetHeroHp();
		lpHeroHpBar->SetTargetFunc(&heroHp, GameData::GetInstance()->GetHeroMaxHp());
	}

	if (PtInRect(lpUIButton->GetRectPointer(), g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
		{
			lpUIButton->SetState(BUTTON_STATE::DOWN);
		}
		else if (lpUIButton->GetState() == BUTTON_STATE::DOWN && KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
		{
			lpUIButton->SetState(BUTTON_STATE::UP);
		}
		else
		{
			lpUIButton->SetState(BUTTON_STATE::UP);
		}	
	}

	GameUI::Update(deltaTime);
}

void InGameRightMenu::Render(HDC hdc)
{
	if (isDebugMode)
	{
		//인포 메뉴 전체의 렉트
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	if (isVisible)
	{
		lpBackground->Render(hdc, rc.left, rc.top, false, true, RGB(0, 170, 255));
		lpItemHScroll->Render(hdc);
		lpTextInfo->Render(hdc);
		lpHeroHpBar->Render(hdc);
		lpUIButton->Render(hdc);
	}
	GameUI::Render(hdc);
}

GameUI* InGameRightMenu::GetSelectedEquip()
{
	return lpItemHScroll->GetChildUI()[index];
}

void InGameRightMenu::UseEquip(GameUI* lpGameUI)
{
	lpItemHScroll->RemoveChildUI(lpGameUI);
	
}

void InGameRightMenu::OnClick(EventData& eventData)
{
	if (PtInRect(lpUIButton->GetRectPointer(), g_ptMouse))
	{
		//lpUIButton->SetState(BUTTON_STATE::DOWN);		
	}
}

void InGameRightMenu::OnDrag(EventData& eventData)
{
	if (lpItemHScroll->GetSelectedChildIndex() != -1)
	{
		index = lpItemHScroll->GetSelectedChildIndex();
		lpItemHScroll->GetChildUI()[index]->SetWorldPos(g_ptMouse);
	}
}

void InGameRightMenu::Drop(EventData& eventData)
{	
}

void InGameRightMenu::EndDrag(EventData& eventData)
{
	if (index != -1)
	{
		eventData.lpDragTarget = lpItemHScroll->GetChildUI()[index];
	}	

	if (GameData::GetInstance()->GetIsEquiped())
	{
		lpItemHScroll->RemoveChildUI(lpItemHScroll->GetChildUI()[index]);
		GameData::GetInstance()->SetIsEquiped(false);
		lpItemHScroll->SetSelectedChildIndex(-1);
	}

	if (lpItemHScroll->GetSelectedChildIndex() != -1)
	{
		index = lpItemHScroll->GetSelectedChildIndex();
		lpItemHScroll->GetChildUI()[index]->SetWorldPos(g_ptMouse);
		lpItemHScroll->SetSelectedChildIndex(-1);
	}
}

void InGameRightMenu::BeginDrag(EventData& eventData)
{
	//선택한거없을때
	if (lpItemHScroll->GetSelectedChildIndex() == -1)
	{
		for (int i = 0; i < lpItemHScroll->GetChildUI().size(); ++i)
		{
			if (PtInRect(lpItemHScroll->GetChildUI()[i]->GetRectPointer(), g_ptMouse))
			{
				
				if (typeid(*lpItemHScroll) == typeid(UIHorizontalScroll))
				{
					UIHorizontalScroll* lpTarget = (UIHorizontalScroll*)lpItemHScroll;
					lpTarget->SetSelectedChildIndex(i);
					if (typeid(*lpTarget->GetChildUI()[i]) == typeid(UISprite))
					{
						UISprite* lpUI = (UISprite*)lpTarget->GetChildUI()[i];
						lpUI->SetWorldPos(g_ptMouse);
					}
				}
				break;
			}
		}
	}

}

void InGameRightMenu::MouseEnter(EventData& eventData)
{
}

void InGameRightMenu::MouseOver(EventData& eventData)
{
}

void InGameRightMenu::MouseOut(EventData& eventData)
{
}

void InGameRightMenu::SetHeroHpBar(Unit* lpHero, float maxHp)
{
	//유닛에서 hp 가져와서
	//타겟 펑크로 넣어준다
	//최대 체력 여기에 써놨다
	lpHeroHpBar->SetTargetFunc(&heroHp, GameData::GetInstance()->GetHeroMaxHp());
}
