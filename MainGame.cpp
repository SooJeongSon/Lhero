#include "MainGame.h"
#include "LoopHero.h"
#include "Image.h"

HRESULT MainGame::Init()
{
    hdc = GetDC(g_hWnd);

    KeyManager::GetInstance()->Init();
    ImageManager::GetInstance()->Init();
    SceneManager::GetInstance()->Init();
    TimerManager::GetInstance()->Init();
    GameData::GetInstance()->Init();
    EventHandler::GetInstance()->Init();
    EventSystem::GetInstance()->Init();
    EquipTable::GetInstance()->Init();

    backBuffer = new Image();
    backBuffer->Init(WINSIZE_WIDTH, WINSIZE_HEIGHT);

    SceneManager::GetInstance()->ChangeScene("TITLE");
    isInited = true;
    return S_OK;
}

void MainGame::Release()
{
    KeyManager::GetInstance()->Release();
    ImageManager::GetInstance()->Release();
    SceneManager::GetInstance()->Release();
    TimerManager::GetInstance()->Release();

    if (backBuffer)
    {
        backBuffer->Release();
        delete backBuffer;
        backBuffer = nullptr;
    }
    ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown('P'))
    {
        isDebugMode = !isDebugMode;
    }
    SceneManager::GetInstance()->Update(TimerManager::GetInstance()->GetElapsedTime());
}

void MainGame::Render()
{
    HDC hBackDC = backBuffer->GetMemDC();
    SceneManager::GetInstance()->Render(hBackDC);

    //FPS
    TimerManager::GetInstance()->Render(hBackDC);
    backBuffer->Render(hdc);
}

LRESULT MainGame::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_MOUSEMOVE:
        g_ptMouse.x = LOWORD(lParam);
        g_ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
    isInited = false;
}

MainGame::~MainGame()
{
}
