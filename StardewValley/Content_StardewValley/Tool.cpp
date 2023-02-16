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

void Player::ToolChange()
{
    if (CurTool == nullptr)
    {
        MsgAssert("CurTool이 설정되지 않았는데 변경하려 했습니다.");
    }

    if (CurToolType == static_cast<int>(ItemType::Axe))
    {
        CurTool = Tool["Axe"];
    }
    else if (CurToolType == static_cast<int>(ItemType::Hoe))
    {
        CurTool = Tool["Hoe"];
    }
    else if (CurToolType == static_cast<int>(ItemType::Pick))
    {
        CurTool = Tool["Pick"];
    }
    else if (CurToolType == static_cast<int>(ItemType::Watering))
    {
        CurTool = Tool["Watering"];
    }
    else
    {
        CurTool = Tool["Default"];
    }
}


void Player::InitTool()
{
    Pick = CreateRender(50);
    Axe = CreateRender(50);
    Hoe = CreateRender(50);
    Watering = CreateRender(50);

    Default = CreateRender("Default.bmp", 2);
    Default->Off();

    Tool.insert({ "Pick", Pick });
    Tool.insert({ "Axe", Axe });
    Tool.insert({ "Hoe",  Hoe });
    Tool.insert({ "Watering", Watering });
    Tool.insert({ "Default", Default });

    //Dir이 R인지 L인지에 따라 다르게 만들어야함
    ColTool = CreateCollision(ActorType::Tool);
    ColTool->SetScale({ 64,64 });

    CurTool = Tool["Pick"];

}

float4 Player::SetToolPos()
{
    if (Dir == "R")
    {
        return { 64, 32 };
    }
    else if (Dir == "L")
    {
        return { -64,32 };
    }
    else if (Dir == "U")
    {
        return { 0,0 };
    }
    else if (Dir == "D")
    {
        return { 0,64 };
    }

    else return { 0,0 };
}

void Player::ToolPosUpdate()
{
    ColTool->SetPosition(SetToolPos());
}

bool Player::IsSameCurTool(std::string _ToolName)
{
    if (MyPlayer->CurTool == MyPlayer->Tool[_ToolName])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::CurToolTypeUpdate()
{
    if (globalValue::GetSelectedItem() != nullptr)
    {
        CurToolType = globalValue::GetSelectedItem()->GetItemType();
    }
}