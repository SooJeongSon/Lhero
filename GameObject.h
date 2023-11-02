#pragma once
#include "LoopHero.h"
#include "EventTrigger.h"

class GameObject : public EventTrigger
{
protected:
	POINTFLOAT pos;
	RECT rc;
	UI_ANCHOR anchor;
	int width;
	int height;
	vector<GameObject*> vChildObject;
	GameObject* lpParent;
	POINTFLOAT origin;
	bool isVisible;
	bool isCanCatchEvent;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual ~GameObject() {};
	inline virtual void SetPos(POINTFLOAT pos) { this->pos = pos; }

	template<typename T>
	static T* CreateObject()
	{
		T* lpGameObject = new T;
		lpGameObject->lpParent = nullptr;
		return lpGameObject;
	}

	template<typename T>
	static T* CreateObject(GameObject* lpParent)
	{
		T* lpGameObject = new T;
		lpGameObject->lpParent = lpParent;
		return lpGameObject;
	}
	virtual inline RECT* GetRectPointer() { return &rc; }
	virtual inline RECT GetRect()  { return rc; }
	virtual void Refresh();
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual GameObject* AddChildObject(GameObject* lpGameObject);
	virtual void RemoveChildObject(GameObject* lpGameObject);
	virtual vector<GameObject*> GetChildObject() { return this->vChildObject; };
	virtual bool GetIsVisible() { return this->isVisible; };
	virtual void SetIsVisible(bool b) { this->isVisible = b; }
	
	virtual void SetIsCanCatchEvent(bool b) { this->isCanCatchEvent = b; }
	virtual bool GetIsCanCatchEvent() { return this->isCanCatchEvent; }
	virtual GameObject* GetCurrObject() { return this; }
	virtual POINTFLOAT GetPos() { return this->pos; }
};

