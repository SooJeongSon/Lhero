#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

enum class EVENT_KEY
{
	SPAWN,
	TEXTPRINT,
	EQUIPTEXTPRINT,
	CARDTEXTPRINT,
	UNITTEXTPRINT,
	NONE
};

struct tagGameData
{
	string selectedCard;
};

struct HeroData
{
	float maxHp;
	float hp;
	float attackDmg;
	float defenseValue;
	float vampValue;
	float conterValue;
	float splashDmg;
	float evasion;
	float attackSpeed;
	float moveSpeed;

	float baseMaxHp;
	float baseAttackDmg;
	float baseDefenseValue;
	float baseVampValue;
	float baseConterValue;
	float baseSplashDmg;
	float baseEvasion;
	float baseAttackSpeed;
	float baseMoveSpeed;
};

class Card;
class Deck;
class EquipInven;
class Equipment;
class GameData : public Singleton<GameData>
{
private:
	Deck* lpDeck;
	EquipInven* lpEquipInven;
	tagGameData gameData;
	string tileKey;
	bool isCardUsed;
	bool isEquiped;
	HeroData heroData;
	map<string, float> mHeroStats;

public:
	HRESULT Init();

	void Save() {}
	void Load() {}

	Card* PickCard();
	Equipment* PickEquip();
	Equipment* PickEquip(string id, string name, int rank, int index, int type);

	inline void SetSelectedCard(string key) { gameData.selectedCard = key; }
	inline string GetSelectedCard() { return gameData.selectedCard; }

	void SetTileKey(string key) { tileKey = key; }
	string GetTileKey() { return tileKey; }

	bool GetIsCardUsed() { return this->isCardUsed; } 
	void SetIsCardUsed(bool b) { this->isCardUsed = b; }

	bool GetIsEquiped() { return this->isEquiped; }
	void SetIsEquiped(bool b) { this->isEquiped = b; }

	void SetHeroHp(float heroHp) { heroData.hp = heroHp; }
	float GetHeroHp() { return heroData.hp; }

	void SetHeroMaxHp(float heroMaxHp) { heroData.maxHp = heroMaxHp; }
	float GetHeroMaxHp() { return heroData.maxHp; }

	void SetHeroStatMap();
	map<string, float> GetHeroStat() { return mHeroStats; }

	void SetBaseStat(float maxHp = 20.0f, float attackDmg = 0.1f, float defenseValue = 1.0f, float vampValue = 1.0f, float conterValue = 1.0f, float splashDmg = 1.0f, float evasion = 3.0f, float attackSpeed = 0.5f, float moveSpeed = 20.f);
	void SetStatFirstTime(float maxHp = 20.0f, float attackDmg = 0.1f, float defenseValue = 1.0f, float vampValue = 1.0f, float conterValue = 1.0f, float splashDmg = 1.0f, float evasion = 3.0f, float attackSpeed = 0.5f, float moveSpeed = 20.f);
	void SetAttackDmg(float attackDmg); 
	float GetAttackDmg() { return this->heroData.attackDmg; }
	
};

struct EQUIP
{
	string id;
	vector<string> name;
	string ability;
	vector<string> bonus_ability;
	string job;
	int rank;
};

class EquipTable : public Singleton<EquipTable> 
{
private:
	map<string, EQUIP*> mLpEquips;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline EQUIP* GetEquip(int index) { return (index < mLpEquips.size()) ? next(mLpEquips.begin(), index)->second : nullptr; }
	inline EQUIP* GetEquip(string key) { return (mLpEquips.find(key) != mLpEquips.end()) ? mLpEquips[key] : nullptr; }

private:
	void LoadEquipData();
};