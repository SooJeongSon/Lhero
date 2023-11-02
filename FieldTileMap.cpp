#include "FieldTileMap.h"
#include "TileTable.h"
#include "Image.h"
#include <cctype>
#include "Card.h"
#include "UISprite.h"
#include "InGameHandCard.h"
#include "Hero.h"
#include "Breed.h"
#include "Mob.h"
#include "InGameBattle.h"
#include "BattleUnit.h"

HRESULT FieldTileMap::Init()
{
	lpTileTable = new TileTable();
	lpTileTable->Init();

	lpSelectedTile = nullptr;
	lpPossibleTile = ImageManager::GetInstance()->FindImage("POSSIBLE");

	lpPreHeroTile = nullptr;
	lpCurrHeroTile = nullptr;
	lpNextHeroTile = nullptr;

	for (int y = 0; y < FIELD_TILE_Y; ++y)
	{
		for (int x = 0; x < FIELD_TILE_X; ++x)
		{
			tiles[y][x].x = x;
			tiles[y][x].y = y;
			SetRect(&tiles[y][x].rc, FIELD_START_X + x * FIELD_TILE_SIZE, FIELD_START_Y + y * FIELD_TILE_SIZE, FIELD_START_X + (x + 1) * FIELD_TILE_SIZE, FIELD_START_Y + (y + 1) * FIELD_TILE_SIZE);
			tiles[y][x].SetPos({ (float)(FIELD_START_X + x * FIELD_TILE_SIZE + FIELD_TILE_SIZE / 2), (float)(FIELD_START_Y + y * FIELD_TILE_SIZE + FIELD_TILE_SIZE / 2) });

			if (defaultMap[y][x] == 1)
			{				
				tiles[y][x].lpTile = lpTileTable->GetTile("road");
				tiles[y][x].vHistory.push_back("road");
				auto it = mBuildTiles.find("road");
				if (it == mBuildTiles.end())
				{
					mBuildTiles.insert(make_pair("road", vector<FieldTile*>()));
				}
				mBuildTiles["road"].push_back(&tiles[y][x]);
				IObserver* observer = &(tiles[y][x]);
				EventHandler::GetInstance()->AddObserver(observer);

				tiles[y][x].img = ImageManager::GetInstance()->FindImage("road");

				//타일 왼쪽, 위 확인하고 있으면 넥스트 타일로 나를 넣어준다.
				if (defaultMap[y][x - 1] == 1)
				{
					tiles[y][x - 1].vLpNextTiles.push_back(&tiles[y][x]);
					tiles[y][x].vLpNextTiles.push_back(&tiles[y][x - 1]);
				}
				if (defaultMap[y - 1][x] == 1)
				{
					tiles[y - 1][x].vLpNextTiles.push_back(&tiles[y][x]);
					tiles[y][x].vLpNextTiles.push_back(&tiles[y - 1][x]);
				}
			}
			else
			{
				tiles[y][x].lpTile = nullptr;
				tiles[y][x].frameX = 0;
				tiles[y][x].frameY = 0;
				tiles[y][x].eventCount = 0;
				tiles[y][x].img = ImageManager::GetInstance()->FindImage("NONETILE");
				isPossibleBuild[y][x] = false;
			}
		}
	}
	//타일 프레임 계산
	for (int y = 0; y < FIELD_TILE_Y; ++y)
	{
		for (int x = 0; x < FIELD_TILE_X; ++x)
		{
			tiles[y][x].tileFrame = CalculateTileFrame(x, y);
		}
	}
	//야영지
	tiles[2][9].lpTile = lpTileTable->GetTile("campsite");
	tiles[2][9].vHistory.push_back("campsite");
	auto it = mBuildTiles.find("campsite");
	if (it == mBuildTiles.end())
	{
		mBuildTiles.insert(make_pair("campsite", vector<FieldTile*>()));
	}
	mBuildTiles["campsite"].push_back(&tiles[2][9]);
	lpCurrHeroTile = &tiles[2][9];
	tiles[2][9].img = ImageManager::GetInstance()->FindImage("campsite");
	tiles[2][9].tileFrame = 0;

	SetRect(&rc, FIELD_START_X, FIELD_START_Y, FIELD_START_X + FIELD_TILE_SIZE * FIELD_TILE_X, FIELD_START_Y + FIELD_TILE_SIZE * FIELD_TILE_Y);

	width = 1050;
	height = 600;
	isCanCatchEvent = true;
	isVisible = true;

	return S_OK;
}

