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
#include "Inventory.h"
#include "Level_Farm.h"
#include "globalValue.h"
#include "Pierre.h"


void Player::CreatePlayerKey()
{
    if (false == GameEngineInput::IsKey("DMove"))
    {
        GameEngineInput::CreateKey("DMove", 'S');
        GameEngineInput::CreateKey("UMove", 'W');
        GameEngineInput::CreateKey("LMove", 'A');
        GameEngineInput::CreateKey("RMove", 'D');
    }

    if (false == GameEngineInput::IsKey("MouseInteract"))
    {
        GameEngineInput::CreateKey("MouseInteract", VK_LBUTTON);
    }

    if (false == GameEngineInput::IsKey("KeyInteract"))
    {
        GameEngineInput::CreateKey("KeyInteract", 'E');
    }

    if (false == GameEngineInput::IsKey("Menu"))
    {
        GameEngineInput::CreateKey("Menu", VK_ESCAPE);
    }

    //농사 테스트키
    if (GameEngineInput::IsKey("MakeCrop") == false)
    {
        GameEngineInput::CreateKey("MakeCrop", 'O');
    }

    if (GameEngineInput::IsKey("QuickSlot_1") == false)
    {
        GameEngineInput::CreateKey("QuickSlot_1", '1');
        GameEngineInput::CreateKey("QuickSlot_2", '2');
        GameEngineInput::CreateKey("QuickSlot_3", '3');
        GameEngineInput::CreateKey("QuickSlot_4", '4');
        GameEngineInput::CreateKey("QuickSlot_5", '5');
        GameEngineInput::CreateKey("QuickSlot_6", '6');
        GameEngineInput::CreateKey("QuickSlot_7", '7');
        GameEngineInput::CreateKey("QuickSlot_8", '8');
        GameEngineInput::CreateKey("QuickSlot_9", '9');
        GameEngineInput::CreateKey("QuickSlot_0", '0');
    }

}


int Player::GetKeyInput()
{
    if (Pierre::IsOpenShop() == true)
    {
        if (true == GameEngineInput::IsDown("KeyInteract"))
        {
            return Act::KeyInteract;
        }

        return Act::Idle;
    }

    if (globalValue::isUpdate_CurLevelInventory(GetLevel()->GetName()) == true)
    {

        if (true == GameEngineInput::IsDown("Menu"))
        {
            return Act::Menu;
        }

        return Act::Idle;
    }

    else
    {
        if (true == GameEngineInput::IsDown("MouseInteract"))
        {
            return Act::MouseInteract;
        }

        if (true == GameEngineInput::IsDown("KeyInteract"))
        {
            return Act::KeyInteract;
        }

        else if (true == GameEngineInput::IsDown("ChangeQuickSlot"))
        {
            return Act::ChangeQuickSlot;
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

        else if (true == GameEngineInput::IsPress("QuickSlot_1"))
        {
            inputNumberKey = 1;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_2"))
        {
            inputNumberKey = 2;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_3"))
        {
            inputNumberKey = 3;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_4"))
        {
            inputNumberKey = 4;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_5"))
        {
            inputNumberKey = 5;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_6"))
        {
            inputNumberKey = 6;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_7"))
        {
            inputNumberKey = 7;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_8"))
        {
            inputNumberKey = 8;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_9"))
        {
            inputNumberKey = 9;
            return Act::ChangeQuickSlotItem;
        }
        else if (true == GameEngineInput::IsPress("QuickSlot_0"))
        {
            inputNumberKey = 10;
            return Act::ChangeQuickSlotItem;
        }

        else
        {
            return Act::Idle;
        }
    }
}


