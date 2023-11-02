#include "KeyManager.h"

HRESULT KeyManager::Init()
{
    isKeyUp.set();
    isKeyDown.reset();
    return S_OK;
}

void KeyManager::Release()
{
    ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int input)
{
    if (GetAsyncKeyState(input) & 0x8000)
    {
        if (isKeyDown[input] == false)
        {
            isKeyDown[input] = true;
            return true;
        }
    }
    else
    {
        isKeyDown[input] = false;
    }

    return false;
}

bool KeyManager::IsOnceKeyUp(int input)
{
    if (GetAsyncKeyState(input) & 0x8000)
    {
        isKeyUp[input] = false;
    }
    else
    {
        if (!isKeyUp[input])
        {
            isKeyUp[input] = true;
            return true;
        }
    }
    return false;
}

bool KeyManager::IsStayKeyDown(int input)
{
    if (GetAsyncKeyState(input) & 0x8000)
    {
        return true;
    }
    return false;
}