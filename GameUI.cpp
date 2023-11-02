#include "GameUI.h"

void GameUI::Refresh()
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

	for (int i = 0; i < vChildUI.size(); ++i)
	{
		vChildUI[i]->Refresh();
	}
}

void GameUI::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height)
{
	this->isVisible = true;
	this->anchor = anchor;
	this->pos = pos;
	this->width = width;
	this->height = height;

	isCanCatchEvent = true;

	Refresh();
}

void GameUI::Release()
{
}

void GameUI::Update(float deltaTime)
{
	if (isVisible)
	{
		for (int i = 0; i < vChildUI.size(); ++i)
		{
			if (vChildUI[i]->isVisible)
			{
				vChildUI[i]->Update(deltaTime);
			}
		}
	}
}

void GameUI::Render(HDC hdc)
{
	if (isVisible)
	{
		for (int i = 0; i < vChildUI.size(); ++i)
		{
			if (vChildUI[i]->isVisible) vChildUI[i]->Render(hdc);
		}
	}
}

GameUI* GameUI::AddChildUI(GameUI* lpChild, bool isReverse)
{
	if (isReverse)
	{
		lpChild->lpParent = this;
		lpChild->Refresh();
		vChildUI.insert(vChildUI.begin(), lpChild);
	}
	else
	{
		lpChild->lpParent = this;
		lpChild->Refresh();
		vChildUI.push_back(lpChild);
	}

	return lpChild;
}

void GameUI::RemoveChildUI(GameUI* lpChild)
{
	auto it = find(vChildUI.begin(), vChildUI.end(), lpChild);
	(*it)->Release();
	vChildUI.erase(it);
}

void GameUI::SetRectByMouse(POINT pos)
{
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + width;
	rc.bottom = pos.y + height;
}

void GameUI::SetWorldPos(POINT point)
{
	LONG a;
	LONG b;

	switch (anchor)	
	{
	case UI_ANCHOR::LEFT_TOP:
		a = point.x - lpParent->GetRect().left;
		b = point.y - lpParent->GetRect().top;
		break;
	case UI_ANCHOR::RIGHT_TOP:
		a = lpParent->GetRect().right - point.x;
		b = point.y - lpParent->GetRect().top;
		break;
	case UI_ANCHOR::LEFT_BOTTOM:
		a = point.x - lpParent->GetRect().left;
		b = point.y - lpParent->GetRect().bottom;
		break;
	case UI_ANCHOR::RIGHT_BOTTOM:
		a = point.x - lpParent->GetRect().right;
		b = point.y - lpParent->GetRect().bottom;
		break;
	case UI_ANCHOR::LEFT_MIDDLE:
		break;
	case UI_ANCHOR::TOP_MIDDLE:
		break;
	case UI_ANCHOR::RIGHT_MIDDLE:
		break;
	case UI_ANCHOR::BOTTOM_MIDDLE:
		break;
	case UI_ANCHOR::MIDDLE:
		break;
	case UI_ANCHOR::NONE:
		break;
	default:
		break;
	}

	pos.x = a;
	pos.y = b;
	Refresh();
}

