#pragma once
#include "GameUI.h"

class UIGrid;
class EquipTable;
class EQUIP;
class Equipment;
class InGameItemSlot : public GameUI
{
private:
	UIGrid* lpUIGrid;
	EventData eventData;
	bool isOpenSlot[4][3];
	EquipTable* lpEquipTable;
	EQUIP* lpSelectedEquip;

	int index;


public:
	virtual void Init(UI_ANCHOR anchor, POINTFLOAT pos, int width, int height) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual GameUI* GetSelectedEquip();

	virtual void OnClick(EventData& eventData) override;
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
};

