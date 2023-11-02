#include "Deck.h"
#include "Image.h"
#include "Card.h"

HRESULT Deck::Init()
{
	mCardListByType.insert(make_pair(CARD_TYPE::ROAD, vector<Card*>()));
	mCardListByType.insert(make_pair(CARD_TYPE::ROAD_SIDE, vector<Card*>()));
	mCardListByType.insert(make_pair(CARD_TYPE::ENVIRONMENT, vector<Card*>()));
	mCardListByType.insert(make_pair(CARD_TYPE::SPECIAL, vector<Card*>()));

	LoadCardData();

	return S_OK;
}

void Deck::Release()
{
	for (int i = 0; i < vCardList.size(); ++i)
	{
		vCardList[i]->Release();
		delete vCardList[i];
	}
	vCardList.clear();

	for (int i = 0; i < vActiveCards.size(); ++i)
	{
		vActiveCards[i]->Release();
		delete vActiveCards[i];
	}
	vActiveCards.clear();
}

void Deck::Update(float deltaTime)
{
	for (int i = 0; i < vCardList.size(); ++i)
	{
		vCardList[i]->Update(deltaTime);
	}
}

void Deck::Render(HDC hdc)
{
	for (auto pair : mCardListByType)
	{
		for (Card* lpCard : pair.second)
		{
			lpCard->Render(hdc);
		}
	}
}

Card* Deck::GetRandomCard()
{
	CARD_RARE rare = (CARD_RARE)(rand() % 2);
	vector<Card*> vCards = mCardListByRare[rare];
	if (!vCards.empty())
	{
		Card* randCard = vCards[rand() % vCards.size()];
		Card* lpCard = nullptr;
		if (vDeactiveCards.empty())
		{
			lpCard = new Card(*randCard);
			lpCard->hFont = CreateFont(13, 5, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, OUT_TT_ONLY_PRECIS, 0, DEFAULT_QUALITY, VARIABLE_PITCH | FF_ROMAN, TEXT("µ¸¿ò"));
		}
		else
		{
			lpCard = vDeactiveCards.back();
			vDeactiveCards.pop_back();

			HFONT hFont = lpCard->hFont;
			*lpCard = *randCard;
			lpCard->hFont = hFont;
		}
		vActiveCards.push_back(lpCard);
		return lpCard;
	}
	return nullptr;
}

Card* Deck::CreateCard(string cardId)
{
	Card* lpCard = new Card();

	lpCard->Init();
	lpCard->id = cardId;
	lpCard->lpIconImg = ImageManager::GetInstance()->FindImage(cardId + "_select");
	lpCard->lpCardImg = ImageManager::GetInstance()->FindImage(cardId + "_card");

	return lpCard;
}

void Deck::LoadCardData()
{
	FileManager::GetInstance()->LoadIniFile("Text/card_data.ini", "cards");
	FileManager::GetInstance()->LoadIniFile("Text/tile_data.ini", "tiles");

	map<string, map<string, string>> mDatas = FileManager::GetInstance()->GetData("cards");
	int index = 0;
	for (auto group : mDatas)
	{
		CARD_TYPE type = (CARD_TYPE)stoi(group.second["type"]);
		CARD_RARE rare = (CARD_RARE)stoi(group.second["rare"]);
		Card* lpCard = CreateCard(group.first);
		lpCard->tileKey = group.second["tileKey"];
		lpCard->type = type;
		lpCard->rare = rare;
		lpCard->name = FileManager::GetInstance()->GetData("tiles", group.second["tileKey"], "name");
		lpCard->desc = FileManager::GetInstance()->GetData("tiles", group.second["tileKey"], "desc");
		lpCard->SetPos({ 43.0f + index++ * 74.5f, WINSIZE_HEIGHT - 20.0f });

		vCardList.push_back(lpCard);
		mCardListByType[type].push_back(lpCard);
		mCardListByRare[rare].push_back(lpCard);
	}

}
