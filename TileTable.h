//타일에 대한 정보를 담고 있는 곳

#pragma once
#include "GameObject.h"

class Image;
struct Tile
{
	string id;
	string name;
	string desc;
	string spawn;
	//타일 기능 설명 문구
	vector<string> vEtc;
	//설치할 수 있는지 정보
	bool checkTiles[3][3];
	//자기 타일 설치 조건
	int selfCondition;
	//주변 타일 설치 조건
	int nearCondition;
	//셀프타일이 될 수 있는 타일들의 키값을 모은 벡터
	vector<string> vSelfTiles;
	//주변타일이 될 수 있는 타일들의 키값을 모은 벡터
	vector<string> vNearTiles;
};

class TileTable
{
private:
	//타일과 키 값 연결
	map<string, Tile*> mLpTiles;
	//타일의 렉트들
	vector<RECT> vRects;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline vector<RECT> GetVRects() { return vRects; }
	inline vector<pair<string, Tile*>> GetVMapList() { vector<pair<string, Tile*>> vList(mLpTiles.begin(), mLpTiles.end()); return vList; }
	//인덱스 값으로 타일 겟하기, 인덱스에 대한 예외처리
	inline Tile* GetTile(int index) { return (index < mLpTiles.size()) ? next(mLpTiles.begin(), index)->second : nullptr; }
	//키 값으로 타일 겟하기, 키 값에 대한 예외처리
	inline Tile* GetTile(string key) { return (mLpTiles.find(key) != mLpTiles.end()) ? mLpTiles[key] : nullptr; }

private:
	void LoadTileData();
};

