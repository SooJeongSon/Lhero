#pragma once
#include "GameObject.h"
#include "IObserver.h"

#define FIELD_START_X 0
#define FIELD_START_Y 54

#define FIELD_TILE_X 21
#define FIELD_TILE_Y 12

#define FIELD_TILE_SIZE 50

class Mob;
class Image; 
class Tile;
class FieldTile : public IObserver, public GameObject
{
public:
	int x;
	int y;
	RECT rc;

	Tile* lpTile;
	vector<FieldTile*> vLpNextTiles;
	int frameX;
	int frameY;
	int eventCount;

	int tileFrame = 0;

	vector<string> vHistory;
	Image* img;
	bool isVisited;
	vector<Mob*> vMobs;

public:
	void GenerateMob();
	virtual void onNotify(EVENT_KEY eventKey)
	{
		switch (eventKey)	
		{
		case EVENT_KEY::SPAWN:
			if (rand() % 20 == 1)
			{
				FieldTile::GenerateMob();
			}			
			break;
		case EVENT_KEY::NONE:
			break;
		default:
			break;
		}
	}
	virtual void Update(float deltaTime);
	virtual void OnClick(EventData& eventData);
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
	virtual RECT* GetRectPointer() { return &rc; }
	virtual FieldTile* GetNextTile(FieldTile* preFieldTile);
};

class EventData;
class TileTable;
class Image;
class Unit;
class InGameBattle;
class FieldTileMap : public GameObject
{
private:
	FieldTile tiles[FIELD_TILE_Y][FIELD_TILE_X];
	map<string, vector<FieldTile*>> mBuildTiles;
	Tile* lpSelectedTile;
	bool isPossibleBuild[FIELD_TILE_Y][FIELD_TILE_X];
	TileTable* lpTileTable;
	Image* lpPossibleTile;
	int defaultMap[FIELD_TILE_Y][FIELD_TILE_X] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
													{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
													{0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0},
													{0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

	Unit* lpIconHero;
	InGameBattle* lpBattleWindow;
	FieldTile* lpPreHeroTile;
	FieldTile* lpCurrHeroTile;
	FieldTile* lpNextHeroTile;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc) override;

	void SelectedTileValidation();

	inline void SetTile(int x, int y, Tile* lpTile) { tiles[y][x].lpTile = lpTile; }
	inline IObserver* GetTile(int x, int y) { return &(tiles[y][x]); }
	int CalculateTileFrame(int x, int y);

	virtual void OnClick(EventData& eventData);
	virtual void OnDrag(EventData& eventData);
	virtual void Drop(EventData& eventData);
	virtual void EndDrag(EventData& eventData);
	virtual void BeginDrag(EventData& eventData);
	virtual void MouseEnter(EventData& eventData);
	virtual void MouseOver(EventData& eventData);
	virtual void MouseOut(EventData& eventData);
};