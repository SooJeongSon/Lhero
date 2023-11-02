#pragma once
#include "Singleton.h"
#include <bitset>
#include <Windows.h>

#define MAX_INPUT_COUNT 256
using namespace std;

class KeyManager : public Singleton<KeyManager>
{
private:
	bitset<MAX_INPUT_COUNT> isKeyUp;
	bitset<MAX_INPUT_COUNT> isKeyDown;

public:
	HRESULT Init();
	void Release();
	bool IsOnceKeyDown(int input);
	bool IsOnceKeyUp(int input);
	bool IsStayKeyDown(int input);
};