void FieldTileMap::Release()
{
	if (lpTileTable)
	{
		lpTileTable->Release();
		delete lpTileTable;
		lpTileTable = nullptr;
	}

	if (lpIconHero)
	{
		SAFE_RELEASE(lpIconHero);
	}

	if (lpBattleWindow)
	{
		SAFE_RELEASE(lpBattleWindow);
	}
}

void FieldTileMap::Update(float deltaTime)
{
	//히어로 부분
	if (KeyManager::GetInstance()->IsOnceKeyDown('H'))
	{
		lpIconHero = new Hero();
		lpIconHero->Init();
		//그 당시의 마우스 위치를 구해서
		POINTFLOAT pos = { (float)g_ptMouse.x, (float)g_ptMouse.y };
		int x = ((int)pos.x - FIELD_START_X) / FIELD_TILE_SIZE;
		int y = ((int)pos.y - FIELD_START_Y) / FIELD_TILE_SIZE;
		//해당되는 타일 위치를 구한뒤
		pos = tiles[2][9].GetPos();
		//타일의 중점으로 셋포스를 해준다
		lpIconHero->SetPos(pos);
		GameData::GetInstance()->SetHeroMaxHp(lpIconHero->GetMaxHp());
		GameData::GetInstance()->SetHeroStatMap();
		EventHandler::GetInstance()->SetIsHeroExist(true);
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RETURN))
	{
		lpNextHeroTile = lpCurrHeroTile->GetNextTile(lpPreHeroTile);
	}

	if (lpIconHero)
	{
		Hero* lpHero = (Hero*)lpIconHero;
		if (lpHero->GetState() == HERO_STATE::LOOP)
		{
			//히어로가 위치한 타일 인덱스 찾기
			//황무지 진입시 타일에 있는 몹 검색
			POINTFLOAT pos = { (float)lpIconHero->GetPos().x, (float)lpIconHero->GetPos().y };
			int x = ((int)pos.x - FIELD_START_X) / FIELD_TILE_SIZE;
			int y = ((int)pos.y - FIELD_START_Y) / FIELD_TILE_SIZE;

			if (lpNextHeroTile)
			{
				POINTFLOAT targetPos = lpNextHeroTile->GetPos();
				float angle = atan2(targetPos.y - pos.y, targetPos.x - pos.x);
				lpIconHero->SetPos({ lpIconHero->GetPos().x + cos(angle)*lpIconHero->GetMoveSpeed() * deltaTime, lpIconHero->GetPos().y + sin(angle)*lpIconHero->GetMoveSpeed() * deltaTime });
				float distance = pow(targetPos.y - pos.y, 2) + pow(targetPos.x - pos.x, 2);

				if (distance < 16)
				{
					lpIconHero->SetPos(lpNextHeroTile->GetPos());
					lpPreHeroTile = lpCurrHeroTile;
					lpCurrHeroTile = lpNextHeroTile;
					lpNextHeroTile = lpCurrHeroTile->GetNextTile(lpPreHeroTile);

					if (!lpCurrHeroTile->vMobs.empty())
					{
						lpBattleWindow = GameUI::CreateUI<InGameBattle>();
						lpBattleWindow->Init(UI_ANCHOR::MIDDLE, { -100.0f, 0.0f }, 301 * 2, 257 * 2);
						lpBattleWindow->SetBattleHero(lpIconHero);
						lpBattleWindow->SetBattleMob(lpCurrHeroTile->vMobs);
						lpHero->SetState(HERO_STATE::BATTLE);		
					}
				}
			}
			lpIconHero->Update(deltaTime);
		}
		GameData::GetInstance()->SetHeroHp(lpIconHero->GetHp());
	}

	for (int y = 0; y < FIELD_TILE_Y; ++y)
	{
		for (int x = 0; x < FIELD_TILE_X; ++x)
		{
			tiles[y][x].Update(deltaTime);
		}
	}

	if (lpIconHero)
	{
		Hero* lpHero = (Hero*)lpIconHero;
		if (lpHero->GetState() == HERO_STATE::BATTLE)
		{
			lpBattleWindow->Update(deltaTime);

			if (EventHandler::GetInstance()->GetIsBattleWin())
			{
				SAFE_RELEASE(lpBattleWindow);
				lpHero->SetState(HERO_STATE::LOOP);
				EventHandler::GetInstance()->SetIsBattleWin(false);
				for (int i = 0; i < lpCurrHeroTile->vMobs.size(); ++i)
				{
					SAFE_RELEASE(lpCurrHeroTile->vMobs[i]);
				}
				lpCurrHeroTile->vMobs.clear();
			}
			if (lpHero->GetHp() <= 0)
			{
				//게임오버
				SceneManager::GetInstance()->ChangeScene("TITLE");
			}
		}
	}
}

