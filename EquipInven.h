#pragma once
#include "GameObject.h"


enum class EQUIP_TYPE;
enum class EQUIP_CLASS;
class Equipment;
class EquipInven : public GameObject
{
private:
	vector<Equipment*> vEquips;
	map<EQUIP_TYPE, vector<Equipment*>> mEquipListByType;
	map<EQUIP_CLASS, vector<Equipment*>> mEquipListByClass;

	vector<Equipment*> vDeactiveEquips;
	vector<Equipment*> vActiveEquips;
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	Equipment* GetRandomEquip();
	Equipment* GetSpecificEquip(string id, string name, int rank, int index, int type);

	virtual ~EquipInven() {};

private:
	Equipment* CreateEquip(string equipKey);
	void LoadEquipData();	
};

