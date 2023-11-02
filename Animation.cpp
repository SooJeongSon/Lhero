#include "Animation.h"
#include "Image.h"


void Animation::Change(string imageKey, int fps, bool isLoop, bool isReset)
{
	if (isReset)
	{
		lpImage = ImageManager::GetInstance()->FindImage(imageKey);
		this->imageKey = imageKey;
		this->isLoop = isLoop;
		this->fps = fps;
		frame = 0;
	}
	else
	{
		if (lpImage)
		{
			if (this->imageKey != imageKey)
			{
				lpImage = ImageManager::GetInstance()->FindImage(imageKey);
				this->imageKey = imageKey;
				this->isLoop = isLoop;
				this->fps = fps;
				frame = 0;
			}
		}
		else
		{
			lpImage = ImageManager::GetInstance()->FindImage(imageKey);
			this->imageKey = imageKey;
			this->isLoop = isLoop;
			this->fps = fps;
			frame = 0;
		}
	}
	state = ANIMATION_STATE::PLAY;
}

void Animation::Update(float deltaTime)
{
	switch (state)	
	{
	case ANIMATION_STATE::STOP:
		frame = 0;
		break;
	case ANIMATION_STATE::PLAY:
		frame += deltaTime * (float)fps;
		if (frame >= lpImage->GetTotalFrame())
		{
			if (isLoop)
			{
				frame = /*((int)(frame / lpImage->GetTotalFrame()) * lpImage->GetTotalFrame())*/0;
			}
			else
			{
				frame = lpImage->GetTotalFrame() - 1;
			}
		}
		break;
	default:
		break;
	}	
}

void Animation::Render(HDC hdc, int destX, int destY, bool centerRender)
{
	lpImage->FrameRender(hdc, destX, destY, ((int)frame), 0, centerRender, 1, true, RGB(0, 170, 255));
}

void Animation::SetCallBack(function<void()> func)
{
	callBack = move(func);
}

void Animation::Stop()
{
	state = ANIMATION_STATE::STOP;
}

void Animation::Play()
{
	if (!lpImage)
	{
		if (callBack)
		{
			callBack();
		}
		return;
	}
	state = ANIMATION_STATE::PLAY;
}

void Animation::Resume()
{
	state = ANIMATION_STATE::PLAY;
}
