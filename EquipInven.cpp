#include "EquipInven.h"
#include "Equipment.h"
#include "CommonFunction.h"

HRESULT EquipInven::Init()
{
	mEquipListByClass.insert(make_pair(EQUIP_CLASS::WARRIOR, vector<Equipment*>()));
	mEquipListByClass.insert(make_pair(EQUIP_CLASS::NECROMANCER, vector<Equipment*>()));
	mEquipListByClass.insert(make_pair(EQUIP_CLASS::ROGUE, vector<Equipment*>()));
	
	LoadEquipData();
	return S_OK;
}

void EquipInven::Release()
{
	for (int i = 0; i < vEquips.size(); ++i)
	{
		vEquips[i]->Release();
		delete vEquips[i];
		vEquips[i] = nullptr;
	}
	vEquips.clear();
}

void EquipInven::Update(float deltaTime)
{
	for (int i = 0; i < vEquips.size(); ++i)
	{
		vEquips[i]->Update(deltaTime);
	}
	
}

void EquipInven::Render(HDC hdc)
{
	for (int i = 0; i < vEquips.size(); ++i)
	{
		vEquips[i]->Render(hdc);
	}
}

Equipment* EquipInven::GetRandomEquip()
{
	EQUIP_CLASS job = EQUIP_CLASS::WARRIOR;
	vector<Equipment*> vEquips = mEquipListByClass[job];
	if (!vEquips.empty())
	{
		Equipment* randEquip = vEquips[rand() % vEquips.size()];
		Equipment* lpEquip = nullptr;
		if (vDeactiveEquips.empty())
		{
			lpEquip = new Equipment(*randEquip);
			lpEquip->max = rand()%(randEquip->max);
			lpEquip->x = (int)randEquip->type;
			lpEquip->rank = rand() % 4;
			lpEquip->lpEquip = EquipTable::GetInstance()->GetEquip(randEquip->GetEquipId());
			lpEquip->mAbilValues.insert(make_pair(lpEquip->lpEquip->ability, 1.0f));
			for (int i = 0; i<lpEquip->lpEquip->bonus_ability.size(); ++i)
			{
				lpEquip->mAbilValues.insert(make_pair(lpEquip->lpEquip->bonus_ability[i], 1.0f));
			}
		}
		else
		{
			lpEquip = vDeactiveEquips.back();
			vDeactiveEquips.pop_back();

			*lpEquip = *randEquip;
		}
		vActiveEquips.push_back(lpEquip);
		return lpEquip;
	}
	return nullptr;
}

Equipment* EquipInven::GetSpecificEquip(string id, string name, int rank, int index, int type)
{
	Equipment* lpEquip = new Equipment();
	lpEquip->Init();

	lpEquip->id = id;
	lpEquip->name = name;
	lpEquip->rank = rank;
	lpEquip->max = index;
	lpEquip->x = type; 
	lpEquip->lpEquip = EquipTable::GetInstance()->GetEquip(id);
	lpEquip->isVisible = true;

	return lpEquip;
}

Equipment* EquipInven::CreateEquip(string equipKey)
{
	Equipment* lpEquip = new Equipment();

	lpEquip->Init();
	lpEquip->id = equipKey;
	lpEquip->lpEquipIcon = ImageManager::GetInstance()->FindImage("equip");
	lpEquip->lpEquipRare = ImageManager::GetInstance()->FindImage("equip_rare");

	return lpEquip;
}

void EquipInven::LoadEquipData()
{
	FileManager::GetInstance()->LoadIniFile("Text/equip_data.ini", "equips");
	map<string, map<string, string>> mDatas = FileManager::GetInstance()->GetData("equips");

	vector<string> vEquipData;
	for (auto group : mDatas)
	{
		Equipment* lpEquip = CreateEquip(group.first);
		EQUIP_TYPE type = (EQUIP_TYPE)stoi(group.second["type"]);
		vector<string> ability = StringSplit(group.second["ability"], ',');
		EQUIP_CLASS job = (EQUIP_CLASS)stoi(group.second["class"]);		 

		lpEquip->id = group.second["itemKey"];
		lpEquip->type = type;
		lpEquip->max = stoi(group.second["max"]);
		
		vEquips.push_back(lpEquip);
		mEquipListByClass[job].push_back(lpEquip);
	}
	
}
