#pragma once
#include <Windows.h>
#include <queue>
#include <functional>
#include "Singleton.h"
#include "EventTrigger.h"
#include <set>

using namespace std;

class GameUI;
class GameObject;
class EventSystem : public Singleton<EventSystem> 
{
private:
	EventData data;
	GameUI* lpCurrUI;
	vector<EventTrigger*> vTargets;

	GameObject* lpCurrObject;
	vector<EventTrigger*> vObjectTargets;

	set<EventTrigger*> sCheck; 
	set<EventTrigger*> sCheckOut;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc); 
	GameUI* FindDisPatcher(vector<EventTrigger*>& vTargets, GameUI* lpCurrUI, POINT point);
	GameObject* FindDisPatcher(vector<EventTrigger*>& vTargets, GameObject* lpCurrUI, POINT point);
	void SetCurrUI(GameUI* lpCurrUI) { this->lpCurrUI = lpCurrUI; }
	void SetCurrObject(GameObject* lpCurrObject) { this->lpCurrObject = lpCurrObject; }
	EventData* GetEventData() { return &data; }
	void CheckEvent();
};

