#include "UIHorizontalScroll.h"
#include <algorithm>

void UIHorizontalScroll::Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row, float margin, MULTILINE_TYPE multiLine, HSCROLL_ALIGN align, int maxItems)
{
	GameUI::Init(anchor, pos, width, height);
	this->align = align;
	this->maxItems = maxItems;
	this->margin = margin;
	this->multiLine = multiLine;
	this->row = row; 
	
	auto compareHeight = [](GameUI* a, GameUI* b) { return a->GetHeight() > b->GetHeight(); };
	sLpGameUIHeightSort = decltype(sLpGameUIHeightSort)(compareHeight);

	auto compareWidth = [](GameUI* a, GameUI* b) { return a->GetWidth() > b->GetWidth(); };
	sLpGameUIWidthSort = decltype(sLpGameUIWidthSort)(compareWidth);

	selectedChildIndex = -1;
}

void UIHorizontalScroll::Update(float deltaTime)
{
	switch (multiLine)
	{
	case MULTILINE_TYPE::ALIGN:
		for (int i = 0; i < vChildUI.size(); ++i)
		{
			if (selectedChildIndex > -1 && selectedChildIndex == i)
			{
				continue;
			}
			
			if (i == 0)
			{
				vChildUI[i]->SetPos({ 0.0f, 0.0f });
			}
			else
			{
				vChildUI[i]->SetPos({ vChildUI[i - 1]->GetWidth()*i + margin, 0.0f });
			}
		}
		break;
	case MULTILINE_TYPE::ZIGZAG:		
		for (int i = 0; i < vChildUI.size(); ++i)
		{
			if (selectedChildIndex > -1 && selectedChildIndex == i)
			{
				continue;
			}
			if (i == 0)
			{
				vChildUI[i]->SetPos({ (float)vChildUI[i]->GetWidth() * (maxItems / row-1)*(i+1) + margin *(maxItems / row - 1)*(i+1), 0.0f });
			}
			else
			{
				//i>3
				if (i >= maxItems / row - 1)
				{
					//i==3
					if (i == maxItems / row-1)
					{
						vChildUI[i]->SetPos({ (float)vChildUI[i]->GetWidth()*(i-3), 0.0f });
					}
					else
					{
						//i>=7
						if (i > (maxItems / row) * 2 - 1)
						{
							//i==8
							if (i == (maxItems / row) * 2)
							{
								vChildUI[i]->SetPos({ (float)vChildUI[i]->GetWidth()*(11-i) + margin*(11-i), vChildUI[i - 1]->GetHeight()*2 + margin*2 });
							}
							//i>8
							else
							{
								vChildUI[i]->SetPos({ (float)vChildUI[i]->GetWidth() * (11-i) + margin*(11-i), (float)vChildUI[i - 1]->GetHeight()*2 + margin*2 });
							}
						}
						//i==4,5,6
						else
						{
							vChildUI[i]->SetPos({ (float)vChildUI[i]->GetWidth()*(i-4) + margin*(i-4), (float)vChildUI[i - 1]->GetHeight() + margin });
						}
					}
				}
				//i==1, 2
				else
				{
					vChildUI[i]->SetPos({ vChildUI[i - 1]->GetWidth()* (maxItems / row - 1-i) + margin* (maxItems / row - 1-i), 0.0f });
				}
			}
		}
		break;
	}	
	GameUI::Update(deltaTime);
}

void UIHorizontalScroll::Render(HDC hdc)
{	
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	GameUI::Render(hdc);
}

GameUI* UIHorizontalScroll::AddChildUI(GameUI* lpChild)
{
	lpChild->SetAnchor(UI_ANCHOR::LEFT_TOP);
	POINTFLOAT lastItemPos;

	//갯수 예외처리, 맥스 아이템보다 커지면 , 맨 앞에꺼 삭제하고, 하나씩 위치를 당겨서 배치한다.
	switch (multiLine)
	{
	case MULTILINE_TYPE::ALIGN:
		switch (align)
		{
		case HSCROLL_ALIGN::LEFT:
			if (vChildUI.empty()) lastItemPos = { (float)-1 * lpChild->GetWidth(), 0.0f };
			else lastItemPos = vChildUI.back()->GetPos();

			if (vChildUI.size() > maxItems - 1)
			{
				RemoveChildUI(vChildUI[0]);
			}

			lpChild->SetPos({ lastItemPos.x + lpChild->GetWidth(), lastItemPos.y });
			GameUI::AddChildUI(lpChild);
			break;
		case HSCROLL_ALIGN::RIGHT:
			lpChild->SetAnchor(UI_ANCHOR::RIGHT_TOP);
			if (vChildUI.empty()) lastItemPos = { (float)lpChild->GetWidth(), 0.0f };
			else lastItemPos = vChildUI.back()->GetPos();

			if (vChildUI.size() > maxItems - 1)
			{
				RemoveChildUI(vChildUI[0]);
			}

			lpChild->SetPos({ lastItemPos.x - lpChild->GetWidth(), lastItemPos.y });
			GameUI::AddChildUI(lpChild);
			break;
		}
		break;
	case MULTILINE_TYPE::ZIGZAG:
		lpChild->SetAnchor(UI_ANCHOR::RIGHT_TOP);
		if (vChildUI.empty()) lastItemPos = { (float)lpChild->GetWidth()*3 + margin*(maxItems/row -1), 0.0f };
		else
		{
			lastItemPos = vChildUI.back()->GetPos();
		}
		if (vChildUI.size() > maxItems - 1)
		{
			RemoveChildUI(vChildUI[maxItems - 1]);
		}
		lpChild->SetPos(lastItemPos);
		GameUI::AddChildUI(lpChild, true);		
		break;
	default:
		break;
	}	
	
	sLpGameUIHeightSort.insert(lpChild);
	sLpGameUIWidthSort.insert(lpChild);

	return lpChild;
}

void UIHorizontalScroll::RemoveChildUI(GameUI* lpChild)
{
	auto it = find(vChildUI.begin(), vChildUI.end(), lpChild);
	vChildUI.erase(it);

	sLpGameUIHeightSort.erase(lpChild);
	sLpGameUIWidthSort.erase(lpChild);
}



