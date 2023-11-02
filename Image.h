#pragma once
#include "LoopHero.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,		// ������Ʈ ��ü�� ���� ��ų �̹���
		FILE,			// �ܺο��� �ε��� �̹���
		EMPTY,			// ��ü ���� �̹���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ������ ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		// �ִϸ��̼� ���� (�����ӵ�����)
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
	IMAGE_INFO* imageInfo;		// �̹��� ���� ����ü ������
	//LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE, int totalFrame = 1);

	// ȭ�鿡 ���
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

