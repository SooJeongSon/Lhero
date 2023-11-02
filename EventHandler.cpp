#include "EventHandler.h"
#include "IObserver.h"


void EventHandler::Init()
{
	eventPeriod = 3.0f;
	eventElapsedTime = 0.0f;
	isMouseOver = false;
	isEquipMouseOver = false;
	isHeroExist = false;
	isBattleWin = false;
	isMobDead = false;
	isMobDeadE = false;
}

void EventHandler::Update(float deltaTime)
{
	eventElapsedTime += 1.0f * deltaTime;
	if (eventElapsedTime > eventPeriod)
	{
		eventElapsedTime = 0;
		EventHandler::notify(EVENT_KEY::SPAWN);
	}

	if (isMouseOver)
	{
		EventHandler::notify(EVENT_KEY::TEXTPRINT);	
		isMouseOver = false;
	}

	if (isEquipMouseOver)
	{
		EventHandler::notify(EVENT_KEY::EQUIPTEXTPRINT);
		isEquipMouseOver = false;
	}
}

void EventHandler::notify(EVENT_KEY eventKey)
{
	for (int i = 0; i < vIObservers.size(); ++i)
	{
		vIObservers[i]->onNotify(eventKey);
	}
}

void EventHandler::AddObserver(IObserver* observer)
{
	vIObservers.push_back(observer);
}

void EventHandler::RemoveObserver(IObserver* observer)
{
	auto it = find(vIObservers.begin(), vIObservers.end(), observer);
	vIObservers.erase(it);
}

void EventHandler::SetTextData(string name, string desc)
{
	this->name = name;
	this->desc = desc;
}

void EventHandler::SetTextData(string name, map<string, float> abilityValue)
{
	this->equipName = name;
	this->abilityValue = abilityValue;
}
