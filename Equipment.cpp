#include "Equipment.h"
#include "Image.h"

HRESULT Equipment::Init()
{
	lpEquipIcon = ImageManager::GetInstance()->FindImage("equip");
	lpEquipRare = ImageManager::GetInstance()->FindImage("equip_rare");

	//pos = { 0, 0 };

	width = 25 * 2;
	height = 25 * 2;

	SetRect(&rc, pos.x - width / 2, pos.y - height / 2, pos.x + width / 2, pos.y + height / 2);

    return S_OK; 
}

void Equipment::Release()
{
}

void Equipment::Update(float deltaTime)
{
	SetRect(&rc, (int)pos.x - width / 2, (int)pos.y - height / 2, (int)pos.x + width / 2, (int)pos.y + height / 2);

	GameObject::Update(deltaTime);
}

void Equipment::Render(HDC hdc)
{
	if (lpEquipRare)
	{
		lpEquipRare = ImageManager::GetInstance()->FindImage("equip_rare");
		lpEquipRare->FrameRender(hdc, pos.x, pos.y, rank, 0, true, 1, true, RGB(0, 170, 255));
	}

	if (lpEquipIcon)
	{
		lpEquipIcon = ImageManager::GetInstance()->FindImage("equip");	
		lpEquipIcon->FrameRender(hdc, pos.x, pos.y, max, x, true, 1, true, RGB(0, 170, 255));
	}
	GameObject::Render(hdc);
}

void Equipment::SetEquipImage(string id, int index, int type, int rank)
{
	// index 가로축
	// type 세로축
	this->id = id;
	this->x = type;
	this->max = index;
	this->rank = rank;
}

void Equipment::OnClick(EventData& eventData)
{
}

void Equipment::OnDrag(EventData& eventData)
{
}

void Equipment::Drop(EventData& eventData)
{
}

void Equipment::EndDrag(EventData& eventData)
{
}

void Equipment::BeginDrag(EventData& eventData)
{
}

void Equipment::MouseEnter(EventData& eventData)
{
}

void Equipment::MouseOver(EventData& eventData)
{
}

void Equipment::MouseOut(EventData& eventData)
{
}
