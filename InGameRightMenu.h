#pragma once
#include "GameUI.h"

class Image;
class UIHorizontalScroll;
class UIItemSlot;
class UITextInfo;
class UIProgressBar; 
class Unit;
class UISprite;
class UIButton;
class InGameRightMenu : public GameUI
{
private:
	Image* lpBackground;
	UIHorizontalScroll* lpItemHScroll;
	UITextInfo* lpTextInfo;
	UIProgressBar* lpHeroHpBar;
	UIButton* lpUIButton;
	EventData eventData;
	vector<string> desc;
	int index;	
	float heroHp;	

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual GameUI* GetSelectedEquip();
	virtual void UseEquip(GameUI* lpGameUI);

	virtual void OnClick(EventData& eventData) override;
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);

	virtual void SetHeroHpBar(Unit* lpHero, float maxHp=10.0f);
};

