#pragma once
#include "GameUI.h"

class UIHorizontalScroll; 
class UISprite;
class InGameHandCard : public GameUI
{
private:
	int moveSpeed;
	POINTFLOAT initPos;
	UIHorizontalScroll* lpHorizontalScroll; 

	//EventData* eventData;
	int index;
	//char szText[128];

public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual GameUI* GetSelectedCard();
	virtual void UseCard(GameUI* lpGameUI);

	virtual void OnClick(EventData& eventData) override;
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
};

