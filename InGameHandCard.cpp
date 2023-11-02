#include "InGameHandCard.h"
#include "Card.h"
#include "Deck.h"
#include "UIHorizontalScroll.h"
#include "UISprite.h"
#include "EventSystem.h"

void InGameHandCard::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	GameUI::Init(anchor, pos, width, height);
	moveSpeed = 200;
	initPos = pos;

	lpHorizontalScroll = GameUI::CreateUI<UIHorizontalScroll>(this);
	lpHorizontalScroll->Init(UI_ANCHOR::LEFT_BOTTOM, { 0.0f, 0.0f }, width, height);
	this->AddChildUI(lpHorizontalScroll);

	index = -1;
}

void InGameHandCard::Update(float deltaTime)
{
	if (EventHandler::GetInstance()->GetIsMobDead())
	{
		UISprite* lpSprite = GameUI::CreateUI<UISprite>(this);
		lpSprite->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 0.0f }, 41 * 2, 58 * 2);
		lpSprite->SetObject(GameData::GetInstance()->PickCard());
		lpHorizontalScroll->AddChildUI(lpSprite);
		EventHandler::GetInstance()->SetIsMobDead(false);
	}

	if (PtInRect(&rc, g_ptMouse))
	{
		pos.y += moveSpeed * deltaTime;
		if (pos.y - initPos.y > 40) pos.y = initPos.y + 40;

		Refresh();
	}
	else
	{
		pos.y -= moveSpeed * deltaTime;
		if (pos.y - initPos.y < 0) pos.y = initPos.y;

		Refresh();
	}
	
	GameUI::Update(deltaTime);
}

void InGameHandCard::Render(HDC hdc)
{
	if (isDebugMode)
	{
		//손패 전체의 렉트
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

	if (lpHorizontalScroll)
	{
		lpHorizontalScroll->Render(hdc);
	}	
}

GameUI* InGameHandCard::GetSelectedCard()
{
	return lpHorizontalScroll->GetChildUI()[index];
}

void InGameHandCard::UseCard(GameUI* lpGameUI)
{
	lpHorizontalScroll->RemoveChildUI(lpGameUI);
}

void InGameHandCard::OnClick(EventData& eventData)
{
	if (lpHorizontalScroll->GetSelectedChildIndex() == -1)
	{
		for (int i = 0; i < lpHorizontalScroll->GetChildUI().size(); ++i)
		{
			if (PtInRect(lpHorizontalScroll->GetChildUI()[i]->GetRectPointer(), g_ptMouse))
			{
				UISprite* lpUI = (UISprite*)lpHorizontalScroll->GetChildUI()[i];
				lpHorizontalScroll->SetSelectedChildIndex(i);
				lpUI->SetWorldPos(g_ptMouse);
			}
		}			
	}
}

void InGameHandCard::OnDrag(EventData& eventData)
{	

	if (lpHorizontalScroll->GetSelectedChildIndex() != -1)
	{
		index = lpHorizontalScroll->GetSelectedChildIndex();
		lpHorizontalScroll->GetChildUI()[index]->SetWorldPos(g_ptMouse);
		if (typeid(*lpHorizontalScroll->GetChildUI()[index]) == typeid(UISprite))
		{
			UISprite* lpUI = (UISprite*)lpHorizontalScroll->GetChildUI()[index];
			if (typeid(*lpUI->GetObjectPointer()) == typeid(Card))
			{
				Card* lpCard = (Card*)lpUI->GetObjectPointer();
				lpCard->SetIsNowSelected(true);
			}
		}	
	}
}

void InGameHandCard::Drop(EventData& eventData)
{	
}

void InGameHandCard::EndDrag(EventData& eventData)
{	
	if (index != -1)
	{
		eventData.lpDragTarget = lpHorizontalScroll->GetChildUI()[index];
	}

	if (GameData::GetInstance()->GetIsCardUsed())
	{
		lpHorizontalScroll->RemoveChildUI(lpHorizontalScroll->GetChildUI()[index]);
		GameData::GetInstance()->SetIsCardUsed(false);
		lpHorizontalScroll->SetSelectedChildIndex(-1);
	}
	
	if(lpHorizontalScroll->GetSelectedChildIndex() != -1)
	{
		index = lpHorizontalScroll->GetSelectedChildIndex();
		lpHorizontalScroll->GetChildUI()[index]->SetWorldPos(g_ptMouse);
		if (typeid(*lpHorizontalScroll->GetChildUI()[index]) == typeid(UISprite))
		{
			UISprite* lpUI = (UISprite*)lpHorizontalScroll->GetChildUI()[index];
			if (typeid(*lpUI->GetObjectPointer()) == typeid(Card))
			{
				Card* lpCard = (Card*)lpUI->GetObjectPointer();
				lpCard->SetIsNowSelected(false);
			}
		}
		lpHorizontalScroll->SetSelectedChildIndex(-1);
	}	
}

void InGameHandCard::BeginDrag(EventData& eventData)
{	
	if (lpHorizontalScroll->GetSelectedChildIndex() != -1)
	{
		index = lpHorizontalScroll->GetSelectedChildIndex();
		lpHorizontalScroll->GetChildUI()[index]->SetWorldPos(g_ptMouse);
		if (typeid(*lpHorizontalScroll->GetChildUI()[index]) == typeid(UISprite))
		{
			UISprite* lpUI = (UISprite*)lpHorizontalScroll->GetChildUI()[index];
			if (typeid(*lpUI->GetObjectPointer()) == typeid(Card))
			{
				Card* lpCard = (Card*)lpUI->GetObjectPointer();
				lpCard->SetIsNowSelected(true);
			}
		}
	}
}

void InGameHandCard::MouseEnter(EventData& eventData)
{
}

void InGameHandCard::MouseOver(EventData& eventData)
{
}

void InGameHandCard::MouseOut(EventData& eventData)
{
}

