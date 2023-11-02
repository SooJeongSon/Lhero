#pragma once
#include <Windows.h>
#include "IClickHandler.h"
#include "IDragHandler.h"
#include "IDropHandler.h"
#include <bitset>
#include <vector> 

using namespace std;

enum class EVENT_TYPE
{
	CLICK,
	BEGIN_DRAG,
	DRAG,
	END_DRAG,
	DROP,
	MOUSE_ENTER,
	MOUSE_OVER,
	MOUSE_OUT,
	NONE
};

enum class EVENT_CATCH
{
	BLOCK,
	BLOCK_PASS,
	PASS
};

class EventTrigger;
struct EventData
{
	bitset<(int)EVENT_TYPE::NONE> message;

	float deltaTime;
	POINT point;
	EVENT_TYPE type;
	vector<EventTrigger*> vLpTargets;
	vector<EventTrigger*> vObjectLpTargets;
	EventTrigger* lpLastTarget;
	EventTrigger* lpDragTarget;
	POINT dragPoint;
	bool isDragging;


	void Use()
	{
		message[(int)type] = false;
	}
	void Reset()
	{
		//�̺�Ʈ ����� ���� �ʾҴ�
		message[(int)type] = true;
	}

	//any -> ��Ʈ���� �ϳ��� 1�̸� 1�� ��ȯ
	bool IsRemain() { return message.any(); }
	bool IsRemain(EVENT_TYPE type) { return message[(int)type]; }
	
};

class EventTrigger : public IClickHandler, public IDragHandler, public IDropHandler 
{
private:
	EVENT_CATCH catchType;

public:
	virtual ~EventTrigger() {};
	//�ֻ��� ��ü�� �Լ��� ������ �̺�Ʈ �ʱ�ȭ
	virtual void OnClick(EventData& eventData) { eventData.Reset(); };
	virtual void OnDrag(EventData& eventData) { eventData.Reset(); };
	virtual void Drop(EventData& eventData) { eventData.Reset(); };
	virtual void EndDrag(EventData& eventData) { eventData.Reset(); }
	virtual void BeginDrag(EventData& eventData) { eventData.Reset(); }
	virtual void MouseEnter(EventData& eventData) { eventData.Reset(); }
	virtual void MouseOver(EventData& eventData) { eventData.Reset(); }
	virtual void MouseOut(EventData& eventData) { eventData.Reset(); }

	virtual EVENT_CATCH GetCatchType() { return catchType; }
	virtual void SetCatchType(EVENT_CATCH catchType) { this->catchType = catchType; }
	virtual bool IsCanPassEvent() { if (catchType == EVENT_CATCH::BLOCK) return true; else return false; }
};