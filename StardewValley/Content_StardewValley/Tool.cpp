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

void Player::ToolChange()
{
    if (CurTool == nullptr)
    {
        MsgAssert("CurTool이 설정되지 않았는데 변경하려 했습니다.");
    }

    if (CurTool == Tool["Axe"])
    {
        CurTool = Tool["Pick"];
    }
    else if (CurTool == Tool["Pick"])
    {
        CurTool = Tool["Hoe"];
    }
    else if (CurTool == Tool["Hoe"])
    {
        CurTool = Tool["Axe"];
    }
}


void Player::InitTool()
{
    Pick = CreateRender(2);
    Axe = CreateRender(2);
    Hoe = CreateRender(2);

    Tool.insert({ "Pick", Pick });
    Tool.insert({ "Axe", Axe });
    Tool.insert({ "Hoe", Hoe });

    //Dir이 R인지 L인지에 따라 다르게 만들어야함
    ColPick = CreateCollision(ActorType::Tool);
    ColPick->SetScale({ 64,64 });

    ColAxe = CreateCollision(ActorType::Tool);
    ColAxe->SetScale({ 64,64 });

    ColHoe = CreateCollision(ActorType::Tool);
    ColHoe->SetScale({ 64,64 });

    CurTool = Tool["Pick"];

}

float4 Player::SetToolPos()
{
    if (Dir.c_str() == "R")
    {
        return { 100,0 };
    }
    else if (Dir.c_str() == "L")
    {
        return { -100,0 };
    }
    else if (Dir.c_str() == "U")
    {
        return { 0,-100 };
    }
    else if (Dir.c_str() == "D")
    {
        return { 0,100 };
    }

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