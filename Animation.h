#pragma once
#include "LoopHero.h"

enum class ANIMATION_STATE
{
	STOP,
	PLAY
};

class Image;
class Animation
{
private:
	bool isLoop;
	float frame;
	int fps;
	Image* lpImage;
	string imageKey;
	function<void()> callBack;
	ANIMATION_STATE	state;

public:
	//void Init(string key, int fps, bool isLoop = true, bool isReset = false);
	void Change(string imageKey, int fps, bool isLoop = true, bool isReset = false);
	void Update(float deltaTime);
	void Render(HDC hdc, int destX, int destY, bool centerRender = false);

	inline Image* GetLpImage() { return lpImage; }
	inline int GetFrame() { return (int)frame; }

	void SetCallBack(function<void()> func);
	void Stop();
	void Play();
	void Resume();	
};
