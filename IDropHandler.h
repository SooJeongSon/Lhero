#pragma once

class EventData;
class IDropHandler
{
public:
	virtual void Drop(EventData& eventData) = 0;
};