#include "UITextInfo.h"

void UITextInfo::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	EventHandler::GetInstance()->AddObserver(this);
	GameUI::Init(anchor, pos, width, height);
}

void UITextInfo::Release()
{
}

void UITextInfo::Update(float deltaTime)
{
	if (EventHandler::GetInstance()->GetIsHeroExist())
	{
		mHeroStats = GameData::GetInstance()->GetHeroStat();
	}	
}

void UITextInfo::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

	if (!EventHandler::GetInstance()->GetEquipMouseOver())
	{
		equipName = EventHandler::GetInstance()->GetEquipName();
		mAbilityValue = EventHandler::GetInstance()->GetAblilityValue();
		isEquipTextPrint = EventHandler::GetInstance()->GetEquipMouseOver();
	}
	mHeroStats = GameData::GetInstance()->GetHeroStat();

	if (isEquipTextPrint)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, rc.left + 75, rc.top + 10, equipName.c_str(), equipName.length());
		RECT rc2{ rc.left, rc.top + 100, rc.right, rc.bottom };
		for (auto iter = mAbilityValue.begin(); iter != mAbilityValue.end(); ++iter)
		{
			TextOut(hdc, rc2.left, rc2.top, iter->first.c_str(), iter->first.length());
			TextOut(hdc, rc2.left + 100, rc2.top, to_string(iter->second).c_str(), 3);
			SetRect(&rc2, rc2.left, rc2.top + 20, rc2.right, rc2.bottom);
		}
		SetTextColor(hdc, RGB(0, 0, 0));
	}
	else if (isTextPrint)
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		TextOut(hdc, rc.left + 75, rc.top + 10, name.c_str(), name.length());
		RECT rc2{ rc.left, rc.top + 100, rc.right, rc.bottom };
		DrawText(hdc, desc.c_str(), desc.length(), &rc2, DT_WORDBREAK);
		SetTextColor(hdc, RGB(0, 0, 0));
	}
	else
	{
		if (EventHandler::GetInstance()->GetIsHeroExist())
		{
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, rc.left + 75, rc.top + 10, "Warrior", 7);
			RECT rc2{ rc.left, rc.top + 100, rc.right, rc.bottom };
			mHeroStats = GameData::GetInstance()->GetHeroStat();
			for (auto iter = mHeroStats.begin(); iter != mHeroStats.end(); ++iter)
			{
				TextOut(hdc, rc2.left, rc2.top, iter->first.c_str(), iter->first.length());
				TextOut(hdc, rc2.left + 100, rc2.top, to_string(iter->second).c_str(), 5);
				SetRect(&rc2, rc2.left, rc2.top + 20, rc2.right, rc2.bottom);
			}
			SetTextColor(hdc, RGB(0, 0, 0));
		}
	}	
}

void UITextInfo::onNotify(EVENT_KEY eventKey)
{
	switch (eventKey)	
	{
	case EVENT_KEY::TEXTPRINT:
		name = EventHandler::GetInstance()->GetName();
		desc = EventHandler::GetInstance()->GetDesc();
		isTextPrint = EventHandler::GetInstance()->GetIsMouseOver();
		break;
	case EVENT_KEY::EQUIPTEXTPRINT:
		name = EventHandler::GetInstance()->GetName();
		mAbilityValue = EventHandler::GetInstance()->GetAblilityValue();
		isEquipTextPrint = EventHandler::GetInstance()->GetEquipMouseOver();
		isTextPrint = false;
		break;
	case EVENT_KEY::SPAWN:
	case EVENT_KEY::NONE:
		name = EventHandler::GetInstance()->GetName();
		desc = EventHandler::GetInstance()->GetDesc();
		isTextPrint = false;
		isEquipTextPrint = false;
	default:
		break;
	}
}