void FieldTileMap::Render(HDC hdc)
{
	if (isDebugMode)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}

	for (int y = 0; y < FIELD_TILE_Y; ++y)
	{
		for (int x = 0; x < FIELD_TILE_X; ++x)
		{
		
			if (isPossibleBuild[y][x])
			{
				if (isDebugMode)
				{
					TextOut(hdc, tiles[y][x].rc.left, tiles[y][x].rc.top + 30, "O", 1);
				}				
				lpPossibleTile->Render(hdc, tiles[y][x].rc.left, tiles[y][x].rc.top, false, true, RGB(0, 170, 255));
			}
			if (tiles[y][x].lpTile)
			{
				tiles[y][x].img->FrameRender(hdc, tiles[y][x].rc.left, tiles[y][x].rc.top - 18, 0, tiles[y][x].tileFrame, false, 1, true, RGB(0, 170, 255));
				//몹 그리기
				if (!tiles[y][x].vMobs.empty())
				{
					for (int i = 0; i < tiles[y][x].vMobs.size(); ++i)
					{
						tiles[y][x].vMobs[i]->Render(hdc);
					}
				}
			}
			if (isDebugMode)
			{
				Rectangle(hdc, tiles[y][x].rc.left, tiles[y][x].rc.top, tiles[y][x].rc.right, tiles[y][x].rc.bottom);
			}
			
		}
	}

	if (lpIconHero)
	{
		lpIconHero->Render(hdc);
	}
	if (lpBattleWindow)
	{
		lpBattleWindow->Render(hdc);
	}	
}

