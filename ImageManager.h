#pragma once
#include "Singleton.h"
#include "LoopHero.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*> mLpImageDatas;

public:
	HRESULT Init();
	void Release();

	Image* AddImage(string key, const char* fileName,
		int width, int height, bool isTransparent = FALSE,
		COLORREF transColor = FALSE);

	Image* AddImage(string key, const char* fileName,
		int width, int height, int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE, int totalFrame = 1);

	void DeleteImage(string key);
	Image* FindImage(string key);
};