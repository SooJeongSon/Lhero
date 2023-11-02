#include "EventSystem.h"
#include "GameUI.h"
#include "GameObject.h" 
#include "EventTrigger.h"
#include <Windows.h>
#include <algorithm>

HRESULT EventSystem::Init()
{
	return S_OK;
}

void EventSystem::Release()
{ 
}

void EventSystem::Update(float deltaTime)
{
	data.message.reset();
	data.point = g_ptMouse;

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
	{
		data.message[(int)EVENT_TYPE::CLICK] = true;
	}
	else if (KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
	{
		if (data.lpDragTarget)
		{
			data.message[(int)EVENT_TYPE::END_DRAG] = true;
			data.message[(int)EVENT_TYPE::DROP] = true;
		}
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LBUTTON))
	{
		if (data.isDragging)
		{
			data.message[(int)EVENT_TYPE::DRAG] = true;
		}
		else
		{
			data.message[(int)EVENT_TYPE::BEGIN_DRAG] = true;
		}		
	}


	//항상 체크해야 하는 이벤트들
	data.message[(int)EVENT_TYPE::MOUSE_ENTER] = true;
	data.message[(int)EVENT_TYPE::MOUSE_OVER] = true;
	data.message[(int)EVENT_TYPE::MOUSE_OUT] = true;

	//디스패처로 찾아올 이벤트 트리거 포인터들의 벡터
	vTargets.clear();
	vObjectTargets.clear();
	FindDisPatcher(vTargets, lpCurrUI, data.point);
	FindDisPatcher(vObjectTargets, lpCurrObject, data.point);

	//체크할 이벤트 트리거 포인터의 벡터
	data.vLpTargets.clear();
	//ui 담기
	data.vLpTargets.insert(data.vLpTargets.begin(), vTargets.crbegin(), vTargets.crend());
	//뒤에 object 담기
	data.vLpTargets.insert(data.vLpTargets.end(), vObjectTargets.crbegin(), vObjectTargets.crend());

	CheckEvent();
}

void EventSystem::Render(HDC hdc) 
{
	SetBkMode(hdc, OPAQUE);
	int lineHeight = 10;
	string text = to_string(data.point.x) + ", " + to_string(data.point.y) + " : " + to_string(data.deltaTime);
	TextOut(hdc, 300, lineHeight, text.c_str(), text.length());
	lineHeight += 15;
	for (int i = 0; i < data.vLpTargets.size(); ++i, lineHeight += 15)
	{
		text = string(typeid(*(data.vLpTargets[i])).name());
		TextOut(hdc, 300, lineHeight, text.c_str(), text.length());
	}
	for (int i = 0; i < data.vObjectLpTargets.size(); ++i, lineHeight += 15)
	{
		text = string(typeid(*(data.vObjectLpTargets[i])).name());
		TextOut(hdc, 300, lineHeight, text.c_str(), text.length());
	}
	SetBkMode(hdc, TRANSPARENT);
}

GameUI* EventSystem::FindDisPatcher(vector<EventTrigger*>& vTargets, GameUI* lpCurrUI, POINT point)
{	
	if (data.isDragging)
	{
		if (data.lpDragTarget == lpCurrUI)
		{
			return nullptr;
		}
	}
	RECT rc = lpCurrUI->GetRect();
	GameUI* lpEventTarget = nullptr;
	GameUI* lpChildTarget;
	if (PtInRect(&rc, point))
	{
		if (lpCurrUI->GetIsCanCatchEvent())
		{
			//최상단 UI부터 시작, 최상단이 이벤트를 캐치하면 안된다. (ex. rootUI)
			lpEventTarget = lpCurrUI;
			vTargets.push_back(lpCurrUI);
		}
	}
	vector<GameUI*> vLpChild = lpCurrUI->GetChildUI();
	for (int i = vLpChild.size() -1; i > -1; --i)
	{
		if (!vLpChild[i]->GetIsVisible())	continue;			
		lpChildTarget = FindDisPatcher(vTargets, vLpChild[i], point);
		if (lpChildTarget)
		{
			lpEventTarget = lpChildTarget;
			break;
		}
	} 	
	return lpEventTarget;
}

GameObject* EventSystem::FindDisPatcher(vector<EventTrigger*>& vObjectTargets, GameObject* lpCurrObject, POINT point)
{
	if (data.isDragging)
	{
		if (data.lpDragTarget == lpCurrObject)
		{
			return nullptr;
		}
	}
	RECT rc = lpCurrObject->GetRect();
	GameObject* lpEventTarget = nullptr;
	GameObject* lpChildTarget;
	if (PtInRect(&rc, point))
	{
		if (lpCurrObject->GetIsCanCatchEvent())
		{
			lpEventTarget = lpCurrObject;
			vObjectTargets.push_back(lpCurrObject);
		}
	}
	vector<GameObject*> vLpChild = lpCurrObject->GetChildObject();
	for (int i = vLpChild.size() - 1; i > -1; --i)
	{
		if (!vLpChild[i]->GetIsVisible())	continue;
		lpChildTarget = FindDisPatcher(vObjectTargets, vLpChild[i], point);
		if (lpChildTarget)
		{
			lpEventTarget = lpChildTarget;
			break;
		}
	}
	return lpEventTarget;
}

