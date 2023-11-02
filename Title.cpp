#include "Title.h"
#include "Image.h"

HRESULT Title::Init()
{
    lpBackground = ImageManager::GetInstance()->FindImage("TITLEBACKGROUND");
    lpBackBuffer = ImageManager::GetInstance()->FindImage("BACKBUFFER");
    return S_OK;
}

void Title::Release()
{
}

void Title::Update(float deltaTime)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
    {
        SceneManager::GetInstance()->ChangeScene("INGAME");
    }
}

void Title::Render(HDC hdc)
{
    HDC hBackDC = lpBackBuffer->GetMemDC();

    lpBackground->Render(hBackDC);

    lpBackBuffer->Render(hdc);
}
