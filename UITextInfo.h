#pragma once
#include "GameUI.h"

class UITextInfo : public GameUI
{
private:
	string name;
	string desc;
	string equipName;
	bool isTextPrint;
	map<string, float> mAbilityValue;
	bool isEquipTextPrint;
	map<string, float> mHeroStats;

public:
	virtual ~UITextInfo() {};
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height);
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual void onNotify(EVENT_KEY eventKey);

};

