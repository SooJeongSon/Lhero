#pragma once
#include "GameObject.h"

enum class EQUIP_TYPE
{
	AMULETS,	//목걸이
	GRIMOIRES,	//마법서
	HELMETS,
	ARMORS,
	BELTS,
	RINGS,
	GLOVES,
	BOOTS,
	SHIELDS,
	WEAPONS,
	NONE
};

enum class EQUIP_RARE
{
	NORMAL,
	RARE,
	EPIC,
	LEGENDARY,
	NONE
};

enum class EQUIP_CLASS
{
	WARRIOR,
	ROGUE,
	NECROMANCER,
	NONE
};

enum class EQUIP_ABLITY
{
	DMG,			//공격력
	DEF,			//방어력
	MAX_HP,			//최대체력
	VAMP,			//흡혈(%)
	COUNTER,		//반격
	SPLASH_DMG,		//전체에게 공격
	EVASION,		//회피
	ATK_SPEED,		//공격속도
	SKEL_QUILITY,	//해골 품질
	SKEL_POWER		//해골 파워
};

class Image;
class EquipInven;
class EQUIP;
class Equipment : public GameObject 
{
private:
	Image* lpEquipIcon;
	Image* lpEquipRare;
	string id;
	string name;
	string desc;
	EQUIP_TYPE type;
	EQUIP_RARE rare; 
	vector<string> ability;
	string itemKey;
	EQUIP* lpEquip;
	map<string, float> mAbilValues;

	RECT rc;
	int width;
	int height;

	int x;		//장비 타입
	int rank;	//장비 랭크
	int max;	//장비 타입별 최대 종류 


private:
	Equipment(const Equipment& other) = default;
	Equipment() {};

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline int GetWidth() { return this->width; }
	string GetEquipId() { return this->id; }
	int GetEquipType() { return this->x; }
	int GetEquipRank() { return this->rank; }
	int GetEquipIndex() { return this->max; }
	string GetEquipName() { return this->name; }
	void SetEquipImage(string id, int index, int type, int rank);
	virtual map<string, float> GetAbilityValue() { return this->mAbilValues; }

	friend class EquipInven;

	virtual void OnClick(EventData& eventData) override;
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
};

