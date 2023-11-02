#pragma once
#include "GameUI.h"
#include <set>

enum class HSCROLL_ALIGN
{
	LEFT,
	RIGHT
};

enum class MULTILINE_TYPE
{
	ALIGN,
	ZIGZAG,
};

class UIHorizontalScroll : public GameUI
{
private:
	HSCROLL_ALIGN align;
	MULTILINE_TYPE multiLine;
	int maxItems;
	float margin;
	float maxMargin;
	float destMargin;
	float totalItemWidth;
	int row;

	//���ϵ�ui���� ���� �� �ڷᱸ��
	//�ι�° ���ڷ� ���� ���ؿ� ���� �Լ��� �־��ش�. -> ���⼭�� ���������� �ΰ��� �Ű������� �޾Ƽ�, width�� �� �������� ����
	set<GameUI*, function<bool(GameUI*, GameUI*)>> sLpGameUIHeightSort;
	set<GameUI*, function<bool(GameUI*, GameUI*)>> sLpGameUIWidthSort;

	int selectedChildIndex;

public:
	virtual ~UIHorizontalScroll() {};
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height, int row = 1, float margin = 0, MULTILINE_TYPE multiLine = MULTILINE_TYPE::ALIGN, HSCROLL_ALIGN align = HSCROLL_ALIGN::LEFT, int maxItems = 12);
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual GameUI* AddChildUI(GameUI* lpChild) final;
	virtual void RemoveChildUI(GameUI* lpChild) override;

	inline void SetMaxItems(int maxItems) { this->maxItems = maxItems; }
	inline void SetSelectedChildIndex(int index) { this->selectedChildIndex = index; }
	inline int GetSelectedChildIndex() { return this->selectedChildIndex; }
};

