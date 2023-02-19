#include "globalSound.h"
#include "Inventory.h"
#include "Pierre.h"
#include "globalValue.h"
#include "Player.h"
#include "ContentsEnum.h"

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

    WateringSound = GameEngineResources::GetInst().SoundPlayToControl("Watering.wav");
    WateringSound.PauseOn();
    
    Farm_BGM = GameEngineResources::GetInst().SoundPlayToControl("Farm_BGM.Mp3");
    Farm_BGM.PauseOn();
}

void globalSound::WalkSoundOn(const std::string_view _LevelName)
{
    if (globalValue::isUpdate_CurLevelInventory(_LevelName))
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
}

void globalSound::SoundUpdate(const std::string_view _LevelName)
{

    if (Player::GetPlayer()->isInteract() == true)
    {
        return;
    }
    
    int Act = globalValue::GetKeyInput();
   
    switch (Act)
    {
    case Act::Idle:
        SoundOff();
        break;
    case Act::Move:
        WalkSoundOn(_LevelName);
        break;
    case Act::MouseInteract:
        ToolSoundOn();
        break;
    case Act::KeyInteract:
        break;
    }
}

void globalSound::ToolSoundOn()
{
    if (Player::IsSameCurTool("Pick") == true)
    {
        //PickSound.PauseOff();
    }
    else if (Player::IsSameCurTool("Hoe") == true)
    {
        //HoeSound.PauseOff();
    }
    else if (Player::IsSameCurTool("Axe") == true)
    {
        //AxeSound.PauseOff();
    }
    else if (Player::IsSameCurTool("Watering") == true)
    {
    }
}

void globalSound::SoundOff()
{
    WalkSound.PauseOn();
}


void globalSound::BGM_On(const std::string_view _LevelName)
{
    if (_LevelName != "Title")
    {
        Farm_BGM.PauseOff();
    }
}