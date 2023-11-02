#pragma once
#include "GameScene.h"

class Image;
class FieldTileMap;
class TileTable; 
class GameUI;
class GameObject;
class EventSystem;
class InGameEventTimer;
class InGameBattle;
class InGameBattleUnit;
struct EventData;
class InGame : public GameScene
{
private:
	Image* lpBackground;
	Image* lpBackBuffer;

	//장비 인벤, 설명창
	GameUI* lpRightMenu;
	//손패
	GameUI* lpHandCards;
	//장착 장비
	GameUI* lpItemSlot;
	//타일
	FieldTileMap* lpFieldTiles;
	//이벤트
	EventSystem* lpEventSystem; 
	//타이머
	InGameEventTimer* lpEventTimer;
	//배틀유닛
	InGameBattleUnit* lpBattleUnit;
	//루트 UI
	GameUI* rootUI;
	//루트 Object
	GameObject* rootObject;

	EventData* data; 
	char szText[128];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

};