void EventSystem::CheckEvent()
{
	if (data.message[(int)EVENT_TYPE::CLICK])
	{
		data.lpLastTarget = nullptr;
		data.type = EVENT_TYPE::CLICK;
		for (int i = 0; i < data.vLpTargets.size(); ++i)
		{
			data.Use();
			data.lpLastTarget = data.vLpTargets[i];
			data.vLpTargets[i]->OnClick(data);
			if (data.vLpTargets[i]->IsCanPassEvent())
			{
				data.Reset();
			}
			else
			{
				break;
			}
		}
	}
	//둘중에 하나만 발생함
	if (data.message[(int)EVENT_TYPE::BEGIN_DRAG] || data.message[(int)EVENT_TYPE::DRAG])
	{
		//begin drag
		if (data.message[(int)EVENT_TYPE::BEGIN_DRAG])
		{
			data.lpLastTarget = nullptr;
			data.Use();
			data.type = EVENT_TYPE::BEGIN_DRAG;
			for (int i = 0; i < data.vLpTargets.size(); ++i)
			{
				data.vLpTargets[i]->BeginDrag(data);
				data.lpLastTarget = data.vLpTargets[i];
				if (data.vLpTargets[i]->IsCanPassEvent())
				{
					data.Reset();
				}
				else
				{
					break;
				}
				data.lpDragTarget = data.lpLastTarget;
			}
			data.isDragging = true;
		}
		//on drag
		else
		{
			data.lpLastTarget = nullptr;
			data.type = EVENT_TYPE::DRAG;
			data.Use();

			data.lpDragTarget->OnDrag(data);
			data.isDragging = true;
		}
	}
	//무조건 같이 발생함
	if (data.message[(int)EVENT_TYPE::END_DRAG] && data.message[(int)EVENT_TYPE::DROP])
	{		
		if (data.isDragging)
		{
			//end drag
			data.type = EVENT_TYPE::END_DRAG;
			data.Use();
			data.lpLastTarget = data.lpDragTarget;
			data.lpDragTarget->EndDrag(data);

			//on drop
			data.type = EVENT_TYPE::DROP;
			//data.lpLastTarget = data.lpDragTarget;
			for (int i = 0; i < data.vLpTargets.size(); ++i)
			{
				data.Use();
				data.vLpTargets[i]->Drop(data);
				data.lpLastTarget = data.vLpTargets[i];
				if (data.vLpTargets[i]->IsCanPassEvent())
				{
					data.Reset();
				}
				else
				{
					break;
				}
			}

			data.Use();
			data.isDragging = false;
			data.lpDragTarget = nullptr;
		}
	}

	if (data.message[(int)EVENT_TYPE::MOUSE_ENTER])
	{
		data.lpLastTarget = nullptr;
		data.type = EVENT_TYPE::MOUSE_ENTER;

		for (int i = 0; i < data.vLpTargets.size(); ++i)
		{
			if (sCheck.find(data.vLpTargets[i]) != sCheck.end())
			{
				continue;
			}
			else
			{
				data.Use();
				data.vLpTargets[i]->MouseEnter(data);
				data.lpLastTarget = data.vLpTargets[i];
				sCheck.insert(data.vLpTargets[i]);
				if (data.vLpTargets[i]->IsCanPassEvent())
				{
					data.Reset();
				}
				else
				{
					break;
				}
			}
		}
	}

	if (data.message[(int)EVENT_TYPE::MOUSE_OVER])
	{
		data.lpLastTarget = nullptr;
		data.type = EVENT_TYPE::MOUSE_OVER;
		for (int i = 0; i < data.vLpTargets.size(); ++i)
		{
			if (sCheck.find(data.vLpTargets[i]) == sCheck.end()) 
			{
				continue;
			}
			data.Use();
			data.vLpTargets[i]->MouseOver(data);
			data.lpLastTarget = data.vLpTargets[i];
			if (data.vLpTargets[i]->IsCanPassEvent())
			{
				data.Reset();
			}
			else
			{
				break;
			}
		}
	}

	if (data.message[(int)EVENT_TYPE::MOUSE_OUT])
	{
		data.lpLastTarget = nullptr;
		data.type = EVENT_TYPE::MOUSE_OUT;

		sCheckOut = sCheck;

		for (int i = 0; i < data.vLpTargets.size(); ++i)
		{
			if (data.vLpTargets[i]->IsCanPassEvent()) //실제로 처리가 된 애들만 지워준다
			{
				sCheckOut.erase(sCheckOut.find(data.vLpTargets[i]));
				data.Reset();
			}	
			else
			{
				break;
			}
		}
	
		for (auto iter = sCheckOut.begin(); iter != sCheckOut.end(); ++iter)
		{
			sCheck.erase(sCheck.find(*iter));
			data.Use();
			
			(*iter)->MouseOut(data);
			data.lpLastTarget = (*iter);
		}
		sCheckOut.clear();
	}
}

