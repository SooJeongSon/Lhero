#include "Button.h"
#include "Image.h"

HRESULT Button::Init(const char* fileName, int posX, int posY)
{
	buttonState = ButtonState::NONE;
	lpImage = ImageManager::GetInstance()->FindImage(fileName);
	if (lpImage == nullptr)
	{
		string warningText = string(fileName) + "�� ����!";
		MessageBox(g_hWnd, warningText.c_str(), "����", MB_OK);
		return E_FAIL;
	}


	pos.x = posX;
	pos.y = posY;

	rcButton.left = pos.x - lpImage->GetFrameWidth() / 2;
	rcButton.top = pos.y - lpImage->GetFrameHeight() / 2;
	rcButton.right = pos.x + lpImage->GetFrameWidth() / 2;
	rcButton.bottom = pos.y + lpImage->GetFrameHeight() / 2;

	func = nullptr; // TilemapTool::Save;

	return S_OK;
}

HRESULT Button::Init()
{
	return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rcButton, g_ptMouse))
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LBUTTON))
		{
			buttonState = ButtonState::DOWN;
		}
		else if (buttonState == ButtonState::DOWN && KeyManager::GetInstance()->IsOnceKeyUp(VK_LBUTTON))
		{
			buttonState = ButtonState::UP;

			//��ư ��� ���� : ���̺�, �ε�
			func(funcArg);
		}
	}
	else
	{
		buttonState = ButtonState::NONE;
	}
}

void Button::Render(HDC hdc)
{
	switch (buttonState)
	{
	case ButtonState::NONE:
	case ButtonState::UP:
		lpImage->FrameRender(hdc, pos.x, pos.y, 0, 0, true);
		break;

	case ButtonState::DOWN:
		lpImage->FrameRender(hdc, pos.x, pos.y, 1, 0, true);
		break;
	}
}
