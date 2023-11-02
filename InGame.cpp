#include "InGame.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Card.h"
#include "InGameUI.h"
#include "Deck.h"
#include "FieldTileMap.h"
#include "TileTable.h"
#include "GameUI.h"
#include "InGameEventTimer.h"
#include "InGameRightMenu.h"
#include "InGameHandCard.h"
#include "EventSystem.h"
#include "UIHorizontalScroll.h"
#include "InGameEventTimer.h"
#include "GameObject.h"
#include "UIProgressBar.h"
#include "InGameBattle.h"
#include "InGameBattleUnit.h"
#include "InGameItemSlot.h"

HRESULT InGame::Init()
{
	SetClientRect(g_hWnd, WINSIZE_WIDTH, WINSIZE_HEIGHT);
	//배경
	lpBackground = ImageManager::GetInstance()->FindImage("INGAMEBACKGROUND");
	lpBackBuffer = ImageManager::GetInstance()->FindImage("BACKBUFFER");
 
	//루트 UI
	rootUI = GameUI::CreateUI<GameUI>();
	rootUI->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 0.0f }, WINSIZE_WIDTH, WINSIZE_HEIGHT);
	rootUI->SetIsCanCatchEvent(false);
	EventSystem::GetInstance()->SetCurrUI(rootUI);

	//루트 Object
	rootObject = GameObject::CreateObject<GameObject>();
	rootObject->Init();
	rootObject->SetIsCanCatchEvent(false);
	EventSystem::GetInstance()->SetCurrObject(rootObject);

	//타일
	lpFieldTiles = GameObject::CreateObject<FieldTileMap>(rootObject);
	lpFieldTiles->Init();

	//장비 인벤, 설명창
	lpRightMenu = GameUI::CreateUI<InGameRightMenu>(rootUI);
	lpRightMenu->Init(UI_ANCHOR::RIGHT_TOP, { 0.0f, 0.0f }, 296, WINSIZE_HEIGHT);

	//손패
	lpHandCards = GameUI::CreateUI<InGameHandCard>(rootUI);
	lpHandCards->Init(UI_ANCHOR::LEFT_BOTTOM, { 0.0f, -48.0f }, WINSIZE_WIDTH - 296, 58 * 2);
	
	//장착 장비
	lpItemSlot = GameUI::CreateUI<InGameItemSlot>(rootUI);
	lpItemSlot->Init(UI_ANCHOR::RIGHT_TOP, { 10.0f, 26*2.0f }, 105 * 2, 78 * 2);
	
	//타이머
	lpEventTimer = GameUI::CreateUI<InGameEventTimer>(rootUI);
	lpEventTimer->Init(UI_ANCHOR::LEFT_TOP, { 0.0f, 0.0f }, 121*2, 27 * 2);

	//배틀 유닛
	lpBattleUnit = GameUI::CreateUI<InGameBattleUnit>(rootUI);
	lpBattleUnit->Init(UI_ANCHOR::MIDDLE, { -50.0f, 0.0f }, 60 * 2, 39 * 3);

	//루트 UI에 자식으로 추가
	rootUI->AddChildUI(lpRightMenu);
	rootUI->AddChildUI(lpHandCards);
	rootUI->AddChildUI(lpEventTimer);
	rootUI->AddChildUI(lpBattleUnit);
	rootUI->AddChildUI(lpItemSlot);

	//루트 Object에 자식으로 추가
	rootObject->AddChildObject(lpFieldTiles);

	return S_OK;
}

void InGame::Release()
{
	if (lpFieldTiles)
	{
		SAFE_RELEASE(lpFieldTiles);
	}

	if (lpRightMenu)
	{
		SAFE_RELEASE(lpRightMenu);
	}

	if (lpHandCards)
	{
		SAFE_RELEASE(lpHandCards);
	}

	if (lpEventTimer)
	{
		SAFE_RELEASE(lpEventTimer);
	}

	if(lpItemSlot)
	{
		SAFE_RELEASE(lpItemSlot);
	}
	if (lpFieldTiles)
	{
		SAFE_RELEASE(lpFieldTiles);
	}
	if (lpEventSystem)
	{
		SAFE_RELEASE(lpEventSystem);
	}
	if (lpBattleUnit)
	{
		SAFE_RELEASE(lpBattleUnit);
	}
	if (rootUI)
	{
		SAFE_RELEASE(rootUI);
	}
	if(rootObject)
	{
		SAFE_RELEASE(rootObject);
	}
}

void InGame::Update(float deltaTime)
{
	//옵저버 패턴. 몹 자동생성 이벤트
	EventHandler::GetInstance()->Update(deltaTime);
	//마우스 클릭, 드래그 등의 이벤트
	EventSystem::GetInstance()->Update(deltaTime);

	if (rootObject)
	{
		rootObject->Update(deltaTime);
	}
	if (rootUI)
	{
		rootUI->Update(deltaTime);
	}

}

void InGame::Render(HDC hdc)
{
	HDC hBackDC = lpBackBuffer->GetMemDC();


	if (lpBackground)
	{
		lpBackground->Render(hBackDC);
	}
	if (rootObject)
	{
		rootObject->Render(hBackDC);
	}
	if (rootUI)
	{
		rootUI->Render(hBackDC);
	}
		
	EventSystem::GetInstance()->Render(hBackDC);
	lpBackBuffer->Render(hdc);
}

