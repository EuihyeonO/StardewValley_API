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

void Player::ToolChange()
{
    if (CurTool == nullptr)
    {
        MsgAssert("CurTool이 설정되지 않았는데 변경하려 했습니다.");
    }

    std::string Name = Inventory::GetSelectedItemName();

    if (Inventory::GetSelectedItemName() == "AxeIcon.bmp")
    {
        CurTool = Tool["Axe"];
    }
    else if (Inventory::GetSelectedItemName() == "HoeIcon.bmp")
    {
        CurTool = Tool["Hoe"];
    }
    else if (Inventory::GetSelectedItemName() == "PickIcon.bmp")
    {
        CurTool = Tool["Pick"];
    }
    else if (Inventory::GetSelectedItemName() == "WateringIcon.bmp")
    {
        CurTool = Tool["Watering"];
    }
}


void Player::InitTool()
{
    Pick = CreateRender(2);
    Axe = CreateRender(2);
    Hoe = CreateRender(2);
    Watering = CreateRender(2);

    Tool.insert({ "Pick", Pick });
    Tool.insert({ "Axe", Axe });
    Tool.insert({ "Hoe", Hoe });
    Tool.insert({ "Watering", Watering });

    //Dir이 R인지 L인지에 따라 다르게 만들어야함
    ColPick = CreateCollision(ActorType::Tool);
    ColPick->SetScale({ 64,64 });   

    ColAxe = CreateCollision(ActorType::Tool);
    ColAxe->SetScale({ 64,64 });

    ColHoe = CreateCollision(ActorType::Tool);
    ColHoe->SetScale({ 64,64 });

    ColWatering = CreateCollision(ActorType::Tool);
    ColWatering->SetScale({ 64,64 });


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
    ColPick->SetPosition(SetToolPos());
    ColAxe->SetPosition(SetToolPos());
    ColHoe->SetPosition(SetToolPos());
    ColWatering->SetPosition(SetToolPos());
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