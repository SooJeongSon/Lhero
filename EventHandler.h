#pragma once
#include "Singleton.h"
#include "LoopHero.h"

class IObserver;
class EventHandler : public Singleton<EventHandler>
{
private:
	//이벤트용 변수들
	float eventPeriod;
	float eventElapsedTime;
	
	string name;
	string desc;
	string equipName;

	bool isMouseOver;
	bool isEquipMouseOver;
	bool isHeroExist;
	bool isBattleWin;
	bool isMobDead;
	bool isMobDeadE;

	vector<IObserver*> vIObservers;
	map<string, float> abilityValue;

public:
	void Init();
	void Update(float deltaTime);
	void notify(EVENT_KEY eventKey);
	void AddObserver(IObserver* observer);
	void RemoveObserver(IObserver* observer);
	void SetTextData(string name, string desc);
	void SetTextData(string name, map<string, float> abilityValue);

	inline void SetIsMouseOver(bool b) { this->isMouseOver = b; }
	inline bool GetIsMouseOver() { return this->isMouseOver; }
	inline string GetName() { return this->name; }
	inline string GetDesc() { return this->desc; }
	inline string GetEquipName() { return this->equipName; }
 	inline float GetDayElapsedTime() { return this->eventElapsedTime; }

	inline void SetAbilityValue(map<string, float> abilityValue) { this->abilityValue = abilityValue; }
	inline map<string, float> GetAblilityValue() { return this->abilityValue; }

	inline void SetEquipMouseOver(bool b) { this->isEquipMouseOver = b; }
	inline bool GetEquipMouseOver() { return this->isEquipMouseOver; }

	inline void SetIsHeroExist(bool b) { this->isHeroExist = b; }
	inline bool GetIsHeroExist() { return this->isHeroExist; }

	inline void SetIsBattleWin(bool b) { this->isBattleWin = b; }
	inline bool GetIsBattleWin() { return this->isBattleWin; }
	
	inline void SetIsMobDead(bool b) { this->isMobDead = b; }
	inline bool GetIsMobDead() { return this->isMobDead; }
	inline void SetIsMobDeadE(bool b) { this->isMobDeadE = b; }
	inline bool GetIsMobDeadE() { return this->isMobDeadE; }
};

