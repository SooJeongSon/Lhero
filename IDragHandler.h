#pragma once

class EventData;
class IDragHandler
{
public:
	virtual void OnDrag(EventData& eventData) = 0;
};