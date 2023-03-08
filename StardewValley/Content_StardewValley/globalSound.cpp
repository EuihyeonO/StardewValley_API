#include "globalSound.h"
#include "Inventory.h"
#include "Pierre.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>

globalSound* globalSound::globalSoundPlayer = nullptr;

globalSound::globalSound()
{
    globalSoundPlayer = this;
}

globalSound::~globalSound()
{
}

void globalSound::SoundInit()
{
    WalkSound = GameEngineResources::GetInst().SoundPlayToControl("Walk.wav");
    WalkSound.PauseOn();
    
    Farm_BGM = GameEngineResources::GetInst().SoundPlayToControl("Farm_BGM.MP3");
    Farm_BGM.PauseOn();
    Farm_BGM.Volume(0);

    Title_BGM = GameEngineResources::GetInst().SoundPlayToControl("Title_BGM.MP3");
    Title_BGM.PauseOn();

    Mine_BGM = GameEngineResources::GetInst().SoundPlayToControl("Mine_BGM.WAV");
    Mine_BGM.PauseOn();
    Mine_BGM.Volume(0);

    TypingSound = GameEngineResources::GetInst().SoundPlayToControl("Typing.wav");
    TypingSound.PauseOn();
}

void globalSound::WalkSoundOn()
{
    if (globalInterface::isMenuOpen() == true || Player::GetIsAbleAct() == false)
    {      
        return;
    }

    WalkSound.PauseOff();
}

void globalSound::SoundUpdate(const std::string_view _LevelName)
{


}
void globalSound::WalkSoundOff()
{
    WalkSound.PauseOn();
}

void globalSound::TypingSoundOn()
{
    TypingSound.PauseOff();
}

void globalSound::TypingSoundOff()
{
    TypingSound.PauseOn();
}


void globalSound::BGM_On(const std::string_view _LevelName)
{
    if (_LevelName == "Farm" || _LevelName == "House")
    {
        Farm_BGM.PauseOff();

        //Å¸ÀÌÆ² ºê±Ý ²¨¹ö¸²
        if (Volume > 0)
        {
            Volume -= 0.005f;
            Title_BGM.Volume(Volume);
        }
        else if (Volume <= 0)
        {
            Title_BGM.PauseOn();
        }

        //³óÀå º¼·ý ÄÔ
        if (FarmVolume < 1)
        {
            FarmVolume += 0.005f;
            Farm_BGM.Volume(FarmVolume);
        }
        else if (FarmVolume >= 1)
        {
            FarmVolume = 1;
        }

        //±¤»ê ºê±Ý ²¨¹ö¸²
        if (MineVolume > 0)
        {
            MineVolume -= 0.005f;
            Mine_BGM.Volume(MineVolume);
        }
        else if (MineVolume <= 0)
        {
            MineVolume = 0;
            Mine_BGM.PauseOn();
        }
    }
    else if (_LevelName == "Mine")
    {
        Mine_BGM.PauseOff();

        //³óÀå ºê±Ý ²¨¹ö¸²
        if (FarmVolume > 0)
        {
            FarmVolume -= 0.005f;
            Farm_BGM.Volume(FarmVolume);
        }
        else if (FarmVolume <= 0)
        {
            FarmVolume = 0;
            Farm_BGM.PauseOn();
        }

        //°ü¤·»ê ºê±Ý ÄÔ
        if (MineVolume < 1)
        {
            MineVolume += 0.005f;
            Mine_BGM.Volume(MineVolume);
        }
        else if (MineVolume >= 1)
        {
            MineVolume = 1;
            Mine_BGM.Volume(MineVolume);
        }
    }

    else if (_LevelName == "Title")
    {
        Title_BGM.PauseOff();
    }
}