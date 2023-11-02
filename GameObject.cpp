#include "GameObject.h"

HRESULT GameObject::Init()
{
	isCanCatchEvent = true;
	isVisible = true;
	return S_OK;
}

void GameObject::Release()
{
}

void GameObject::Update(float deltaTime)
{
	if (isVisible)
	{
		for (int i = 0; i < vChildObject.size(); ++i)
		{
			if (vChildObject[i]->isVisible)
			{
				vChildObject[i]->Update(deltaTime);
			}
		}
	}
}

void GameObject::Render(HDC hdc)
{
	if (isVisible)
	{
		for (int i = 0; i < vChildObject.size(); ++i)
		{
			if (vChildObject[i]->isVisible) vChildObject[i]->Render(hdc);
		}
	}
}

void GameObject::Refresh()
{
	RECT view;
	if (lpParent) view = lpParent->rc;
	else SetRect(&view, 0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT);

	switch (anchor)
	{
	case UI_ANCHOR::RIGHT_TOP:
		origin = { (float)view.right, (float)view.top };
		SetRect(&rc, view.right - pos.x - width, view.top + pos.y, view.right - pos.x, view.top + pos.y + height);
		break;
	case UI_ANCHOR::LEFT_BOTTOM:
		origin = { (float)view.left, (float)view.bottom };
		SetRect(&rc, view.left + pos.x, view.bottom - pos.y - height, view.left + pos.x + width, view.bottom - pos.y);
		break;
	case UI_ANCHOR::RIGHT_BOTTOM:
		origin = { (float)view.right, (float)view.bottom };
		SetRect(&rc, view.right - pos.x - width, view.bottom - pos.y - height, view.right - pos.x, view.bottom - pos.y);
		break;
	case UI_ANCHOR::MIDDLE:
		origin = { (view.right + view.left) / 2.0f, (view.top + view.bottom) / 2.0f };
		SetRect(&rc, (view.right + view.left) / 2 + pos.x - width / 2, (view.top + view.bottom) / 2 + pos.y - height / 2, (view.right + view.left) / 2 + pos.x + width / 2, (view.top + view.bottom) / 2 + pos.y + height / 2);
		break;
	case UI_ANCHOR::LEFT_MIDDLE:
		origin = { (float)view.left, (view.top + view.bottom) / 2.0f };
		SetRect(&rc, view.left + pos.x, (view.top + view.bottom) / 2 + pos.y - height / 2, view.left + pos.x + width, (view.top + view.bottom) / 2 + pos.y + height / 2);
		break;
	case UI_ANCHOR::RIGHT_MIDDLE:
		origin = { (float)view.right, (view.top + view.bottom) / 2.0f };
		SetRect(&rc, view.right - pos.x - width, (view.top + view.bottom) / 2 + pos.y - height / 2, view.right - pos.x, (view.top + view.bottom) / 2 + pos.y + height / 2);
		break;
	case UI_ANCHOR::TOP_MIDDLE:
		origin = { (view.right + view.left) / 2.0f, (float)view.top };
		SetRect(&rc, (view.right + view.left) / 2 + pos.x - width / 2, view.top + pos.y, (view.right + view.left) / 2 + pos.x + width / 2, view.top + pos.y + height);
		break;
	case UI_ANCHOR::BOTTOM_MIDDLE:
		origin = { (view.right + view.left) / 2.0f, (float)view.bottom };
		SetRect(&rc, (view.right + view.left) / 2 + pos.x - width / 2, view.bottom - pos.y - height, (view.right + view.left) / 2 + pos.x + width / 2, view.bottom - pos.y);
		break;
	case UI_ANCHOR::LEFT_TOP:
	default:
		origin = { (float)view.left, (float)view.top };
		SetRect(&rc, view.left + pos.x, view.top + pos.y, view.left + pos.x + width, view.top + pos.y + height);
		break;
	}
}

void GameObject::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
}

GameObject* GameObject::AddChildObject(GameObject* lpChild)
{
	
	lpChild->lpParent = this;
	vChildObject.push_back(lpChild);
	
	return lpChild;
}

void GameObject::RemoveChildObject(GameObject* lpGameObject)
{
	auto it = find(vChildObject.begin(), vChildObject.end(), lpGameObject);
	vChildObject.erase(it);
}