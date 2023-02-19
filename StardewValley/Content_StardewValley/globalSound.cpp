#include "globalSound.h"
#include "Inventory.h"
#include "Pierre.h"
#include "globalValue.h"

#include <GameEnginePlatform/GameEngineInput.h>

globalSound::globalSound()
{
}

globalSound::~globalSound()
{
}

void globalSound::SoundInit()
{
    WalkSound = GameEngineResources::GetInst().SoundPlayToControl("Walk.wav");
    WalkSound.PauseOn();
}

void globalSound::WalkSoundOff()
{  
    WalkSound.PauseOn();
}

void globalSound::WalkSoundOn()
{
    WalkSound.PauseOff();
}

void globalSound::WalkSoundOnOff(const std::string_view _LevelName)
{
    if (globalValue::isUpdate_CurLevelInventory(_LevelName) || Pierre::IsOpenShop() == true)
    {
        return;
    }
    if (GameEngineInput::IsPress("DMove") ||
        GameEngineInput::IsPress("UMove") ||
        GameEngineInput::IsPress("RMove") ||
        GameEngineInput::IsPress("LMove"))
    {
        WalkSound.PauseOff();
    }
    else 
    {
        WalkSound.PauseOn();
    }
}