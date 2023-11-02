#pragma once

class EventData;
class IClickHandler
{
public:
	virtual void OnClick(EventData& eventData) = 0;
};