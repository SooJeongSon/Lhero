#include "Mob.h"
#include "Breed.h"
#include "Image.h"
#include "Animation.h"

HRESULT Mob::Init()
{
    return E_NOTIMPL;
}

void Mob::Release()
{
}

void Mob::Update(float deltaTime)
{
    if (lpIconAni)
    {
       lpIconAni->Update(deltaTime);
    }
}

void Mob::Render(HDC hdc)
{
    if (lpIconAni)
    {
        lpIconAni->Render(hdc, pos.x, pos.y);
    }
}

Mob::Mob(Breed& breed, float maxHp)
{
    name = breed.GetName();
    this->maxHp = maxHp;
    this->hp = 50.0f;
    this->attackDmg = 0.001f;
    this->attackSpeed = 1.0f;
    string key = name + "_icon";
    SetRect(&rc, WINSIZE_WIDTH / 2, WINSIZE_HEIGHT / 2, WINSIZE_WIDTH / 2 +10, WINSIZE_HEIGHT / 2 + 10);
    this->lpIconAni = new Animation();
    lpIconAni->Change(key, 2, true, false);
}