void FieldTileMap::SelectedTileValidation()
{
	map<FieldTile*, int> mCheckMap;
	if (lpSelectedTile->nearCondition != -1)
	{
		if (lpSelectedTile->nearCondition == 0)
		{
			// 텅빈상태
			for (int y = 0; y < FIELD_TILE_Y; ++y)
			{
				for (int x = 0; x < FIELD_TILE_X; ++x)
				{
					isPossibleBuild[y][x] = true;
				}
			}

			for (auto pair : mBuildTiles)
			{
				for (FieldTile* lpFieldTile : pair.second)
				{
					isPossibleBuild[lpFieldTile->y][lpFieldTile->x] = false;

					if (lpSelectedTile->checkTiles[2][1] && lpFieldTile->y - 1 > -1)
					{
						isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x] = false;
					}
					if (lpSelectedTile->checkTiles[1][2] && lpFieldTile->x - 1 > -1)
					{
						isPossibleBuild[lpFieldTile->y][lpFieldTile->x - 1] = false;
					}
					if (lpSelectedTile->checkTiles[0][1] && lpFieldTile->y + 1 < FIELD_TILE_Y)
					{
						isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x] = false;
					}
					if (lpSelectedTile->checkTiles[1][0] && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						isPossibleBuild[lpFieldTile->y][lpFieldTile->x + 1] = false;
					}

					// 대각선
					if (lpSelectedTile->checkTiles[0][0] && lpFieldTile->y - 1 > -1 && lpFieldTile->x - 1 > -1)
					{
						isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x - 1] = false;
					}
					if (lpSelectedTile->checkTiles[2][2] && lpFieldTile->y + 1 < FIELD_TILE_Y && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x + 1] = false;
					}
					if (lpSelectedTile->checkTiles[0][2] && lpFieldTile->y - 1 > -1 && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x + 1] = false;
					}
					if (lpSelectedTile->checkTiles[2][0] && lpFieldTile->y + 1 < FIELD_TILE_Y && lpFieldTile->x - 1 > -1)
					{
						isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x - 1] = false;
					}
				}
			}
		}
		else if (lpSelectedTile->nearCondition == 99)
		{
			// 마지막 타일 인접 && 시작과 끝이 존재하거나 하나도 없을때
			// 무조건 단 하나의 노드만 확인
			if (mBuildTiles.find(lpSelectedTile->vNearTiles[0]) == mBuildTiles.end())
			{
				// 지어진 타일이 없음
				// 어디든 지어도 됨
				for (int y = 0; y < FIELD_TILE_Y; ++y)
				{
					for (int x = 0; x < FIELD_TILE_X; ++x)
					{
						isPossibleBuild[y][x] = (tiles[y][x].lpTile == nullptr);
					}
				}
			}
			else
			{
				// 지어진 타일이 있음
				for (int y = 0; y < FIELD_TILE_Y; ++y)
				{
					for (int x = 0; x < FIELD_TILE_X; ++x)
					{
						isPossibleBuild[y][x] = false;
					}
				}

				FieldTile* lpFieldTile = mBuildTiles[lpSelectedTile->vNearTiles[0]].back();
				if (lpSelectedTile->checkTiles[2][1] && lpFieldTile->y - 1 > -1)
				{
					isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x] = true;
					// 상하좌우 확인해서 만약 시작과 끝점이 아닌 같은 타일이 만나면 그건 절대 안됨
					if (lpFieldTile->y - 2 > -1)
					{
						if (tiles[lpFieldTile->y - 2][lpFieldTile->x].lpTile == lpSelectedTile && &tiles[lpFieldTile->y - 2][lpFieldTile->x] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y - 2][lpFieldTile->x] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x] = false;
						}
					}
					if (lpFieldTile->x - 1 > -1)
					{
						if (tiles[lpFieldTile->y - 1][lpFieldTile->x - 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y - 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y - 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x] = false;
						}
					}
					if (lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						if (tiles[lpFieldTile->y - 1][lpFieldTile->x + 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y - 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y - 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y - 1][lpFieldTile->x] = false;
						}
					}
				}
				if (lpSelectedTile->checkTiles[1][2] && lpFieldTile->x - 1 > -1)
				{
					isPossibleBuild[lpFieldTile->y][lpFieldTile->x - 1] = true;
					if (lpFieldTile->y - 1 > -1)
					{
						if (tiles[lpFieldTile->y - 1][lpFieldTile->x - 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y - 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y - 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x - 1] = false;
						}
					}
					if (lpFieldTile->y + 1 < FIELD_TILE_Y)
					{
						if (tiles[lpFieldTile->y + 1][lpFieldTile->x - 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y + 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y + 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x - 1] = false;
						}
					}
					if (lpFieldTile->x - 2 > -1)
					{
						if (tiles[lpFieldTile->y][lpFieldTile->x - 2].lpTile == lpSelectedTile && &tiles[lpFieldTile->y][lpFieldTile->x - 2] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y][lpFieldTile->x - 2] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x - 1] = false;
						}
					}
				}
				if (lpSelectedTile->checkTiles[0][1] && lpFieldTile->y + 1 < FIELD_TILE_Y)
				{
					isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x] = true;
					if (lpFieldTile->y + 2 < FIELD_TILE_Y)
					{
						if (tiles[lpFieldTile->y + 2][lpFieldTile->x].lpTile == lpSelectedTile && &tiles[lpFieldTile->y + 2][lpFieldTile->x] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y + 2][lpFieldTile->x] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x] = false;
						}
					}
					if (lpFieldTile->x - 1 > -1)
					{
						if (tiles[lpFieldTile->y + 1][lpFieldTile->x - 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y + 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y + 1][lpFieldTile->x - 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x] = false;
						}
					}
					if (lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						if (tiles[lpFieldTile->y + 1][lpFieldTile->x + 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y + 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y + 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y + 1][lpFieldTile->x] = false;
						}
					}
				}
				if (lpSelectedTile->checkTiles[1][0] && lpFieldTile->x + 1 < FIELD_TILE_X)
				{
					isPossibleBuild[lpFieldTile->y][lpFieldTile->x + 1] = true;
					if (lpFieldTile->y - 1 > -1)
					{
						if (tiles[lpFieldTile->y - 1][lpFieldTile->x + 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y - 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y - 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x + 1] = false;
						}
					}
					if (lpFieldTile->y + 1 < FIELD_TILE_Y)
					{
						if (tiles[lpFieldTile->y + 1][lpFieldTile->x + 1].lpTile == lpSelectedTile && &tiles[lpFieldTile->y + 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y + 1][lpFieldTile->x + 1] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x + 1] = false;
						}
					}
					if (lpFieldTile->x + 2 < FIELD_TILE_X)
					{
						if (tiles[lpFieldTile->y][lpFieldTile->x + 2].lpTile == lpSelectedTile && &tiles[lpFieldTile->y][lpFieldTile->x + 2] != mBuildTiles[lpSelectedTile->vNearTiles[0]].back()
							&& &tiles[lpFieldTile->y][lpFieldTile->x + 2] != mBuildTiles[lpSelectedTile->vNearTiles[0]].front())
						{
							isPossibleBuild[lpFieldTile->y][lpFieldTile->x + 1] = false;
						}
					}
				}

			}
		}
		else
		{
			// 텅비지 않은 상태
			for (int y = 0; y < FIELD_TILE_Y; ++y)
			{
				for (int x = 0; x < FIELD_TILE_X; ++x)
				{
					isPossibleBuild[y][x] = false;
				}
			}

			for (string tileKey : lpSelectedTile->vNearTiles)
			{
				if (mBuildTiles.find(tileKey) == mBuildTiles.end()) continue;

				for (FieldTile* lpFieldTile : mBuildTiles[tileKey])
				{
					//상하좌우
					if (lpSelectedTile->checkTiles[2][1] && lpFieldTile->y - 1 > -1)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y - 1][lpFieldTile->x]);
						if (!tiles[lpFieldTile->y - 1][lpFieldTile->x].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y - 1][lpFieldTile->x], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[1][2] && lpFieldTile->x - 1 > -1)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y][lpFieldTile->x - 1]);
						if (!tiles[lpFieldTile->y][lpFieldTile->x - 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y][lpFieldTile->x - 1], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[0][1] && lpFieldTile->y + 1 < FIELD_TILE_Y)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y + 1][lpFieldTile->x]);
						if (!tiles[lpFieldTile->y + 1][lpFieldTile->x].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y + 1][lpFieldTile->x], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[1][0] && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y][lpFieldTile->x + 1]);
						if (!tiles[lpFieldTile->y][lpFieldTile->x + 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y][lpFieldTile->x + 1], 1));
							else ++(it->second);
						}
					}

					//대각선
					if (lpSelectedTile->checkTiles[0][0] && lpFieldTile->y - 1 > -1 && lpFieldTile->x - 1 > -1)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y - 1][lpFieldTile->x - 1]);
						if (!tiles[lpFieldTile->y - 1][lpFieldTile->x - 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y - 1][lpFieldTile->x - 1], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[2][2] && lpFieldTile->y + 1 < FIELD_TILE_Y && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y + 1][lpFieldTile->x + 1]);
						if (!tiles[lpFieldTile->y + 1][lpFieldTile->x + 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y + 1][lpFieldTile->x + 1], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[0][2] && lpFieldTile->y - 1 > -1 && lpFieldTile->x + 1 < FIELD_TILE_X)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y - 1][lpFieldTile->x + 1]);
						if (!tiles[lpFieldTile->y - 1][lpFieldTile->x + 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y - 1][lpFieldTile->x + 1], 1));
							else ++(it->second);
						}
					}
					if (lpSelectedTile->checkTiles[2][0] && lpFieldTile->y + 1 < FIELD_TILE_Y && lpFieldTile->x - 1 > -1)
					{
						auto it = mCheckMap.find(&tiles[lpFieldTile->y + 1][lpFieldTile->x - 1]);
						if (!tiles[lpFieldTile->y + 1][lpFieldTile->x - 1].lpTile)
						{
							if (it == mCheckMap.end()) mCheckMap.insert(make_pair(&tiles[lpFieldTile->y + 1][lpFieldTile->x - 1], 1));
							else ++(it->second);
						}
					}
				}
			}

			switch (lpSelectedTile->nearCondition)
			{
			case 1:
				for (auto pair : mCheckMap)
				{
					if (pair.second > 0)
					{
						isPossibleBuild[pair.first->y][pair.first->x] = true;
					}
				}
				break;
			case 2:
				for (auto pair : mCheckMap)
				{
					// 틀림
					if (pair.second == lpSelectedTile->vNearTiles.size())
					{
						isPossibleBuild[pair.first->y][pair.first->x] = true;
					}
				}
				break;
			case 3:
				for (auto pair : mCheckMap)
				{
					if (pair.second > 0)
					{
						isPossibleBuild[pair.first->y][pair.first->x] = true;
					}
				}

				for (int y = 0; y < FIELD_TILE_Y; ++y)
				{
					for (int x = 0; x < FIELD_TILE_X; ++x)
					{
						isPossibleBuild[y][x] = !isPossibleBuild[y][x];
					}
				}
				break;
			}
		}

	}
	else
	{
		for (int y = 0; y < FIELD_TILE_Y; ++y)
		{
			for (int x = 0; x < FIELD_TILE_X; ++x)
			{
				isPossibleBuild[y][x] = true;
			}
		}
	}

	if (lpSelectedTile->selfCondition != -1)
	{
		// true인 애들의 확인
		for (int y = 0; y < FIELD_TILE_Y; ++y)
		{
			for (int x = 0; x < FIELD_TILE_X; ++x)
			{
				if (isPossibleBuild[y][x])
				{
					switch (lpSelectedTile->selfCondition)
					{
					case 0:
						isPossibleBuild[y][x] = (tiles[y][x].lpTile == nullptr);
						break;
					case 1:
						if (!tiles[y][x].lpTile)
						{
							isPossibleBuild[y][x] = false;
						}
						else
						{
							isPossibleBuild[y][x] = false;
							for (string tileKey : lpSelectedTile->vSelfTiles)
							{
								if (tiles[y][x].lpTile->id == tileKey)
								{
									isPossibleBuild[y][x] = true;
									break;
								}
							}
						}
						break;
					case 2:
						if (!tiles[y][x].lpTile || lpSelectedTile->vSelfTiles.size() > 1)
						{
							isPossibleBuild[y][x] = false;
						}
						else
						{
							isPossibleBuild[y][x] = false;
							for (string tileKey : lpSelectedTile->vSelfTiles)
							{
								if (tiles[y][x].lpTile->id == tileKey)
								{
									isPossibleBuild[y][x] = true;
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}

int FieldTileMap::CalculateTileFrame(int x, int y)
{
	if (tiles[y][x].lpTile)
	{
		//left right
		if (tiles[y][x - 1].lpTile && tiles[y][x + 1].lpTile)
		{
			return 1;
		}
		//up down
		if (tiles[y - 1][x].lpTile && tiles[y + 1][x].lpTile)
		{
			return 2;
		}
		//right down
		if (tiles[y][x + 1].lpTile && tiles[y + 1][x].lpTile)
		{
			return 3;
		}
		if (tiles[y][x - 1].lpTile && tiles[y + 1][x].lpTile)
		{
			return 4;
		}
		if (tiles[y - 1][x].lpTile && tiles[y][x + 1].lpTile)
		{
			return 5;
		}
		if (tiles[y - 1][x].lpTile && tiles[y][x - 1].lpTile)
		{
			return 6;
		}
	}
	return 0;
}

void FieldTileMap::OnClick(EventData& eventData)
{
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - FIELD_START_X) / FIELD_TILE_SIZE;
	int y = (mPoint.y - FIELD_START_Y) / FIELD_TILE_SIZE;

	if (typeid(*(eventData.lpLastTarget)) != typeid(*this))
	{
		return;
	}		
}

void FieldTileMap::OnDrag(EventData& eventData)
{	
}

void FieldTileMap::Drop(EventData& eventData)
{
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - FIELD_START_X) / FIELD_TILE_SIZE;
	int y = (mPoint.y - FIELD_START_Y) / FIELD_TILE_SIZE;
	//카드
	if (typeid(*eventData.lpDragTarget) == typeid(UISprite))
	{
		UISprite* lpTarget = (UISprite*)eventData.lpDragTarget;
		if (typeid(*(lpTarget->GetObjectPointer())) == typeid(Card))
		{
			Card* lpCard = (Card*)lpTarget->GetObjectPointer();
			lpSelectedTile = lpTileTable->GetTile(lpCard->GetCardKey());
			if (isPossibleBuild[y][x])
			{				
				tiles[y][x].lpTile = lpSelectedTile;
				tiles[y][x].vHistory.push_back(lpSelectedTile->id);
				auto it = mBuildTiles.find(lpSelectedTile->id);
				if (it == mBuildTiles.end())
				{
					mBuildTiles.insert(make_pair(lpSelectedTile->id, vector<FieldTile*>()));
				}
				mBuildTiles[lpSelectedTile->id].push_back(&tiles[y][x]);
				tiles[y][x].img = ImageManager::GetInstance()->FindImage(lpCard->GetCardKey());
				lpSelectedTile = nullptr;

				//옵저버 설치
				IObserver* observer = &(tiles[y][x]);
				EventHandler::GetInstance()->AddObserver(observer);

				//가능지역 초기화
				for (int y = 0; y < FIELD_TILE_Y; ++y)
				{
					for (int x = 0; x < FIELD_TILE_X; ++x)
					{
						isPossibleBuild[y][x] = 0;
					}
				}	
				InGameHandCard* lpHandCard = (InGameHandCard*)eventData.lpLastTarget;
				lpHandCard->UseCard(lpTarget);
			}
		}
	}
}

void FieldTileMap::EndDrag(EventData& eventData)
{
}

void FieldTileMap::BeginDrag(EventData& eventData)
{
}

void FieldTileMap::MouseEnter(EventData& eventData)
{
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - FIELD_START_X) / FIELD_TILE_SIZE;
	int y = (mPoint.y - FIELD_START_Y) / FIELD_TILE_SIZE;

	if (eventData.isDragging)
	{
		if (typeid(*eventData.lpDragTarget) == typeid(InGameHandCard))
		{
			InGameHandCard* lpTarget = (InGameHandCard*)eventData.lpDragTarget;
			if (lpTarget->GetSelectedCard() != nullptr && 
				typeid(*(lpTarget->GetSelectedCard())) == typeid(UISprite))
			{
				UISprite* lpSprite = (UISprite*)lpTarget->GetSelectedCard();
				if (typeid(*(lpSprite->GetObjectPointer())) == typeid(Card))
				{
					Card* lpCard = (Card*)lpSprite->GetObjectPointer();
					lpSelectedTile = lpTileTable->GetTile(lpCard->GetCardKey());
					SelectedTileValidation();
				}					
			}			
		}		
	}
}

void FieldTileMap::MouseOver(EventData& eventData)
{
	POINT mPoint = g_ptMouse;
	int x = (mPoint.x - FIELD_START_X) / FIELD_TILE_SIZE;
	int y = (mPoint.y - FIELD_START_Y) / FIELD_TILE_SIZE;

	if (tiles[y][x].lpTile)
	{
		//필요 정보를 넘겨준다, 알림을 보낸다 (핸들러의 변수를 변경)
		EventHandler::GetInstance()->SetTextData(tiles[y][x].lpTile->id, tiles[y][x].lpTile->desc);
		EventHandler::GetInstance()->SetIsMouseOver(true);
	}
	else
	{
		EventHandler::GetInstance()->SetTextData("","");
		EventHandler::GetInstance()->SetIsMouseOver(false);
	}
}

void FieldTileMap::MouseOut(EventData& eventData)
{
	for (int y = 0; y < FIELD_TILE_Y; ++y)
	{
		for (int x = 0; x < FIELD_TILE_X; ++x)
		{
			isPossibleBuild[y][x] = 0;
		}
	}
}

void FieldTile::GenerateMob()
{
	if (lpTile->spawn == "slime")
	{
		Breed breed = Breed("slime");
		vMobs.push_back(breed.CreateMob(10.0f));
	}

	if (lpTile->spawn == "ratwolf")
	{
		Breed breed = Breed("ratwolf");
		vMobs.push_back(breed.CreateMob(15.0f));
	}

	if (lpTile->spawn == "skel")
	{
		Breed breed = Breed("skel");
		vMobs.push_back(breed.CreateMob(20.0f));
	}

	if (lpTile->spawn == "mosquito")
	{
		Breed breed = Breed("mosquito");
		vMobs.push_back(breed.CreateMob(10.0f));
	}
}

void FieldTile::Update(float deltaTime)
{
	if (!vMobs.empty())
	{
		for (int i = 0; i < vMobs.size(); ++i)
		{
			vMobs[i]->Update(deltaTime);
			vMobs[i]->SetPos({(float)this->rc.left + 5 + 5*(i%4), (float)this->rc.top + 5 + 5*(i%4)});
		}
		//몹 최대개수
		if (vMobs.size() > 5)
		{
			vMobs.erase(vMobs.begin());
		}
	}
}

void FieldTile::OnClick(EventData& eventData)
{
}

void FieldTile::OnDrag(EventData& eventData)
{
}

void FieldTile::Drop(EventData& eventData)
{
}

void FieldTile::EndDrag(EventData& eventData)
{
}

void FieldTile::BeginDrag(EventData& eventData)
{
}

void FieldTile::MouseEnter(EventData& eventData)
{
}

void FieldTile::MouseOver(EventData& eventData)
{
}

void FieldTile::MouseOut(EventData& eventData)
{
}

FieldTile* FieldTile::GetNextTile(FieldTile* preFieldTile)
{
	FieldTile* lpNextTile = nullptr;

	for (int i = 0; i < vLpNextTiles.size(); ++i)
	{
		if (vLpNextTiles[i] == preFieldTile)
		{
			continue;
		}
		lpNextTile = vLpNextTiles[i];
		break;
	}
	return lpNextTile;
}
