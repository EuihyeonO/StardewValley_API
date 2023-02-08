#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Farm.h"
#include "GlobalFunction.h"
#include "Inventory.h"
#include "Level_Farm.h"


void Player::CreatePlayerKey()
{
    if (false == GameEngineInput::IsKey("DMove"))
    {
        GameEngineInput::CreateKey("DMove", 'S');
        GameEngineInput::CreateKey("UMove", 'W');
        GameEngineInput::CreateKey("LMove", 'A');
        GameEngineInput::CreateKey("RMove", 'D');
    }

    if (false == GameEngineInput::IsKey("Interact"))
    {
        GameEngineInput::CreateKey("Interact", 'E');
    }

    if (false == GameEngineInput::IsKey("Menu"))
    {
        GameEngineInput::CreateKey("Menu", VK_ESCAPE);
    }

    if (false == GameEngineInput::IsKey("ToolChange"))
    {
        GameEngineInput::CreateKey("ToolChange", 'F');
    }

    //농사 테스트키
    if (GameEngineInput::IsKey("MakeCrop") == false)
    {
        GameEngineInput::CreateKey("MakeCrop", 'O');
    }
}


int Player::GetKeyInput()
{
    if (Inventory::GetInventoryRender()->IsUpdate() == true)
    {

        if (true == GameEngineInput::IsDown("Menu"))
        {
            return Act::Menu;
        }

        return Act::Idle;
    }

    else
    {
        if (true == GameEngineInput::IsDown("Interact"))
        {
            return Act::Interact;
        }

        else if (true == GameEngineInput::IsDown("ToolChange"))
        {
            return Act::ToolChange;
        }

        else if (true == GameEngineInput::IsDown("Menu"))
        {
            return Act::Menu;
        }

        else if (true == GameEngineInput::IsPress("LMove") ||
            true == GameEngineInput::IsPress("RMove") ||
            true == GameEngineInput::IsPress("UMove") ||
            true == GameEngineInput::IsPress("DMove"))
        {
            return Act::Move;
        }

        else
        {
            return Act::Idle;
        }
    }
}