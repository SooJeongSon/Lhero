#pragma once
#include "LoopHero.h"

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void onNotify(EVENT_KEY eventKey) {};
};