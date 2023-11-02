#include "ImageManager.h"
#include "Image.h"
#include <cmath>

HRESULT ImageManager::Init()
{
#pragma region UI
    //맵툴
    AddImage("SAVE", "Image/Save.bmp", 122, 62, 2, 1);
    AddImage("LOAD", "Image/Load.bmp", 122, 62, 2, 1);
    AddImage("오른쪽버튼", "Image/Right.bmp", 120, 60, 2, 1);
    AddImage("왼쪽버튼", "Image/Left.bmp", 120, 60, 2, 1);
    AddImage("SAMPLETILE", "Image/Tiles/sample_tile.bmp", 100 * 2, 50 * 2, 4, 2);
    AddImage("EXITBUTTON", "Image/UI/InGame/Button/button_exit.bmp", 35 * 2, 87 * 2, 1, 3, true, RGB(0, 170, 255), 3);
    //인게임
    AddImage("INGAMEBACKGROUND", "Image/UI/InGame/InGame_BackGround.bmp", 554*2, 434*2);
    AddImage("INGAMEINFO", "Image/UI/InGame/ingame_info_background.bmp", 296*2, 360*2, 2, 1, true, RGB(0, 170, 255));
    AddImage("INGAMETIMER", "Image/UI/InGame/ingame_bosstimer_background.bmp", 121*2, 27*2);
    AddImage("INGAMETIMERSPEED", "Image/UI/InGame/ingame_timerspeed_background.bmp", 69*2, 27*2);
    AddImage("INGAMEPLAYSTATE", "Image/UI/InGame/ingame_playstate_background.bmp", 146 * 2, 27 * 2, true, RGB(0, 170, 255));
    AddImage("INGAMELOOTINVEN", "Image/UI/InGame/ingame_lootinven_background.bmp", 189 * 2, 27 * 2, true, RGB(0, 170, 255));
    AddImage("STATUSBAR", "Image/UI/InGame/battle_unit_statusbar_hp.bmp", 25 * 8, 2 * 3, true, RGB(0, 170, 255));
    AddImage("HEROHPBAR", "Image/UI/InGame/hero_hpbar.bmp", 25 * 8, 5 * 3, true, RGB(0, 170, 255));
    AddImage("BATTLEBACKGROUND", "Image/UI/InGame/battle_background.bmp", 301 * 2, 257 * 2, true, RGB(0, 170, 255));
    //타이틀
    AddImage("TITLEBACKGROUND", "Image/UI/Title/title_background2.bmp", 644 * 2, 364 * 2, true, RGB(0, 170, 255));
#pragma endregion

#pragma region CARD
    AddImage("road_card", "Image/Cards/spider_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("battlefield_card", "Image/Cards/battlefield_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("bloodgrove_card", "Image/Cards/bloodgrove_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("cemetery_card", "Image/Cards/cemetery_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("crystal_card", "Image/Cards/crystal_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("grove_card", "Image/Cards/grove_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("lantern_card", "Image/Cards/lantern_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("meadom_card", "Image/Cards/meadom_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("mountain_card", "Image/Cards/mountain_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("oblivion_card", "Image/Cards/oblivion_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("rock_card", "Image/Cards/rock_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("spider_card", "Image/Cards/spider_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("swamp_card", "Image/Cards/swamp_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("tresury_card", "Image/Cards/tresury_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("village_card", "Image/Cards/village_card.bmp", 41 * 2, 58 * 2, 1, 1, true, RGB(0, 170, 255));
#pragma endregion

#pragma region TILE
    AddImage("bandit", "Image/Tiles/bandit_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("battlefield", "Image/Tiles/battlefield_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("bloodgrove", "Image/Tiles/bloodgrove_tile.bmp", 50 * 2, 34 * 2, 2, 1, true, RGB(0, 170, 255));
    AddImage("bloodroad", "Image/Tiles/bloodroad_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("cemetery", "Image/Tiles/cemetery_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("crystal", "Image/Tiles/crystal_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("goblin", "Image/Tiles/goblin_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("grove", "Image/Tiles/grove_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("lantern", "Image/Tiles/lantern_tile.bmp", 50 * 2, 34 * 2, 2, 1, true, RGB(0, 170, 255));
    AddImage("road", "Image/Tiles/road_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("rock", "Image/Tiles/rock_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("spider", "Image/Tiles/spider_tile.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("swamp", "Image/Tiles/swamp_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("tresury", "Image/Tiles/tresury_tile.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("village", "Image/Tiles/village_tile.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("NONETILE", "Image/Tiles/none_tile2.bmp", 25*2, 34*2, 1, 1, true, RGB(0, 170, 255));
    AddImage("POSSIBLE", "Image/Tiles/possible_tile.bmp", 23 * 2, 24 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("meadom", "Image/Tiles/meadom_tile.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("mountain", "Image/Tiles/mountain_tile.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("goblin", "Image/Tiles/goblin_tile.bmp", 25 * 2, 34 * 3, 1, 1, true, RGB(0, 170, 255));
    AddImage("campsite", "Image/Tiles/campsite_tile.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("battlefield_select", "Image/Tiles/battlefield_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("rock_select", "Image/Tiles/rock_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("bloodgrove_select", "Image/Tiles/bloodgrove_tile_select.bmp", 50 * 2, 34 * 2, 2, 1, true, RGB(0, 170, 255));
    AddImage("cemetery_select", "Image/Tiles/cemetery_tile_select.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("grove_select", "Image/Tiles/grove_tile_select.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("crystal_select", "Image/Tiles/crystal_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("lantern_select", "Image/Tiles/lantern_tile_select.bmp", 50 * 2, 34 * 2, 2, 1, true, RGB(0, 170, 255));
    AddImage("spider_select", "Image/Tiles/spider_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("swamp_select", "Image/Tiles/swamp_tile_select.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("tresury_select", "Image/Tiles/tresury_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("village_select", "Image/Tiles/village_tile_select.bmp", 25 * 2, 238 * 2, 1, 7, true, RGB(0, 170, 255));
    AddImage("meadom_select", "Image/Tiles/meadom_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("mountain_select", "Image/Tiles/mountain_tile_select.bmp", 25 * 2, 34 * 2, 1, 1, true, RGB(0, 170, 255));
#pragma endregion

#pragma region Equip
    AddImage("equip", "Image/Item/item.bmp", 375*2, 325 * 2, 15, 13, true, RGB(0, 170, 255));
    AddImage("equip_rare", "Image/Item/item_rank.bmp", 92 * 2, 23 * 2, 4, 1, true, RGB(0, 170, 255));
#pragma endregion

#pragma region Unit
    AddImage("hero_icon", "Image/ObjectIcon/hero_icon.bmp", 56 * 2, 14 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("hero_attack", "Image/Hero/Warrior/hero_attack.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("hero_death", "Image/Hero/Warrior/hero_death.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("hero_hurt", "Image/Hero/Warrior/hero_hurt.bmp", 240 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("hero_idle", "Image/Hero/Warrior/hero_idle.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255), 1);
    AddImage("hero_revive", "Image/Hero/Warrior/hero_revive.bmp", 360 * 2, 39 * 2, 6, 1, true, RGB(0, 170, 255), 6);
    AddImage("hero_intro", "Image/Hero/Warrior/hero_charge.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255), 1);
    AddImage("bandit_icon", "Image/ObjectIcon/bandit_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("chest_icon", "Image/ObjectIcon/chest_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("gargoyle_fly_icon", "Image/ObjectIcon/gargoyle_fly_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255),2);
    AddImage("gargoyle_icon", "Image/ObjectIcon/gargoyle_icon.bmp", 28*3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255),2);
    AddImage("ghost_icon", "Image/ObjectIcon/ghost_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255),2);
    AddImage("goblin_icon", "Image/ObjectIcon/goblin_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255),2);
    AddImage("harpy_icon", "Image/ObjectIcon/harpy_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255),2);
    AddImage("mosquito_icon", "Image/ObjectIcon/mosquito_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("mosquito_attack", "Image/Enemy/Mosquito/mosquito_attack.bmp", 240 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("mosquito_hurt", "Image/Enemy/Mosquito/mosquito_hurt.bmp", 240 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("mosquito_death", "Image/Enemy/Mosquito/mosquito_death_1.bmp", 540 * 2, 39 * 2, 9, 1, true, RGB(0, 170, 255), 9);
    AddImage("mosquito_idle", "Image/Enemy/Mosquito/mosquito_idle.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("ratwolf_icon", "Image/ObjectIcon/ratwolf_icon.bmp", 28* 3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("ratwolf_attack", "Image/Enemy/RatWolf/ratwolf_attack.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("ratwolf_death", "Image/Enemy/RatWolf/ratwolf_death.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("ratwolf_hurt", "Image/Enemy/RatWolf/ratwolf_hurt.bmp", 300 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("ratwolf_idle", "Image/Enemy/RatWolf/ratwolf_idle.bmp", 300 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("skel_icon", "Image/ObjectIcon/skeleton_icon.bmp", 28*3/2, 14*3/2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("skel_attack", "Image/Enemy/Skeleton/skeleton_attack.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("skel_death", "Image/Enemy/Skeleton/skeleton_death.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("skel_hurt", "Image/Enemy/Skeleton/skeleton_hurt.bmp", 240 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("skel_idle", "Image/Enemy/Skeleton/skeleton_idle.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255));
    AddImage("slime_icon", "Image/ObjectIcon/slime_icon.bmp", 28*3/2, 14*3/2, 2, 1, true, RGB(0, 170, 255), 2);
    AddImage("slime_attack", "Image/Enemy/Slime/slime_attack.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("slime_death", "Image/Enemy/Slime/slime_death.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("slime_revive", "Image/Enemy/Slime/slime_death.bmp", 300 * 2, 39 * 2, 5, 1, true, RGB(0, 170, 255), 5);
    AddImage("slime_hurt", "Image/Enemy/Slime/slime_hurt.bmp", 240 * 2, 39 * 2, 4, 1, true, RGB(0, 170, 255), 4);
    AddImage("slime_idle", "Image/Enemy/Slime/slime_idle.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255), 1);
    AddImage("slime_intro", "Image/Enemy/Slime/slime_idle.bmp", 60 * 2, 39 * 2, 1, 1, true, RGB(0, 170, 255), 1);
    AddImage("spider_icon", "Image/ObjectIcon/spider_icon.bmp", 28*3 / 2, 14* 3 / 2, 2, 1, true, RGB(0, 170, 255));
#pragma endregion

    AddImage("BACKBUFFER", "Image/background.bmp", WINSIZE_WIDTH, WINSIZE_HEIGHT); 
    return S_OK;
}

void ImageManager::Release()
{
    map<string, Image*>::iterator it;
    for (it = mLpImageDatas.begin(); it != mLpImageDatas.end(); it++)
    {
        if ((it->second))
        {
            (it->second)->Release();
            delete (it->second);
            (it->second) = nullptr;
        }
    }
    mLpImageDatas.clear();
    ReleaseSingleton();
}


Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    Image* image = nullptr;

    image = FindImage(key);
    if (image)
    {
        return image;
    }
    image = new Image();
    if (FAILED(image->Init(fileName, width, height, isTransparent, transColor)))
    {
        image->Release();
        delete image;

        return nullptr;
    }
    mLpImageDatas.insert(make_pair(key, image));
    return image;
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor, int totalFrame)
{
    Image* image = nullptr;

    image = FindImage(key);
    if (image)
    {
        return image;
    }

    image = new Image();
    if (FAILED(image->Init(fileName, width, height,
        maxFrameX, maxFrameY, isTransparent, transColor, totalFrame)))
    {
        image->Release();
        delete image;

        return nullptr;
    }

    mLpImageDatas.insert(make_pair(key, image));
    return image;
}


void ImageManager::DeleteImage(string key)
{
    map<string, Image*>::iterator it;
    it = mLpImageDatas.find(key);

    if (it == mLpImageDatas.end())
    {
        return;
    }

    (it->second)->Release();
    delete (it->second);
    (it->second) = nullptr;

    mLpImageDatas.erase(it);
}

Image* ImageManager::FindImage(string key)
{
    map<string, Image*>::iterator it;
    it = mLpImageDatas.find(key);

    if (it == mLpImageDatas.end())
    {
        return nullptr;
    }

    return it->second;
}
