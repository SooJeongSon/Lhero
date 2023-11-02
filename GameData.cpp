#include "GameData.h"
#include "Deck.h"
#include "EquipInven.h"
#include "CommonFunction.h"

HRESULT GameData::Init()
{
    lpDeck = new Deck();
    lpDeck->Init();

    lpEquipInven = new EquipInven();
    lpEquipInven->Init();

    isCardUsed = false;
    isEquiped = false;

    return S_OK;
}

Card* GameData::PickCard()
{
    return lpDeck->GetRandomCard();
}

Equipment* GameData::PickEquip()
{
    return lpEquipInven->GetRandomEquip();
}

Equipment* GameData::PickEquip(string id, string name, int rank, int index, int type)
{
    return lpEquipInven->GetSpecificEquip(id, name, rank, index, type);
}

void GameData::SetHeroStatMap()
{
    mHeroStats.insert(make_pair("공격력", heroData.attackDmg));
    mHeroStats.insert(make_pair("최대체력", heroData.maxHp));
    mHeroStats.insert(make_pair("방어력", heroData.defenseValue));
    mHeroStats.insert(make_pair("흡혈", heroData.vampValue));
    mHeroStats.insert(make_pair("공격속도", heroData.attackSpeed));
    mHeroStats.insert(make_pair("회피", heroData.evasion));
    mHeroStats.insert(make_pair("반격", heroData.conterValue));
}

void GameData::SetBaseStat(float maxHp, float attackDmg, float defenseValue, float vampValue, float conterValue, float splashDmg, float evasion, float attackSpeed, float moveSpeed)
{
    this->heroData.baseMaxHp = maxHp;
    this->heroData.baseAttackDmg = attackDmg;
    this->heroData.baseDefenseValue = defenseValue;
    this->heroData.baseVampValue = vampValue;
    this->heroData.baseConterValue = conterValue;
    this->heroData.baseSplashDmg = splashDmg;
    this->heroData.baseEvasion = evasion;
    this->heroData.baseAttackSpeed = attackSpeed;
    this->heroData.baseMoveSpeed = moveSpeed;
}

void GameData::SetStatFirstTime(float maxHp, float attackDmg, float defenseValue, float vampValue, float conterValue, float splashDmg, float evasion, float attackSpeed, float moveSpeed)
{
    this->heroData.maxHp = maxHp;
    this->heroData.attackDmg = attackDmg;
    this->heroData.defenseValue = defenseValue;
    this->heroData.vampValue = vampValue;
    this->heroData.conterValue = conterValue;
    this->heroData.splashDmg = splashDmg;
    this->heroData.evasion = evasion;
    this->heroData.attackSpeed = attackSpeed;
    this->heroData.moveSpeed = moveSpeed;
}

void GameData::SetAttackDmg(float attackDmg)
{
    this->heroData.attackDmg = this->heroData.baseAttackDmg + attackDmg;
    mHeroStats["공격력"] = this->heroData.attackDmg;
}

void EquipTable::Init()
{
    LoadEquipData();
}

void EquipTable::Release()
{
    for (auto p : mLpEquips)
    {
        delete p.second;
    }
    mLpEquips.clear();
}

void EquipTable::Update()
{
}

void EquipTable::Render(HDC hdc)
{
}

void EquipTable::LoadEquipData()
{
    FileManager::GetInstance()->LoadIniFile("Text/equip_data.ini", "equip_data");

    map<string, map<string, string>> mDatas = FileManager::GetInstance()->GetData("equip_data");
    vector<string> vEquipData;

    for (auto group : mDatas)
    {
        mLpEquips.insert(make_pair(group.first, new EQUIP()));
        mLpEquips[group.first]->id = group.first;
        mLpEquips[group.first]->ability = mDatas[group.first]["ability"];
        mLpEquips[group.first]->bonus_ability = StringSplit(mDatas[group.first]["bonus_ability"],',');
        mLpEquips[group.first]->job = mDatas[group.first]["class"];
        mLpEquips[group.first]->name = StringSplit(mDatas[group.first]["name"],',');
    }
}
