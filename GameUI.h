#pragma once
#include "LoopHero.h"
#include "EventTrigger.h"
#include "IObserver.h"


class GameUI : public EventTrigger, public IObserver
{
private:
	function<bool(POINT)> onClick;

protected:
	GameUI* lpParent;
	vector<GameUI*> vChildUI; 
	bool isVisible;
	UI_ANCHOR anchor;
	int width;
	int height;
	POINTFLOAT origin;
	POINTFLOAT pos;
	RECT rc;
	int depth;
	bool isCanCatchEvent;

protected:
	GameUI() {}

	virtual bool OnClick(POINT point) { return PtInRect(&rc, point); }
	

public:
	virtual ~GameUI() {}
	virtual void Refresh();
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);

	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	template<typename T>
	static T* CreateUI()
	{
		T* lpGameUI = new T;
		lpGameUI->lpParent = nullptr;
		//lpGameUI->onClick = bind(&GameUI::OnClick, lpGameUI, placeholders::_1);
		return lpGameUI;
	}

	template<typename T>
	static T* CreateUI(GameUI* lpParent)
	{
		T* lpGameUI = new T;
		lpGameUI->lpParent = lpParent;
		//if (!lpParent)
		//{
		//	lpGameUI->depth = 0;
		//}
		//else
		//{
		//	lpGameUI->depth = lpParent->GetDepth() + 1;
		//}

		//lpGameUI->onClick = bind(&GameUI::OnClick, lpGameUI, placeholders::_1);

		return lpGameUI;
	}

	virtual GameUI* AddChildUI(GameUI* lpChild, bool isReverse = false);
	//Ãß°¡
	virtual void RemoveChildUI(GameUI* lpChild);
	virtual vector<GameUI*> GetChildUI() { return this->vChildUI; }
	//
	virtual inline void SetAnchor(UI_ANCHOR anchor) { this->anchor = anchor; }
	virtual inline void SetPos(POINTFLOAT pos) final { this->pos = pos; Refresh(); }
	virtual inline void SetVisible(bool isVisible) final { this->isVisible = isVisible; }
	virtual inline POINTFLOAT GetPos() final { return pos; }
	virtual inline RECT GetRect() final { return rc; }
	virtual inline RECT* GetRectPointer() final { return &rc; }
	virtual inline int GetWidth() final { return width; }
	virtual inline int GetHeight() final { return height; }

	virtual int GetDepth() { return this->depth; }
	virtual bool GetIsVisible() { return this->isVisible; }
	virtual void SetRectByMouse(POINT pos);
	virtual void SetWorldPos(POINT point);

	virtual void SetIsCanCatchEvent(bool b) { this->isCanCatchEvent = b; }
	virtual bool GetIsCanCatchEvent() { return this->isCanCatchEvent; }
	virtual GameUI* GetCurrUI() { return this; }
	
	virtual void OnClick() {};

};