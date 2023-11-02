#pragma once
#include "GameObject.h"

enum class CARD_TYPE
{
	ROAD,
	ROAD_SIDE,
	ENVIRONMENT,
	SPECIAL,
	NONE
};

enum class CARD_RARE
{
	NORMAL,
	RARE,
	EPIC,
	NONE
};

class Deck;
class Card : public GameObject
{
private:
	CARD_TYPE type;
	CARD_RARE rare;
	Image* lpIconImg;
	Image* lpCardImg;

	string id;
	string name;
	string desc;

	string tileKey;

	RECT rc;
	int width;
	int height;

	HFONT hFont;
	HFONT hOldFont;

	bool isNowSelected;

private:
	Card() :hFont(NULL) {}
	Card(const Card& other) = default;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	inline Image* GetIconImg() { return lpIconImg; }
	inline Image* GetCardImg() { return lpCardImg; }
	inline void SetCardImg(Image* lpCardImg) { this->lpCardImg = lpCardImg; }
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline string GetCardKey() { return this->tileKey; }

	void SetIsNowSelected(bool b) { this->isNowSelected = b; }
	bool GetIsNowSelected() { return this->isNowSelected; }

	friend class Deck;

	virtual void OnClick(EventData& eventData) override;
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
};


