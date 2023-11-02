#include "Hero.h"
#include "Image.h"
#include "Animation.h"

HRESULT Hero::Init()
{
    width = 14 * 2;
    height = 14 * 2;
    name = "hero";
    hp = 10.0f;
    maxHp = 20.0f;
    attackDmg = 0.1f;
    defenseValue = 1.0f;
    vampValue = 1.0f;
    conterValue = 1.0f;
    splashDmg = 1.0f;
    evasion = 3.0f;
    attackSpeed = 0.5f;
    moveSpeed = 20.0f;
    GameData::GetInstance()->SetStatFirstTime();
    GameData::GetInstance()->SetBaseStat();
    SetPos({ (float)g_ptMouse.x , (float)g_ptMouse.y });
    SetRect(&rc, pos.x - width/2, pos.y - height/2, pos.x + width/2, pos.y + height/2);
    state = HERO_STATE::LOOP;
    lpIconAni = new Animation();
    lpIconAni->Change("hero_icon", 5, true);
    return S_OK;
}

void Hero::Release()
{
}

void Hero::Update(float deltaTime)
{
    SetRect(&rc, pos.x - width / 2, pos.y - height / 2, pos.x + width / 2, pos.y + height / 2);

    if (state == HERO_STATE::LOOP)
    {
        if (lpIconAni)
        {
            lpIconAni->Update(deltaTime);
        }
    }
}

void Hero::Render(HDC hdc)
{
    if (isDebugMode)
    {
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    }

    if (lpIconAni)
    {
        lpIconAni->Render(hdc, pos.x, pos.y, true);
    }
}
