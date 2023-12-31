#pragma once
#include "LoopHero.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// 프로젝트 자체에 포함 시킬 이미지
		FILE,			// 외부에서 로드할 이미지
		EMPTY,			// 자체 생산 이미지
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// 리소스의 고유한 ID
		HDC hMemDC;			// 그리기를 주관하는 핸들
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int width;			// 이미지 가로 크기
		int height;			// 이미지 세로 크기
		BYTE loadType;		// 로드 타입

		// 애니메이션 관련 (프레임데이터)
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;
		int totalFrame;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;		// 이미지 정보 구조체 포인터
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	// 빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 이미지를 로드하는 함수
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE, int totalFrame = 1);

	// 화면에 출력
	void Render(HDC hdc, int destX = 0, int destY = 0,
		bool isCenterRenderring = false, bool isTransparent = false, COLORREF transColor = RGB(0,170,255));
	void FrameRender(HDC hdc, int destX, int destY,
		int currFrameX, int currFrameY, bool isCenterRenderring = false, int size = 1, bool isTransparent=false, COLORREF transColor = RGB(0,170,255));

	void Release();

	// get, set
	HDC GetMemDC()
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}

	inline int GetWidth() { return this->imageInfo->width; }
	inline int GetHeight() { return this->imageInfo->height; }
	inline int GetFrameWidth() { return this->imageInfo->frameWidth; }
	inline int GetFrameHeight() { return this->imageInfo->frameHeight; }
	inline void SetWidth(int width) { this->imageInfo->width = width; }
	inline int GetTotalFrame() { return (imageInfo) ? imageInfo->totalFrame : 1; }
	IMAGE_INFO* const GetImageInfo() { return this->imageInfo; }
};

