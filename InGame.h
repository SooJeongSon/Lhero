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

	//��� �κ�, ����â
	GameUI* lpRightMenu;
	//����
	GameUI* lpHandCards;
	//���� ���
	GameUI* lpItemSlot;
	//Ÿ��
	FieldTileMap* lpFieldTiles;
	//�̺�Ʈ
	EventSystem* lpEventSystem; 
	//Ÿ�̸�
	InGameEventTimer* lpEventTimer;
	//��Ʋ����
	InGameBattleUnit* lpBattleUnit;
	//��Ʈ UI
	GameUI* rootUI;
	//��Ʈ Object
	GameObject* rootObject;

	EventData* data; 
	char szText[128];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

};

