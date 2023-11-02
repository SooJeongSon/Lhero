#include "SceneManager.h"
#include "GameScene.h"
#include "InGame.h"
#include "Title.h"

GameScene* SceneManager::currentScene = nullptr;
GameScene* SceneManager::loadingScene = nullptr;
GameScene* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
    if (SUCCEEDED(SceneManager::readyScene->Init()))
    {
        SceneManager::currentScene = SceneManager::readyScene;

        SceneManager::loadingScene->Release();
        SceneManager::loadingScene = nullptr;
        SceneManager::readyScene = nullptr;
    }
    return 0;
}

HRESULT SceneManager::Init()
{
    SceneManager::GetInstance()->AddScene("INGAME", new InGame());
    SceneManager::GetInstance()->AddScene("TITLE", new Title());
    return S_OK;
}

void SceneManager::Release()
{
    map<string, GameScene*>::iterator it;
    for (it = mSceneDatas.begin(); it != mSceneDatas.end(); it++)
    {
        if (it->second)
        {
            SAFE_RELEASE(it->second);
        }
    }
    mSceneDatas.clear();

    ReleaseSingleton();
}

void SceneManager::Update(float deltaTime)
{
    if (currentScene)
    {
        currentScene->Update(deltaTime);
    }
}

void SceneManager::Render(HDC hdc)
{
    if (currentScene)
    {
        currentScene->Render(hdc);
    }
}

GameScene* SceneManager::AddScene(string key, GameScene* scene)
{
    if (scene == nullptr)
    {
        return nullptr;
    }

    map<string, GameScene*>::iterator it = mSceneDatas.find(key);
    if (it != mSceneDatas.end())
    {
        return it->second;
    }

    mSceneDatas.insert(pair<string, GameScene*>(key, scene));

    return scene;
}

GameScene* SceneManager::AddLoadingScene(string key, GameScene* scene)
{
    if (scene == nullptr)
    {
        return nullptr;
    }

    map<string, GameScene*>::iterator it = mLoadingSceneDatas.find(key);
    if (it != mLoadingSceneDatas.end())
    {
        return it->second;
    }

    mLoadingSceneDatas.insert(pair<string, GameScene*>(key, scene));

    return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
    map<string, GameScene*>::iterator it = mSceneDatas.find(sceneName);
    if (it == mSceneDatas.end())
    {
        return E_FAIL;
    }

    if (it->second == currentScene)
    {
        return S_OK;
    }

    if (SUCCEEDED(it->second->Init()))
    {
        if (currentScene)
        {
            currentScene->Release();
        }
        currentScene = it->second;

        return S_OK;
    }

    return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingsceneName)
{
    map<string, GameScene*>::iterator it = mSceneDatas.find(sceneName);
    if (it == mSceneDatas.end())
    {
        return E_FAIL;
    }

    if (it->second == currentScene)
    {
        return S_OK;
    }

    //로딩씬 찾기
    map<string, GameScene*>::iterator itLoading = mLoadingSceneDatas.find(loadingsceneName);
    if (itLoading == mLoadingSceneDatas.end())
    {
        return ChangeScene(sceneName);
    }

    if (SUCCEEDED(itLoading->second->Init()))
    {
        if (currentScene)
        {
            currentScene->Release();
        }
        currentScene = itLoading->second;

        readyScene = it->second;
        loadingScene = itLoading->second;

        //다음 씬을 초기화할 쓰레드를 생성
        DWORD loadingThreadId;
        HANDLE hThread;
        hThread = CreateThread(NULL, 0,
            LoadingThread,      //실행 시킬 함수포인터
            NULL,               //실행 시킬 함수에 들어갈 매개변수
            0,
            &loadingThreadId
        );

        CloseHandle(hThread);
        return S_OK;
    }
    return E_FAIL;
}
