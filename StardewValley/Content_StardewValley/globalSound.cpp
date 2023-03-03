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
    
    Farm_BGM = GameEngineResources::GetInst().SoundPlayToControl("Farm_BGM.Mp3");
    Farm_BGM.PauseOn();

    Title_BGM = GameEngineResources::GetInst().SoundPlayToControl("Title_BGM.Mp3");
    Title_BGM.PauseOn();
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


void globalSound::BGM_On(const std::string_view _LevelName)
{
    if (_LevelName != "Title")
    {
        Farm_BGM.PauseOff();

        if (Title_BGM.GetPause() == false)
        {
            if (Volume > 0)
            {
                Volume -= 0.005f;
                Title_BGM.Volume(Volume);
            }
            if (Volume <= 0)
            {
                Title_BGM.PauseOn();
            }
        }
    }
    else if (_LevelName == "Title")
    {
        Title_BGM.PauseOff();
    }
}