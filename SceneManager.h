#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <map>
#include <string>

using namespace std;

class GameScene;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameScene*>	mSceneDatas;
	map<string, GameScene*>	mLoadingSceneDatas;

public:
	static GameScene* currentScene;
	static GameScene* loadingScene;
	static GameScene* readyScene;

public:
	HRESULT Init();
	void Release();
	void Update(float deltaTime);
	void Render(HDC hdc);

	GameScene* AddScene(string key, GameScene* scene);
	GameScene* AddLoadingScene(string key, GameScene* scene);

	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingsceneName);
};

