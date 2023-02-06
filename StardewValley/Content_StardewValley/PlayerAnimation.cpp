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

void Player::CreateAllAnimation()
{
    // 상하좌우 기본 움직임
    std::vector<int> DIdle(1);
    DIdle = { 0 };

    //아래쪽 기반 움직임
    std::vector<int> DMove(8);
    DMove = { 0, 1, 18, 1, 0, 2, 19, 2 };
    std::vector<float> DMoveFrame(8);
    DMoveFrame = { 0.09f, 0.06f, 0.12f, 0.06f, 0.09f, 0.06f, 0.12f, 0.06f };

    std::vector<int> DHeavyTool(6);
    DHeavyTool = { 66, 67, 68, 69, 70, 99 };
    std::vector<float> DHeavyToolFrame(6);
    DHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 100.0f };

    //오른쪽 기반 움직임
    std::vector<int> RIdle(1);
    RIdle = { 6 };
    std::vector<int> RMove(6);
    RMove = { 6, 21, 17, 6, 20, 11 };
    std::vector<float> RMoveFrame(6);
    RMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> RHeavyTool(5);
    RHeavyTool = { 48, 49, 50, 51, 52, 99 };
    std::vector<float> RHeavyToolFrame(6);
    RHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    //위쪽 기반 움직임
    std::vector<int> UIdle(1);
    UIdle = { 12 };
    std::vector<int> UMove(8);
    UMove = { 12, 13, 22, 13, 12, 14, 23, 14 };
    std::vector<float> UMoveFrame(8);
    UMoveFrame = { 0.09f, 0.06f, 0.12f, 0.06f, 0.09f, 0.06f, 0.12f, 0.06f };

    std::vector<int> UHeavyTool(6);
    UHeavyTool = { 36, 37, 38, 63, 62, 99 };
    std::vector<float> UHeavyToolFrame(6);
    UHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    //왼쪽 기반 움직임
    std::vector<int> LIdle(1);
    LIdle = { 11 };
    std::vector<int> LMove(6);
    LMove = { 11, 20, 12, 11, 21, 6 };
    std::vector<float> LMoveFrame(6);
    LMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> LHeavyTool(5);
    LHeavyTool = { 53, 52, 51, 50, 49, 99 };
    std::vector<float> LHeavyToolFrame(6);
    LHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.075f };

    CreatePlayerAnimation("DIdle", DIdle, { 1.0f });
    CreatePlayerAnimation("DMove", DMove, DMoveFrame);
    CreatePlayerAnimation("DHeavyTool", DHeavyTool, DHeavyToolFrame);

    CreatePlayerAnimation("RIdle", RIdle, { 1.0f });
    CreatePlayerAnimation("RMove", RMove, RMoveFrame);
    CreatePlayerAnimation("RHeavyTool", RHeavyTool, RHeavyToolFrame);

    CreatePlayerAnimation("UIdle", UIdle, { 1.0f });
    CreatePlayerAnimation("UMove", UMove, UMoveFrame);
    CreatePlayerAnimation("UHeavyTool", UHeavyTool, UHeavyToolFrame);

    CreatePlayerAnimation("LIdle", LIdle, { 1.0f }, Act::Left);
    CreatePlayerAnimation("LMove", LMove, LMoveFrame, Act::Left);
    CreatePlayerAnimation("LHeavyTool", LHeavyTool, LHeavyToolFrame, Act::Left);


    //도구 애니메이션
    std::vector<int> _RHeavyTool(5);
    _RHeavyTool = { 0, 1, 2, 3, 4, 5 };
    std::vector<float> _RHeavyToolFrame(5);
    _RHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 0.075f };

    std::vector<int> _LHeavyTool(5);
    _LHeavyTool = { 5, 4, 3, 2, 1, 0 };
    std::vector<float> _LHeavyToolFrame(5);
    _LHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 0.075f };

    std::vector<int> _DHeavyTool(6);
    _DHeavyTool = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _DHeavyToolFrame(6);
    _DHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 100.0f };

    std::vector<int> _UHeavyTool(6);
    _UHeavyTool = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _UHeavyToolFrame(6);
    _UHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    Tool["Pick"]->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Pick.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Pick"]->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Pick.bmp",.FrameIndex = {0} });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Axe.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Axe.bmp",.FrameIndex = {0} });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Hoe.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Hoe.bmp",.FrameIndex = {0} });

    Tool["Pick"]->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LPick.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Pick"]->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LPick.bmp",.FrameIndex = {0} });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LAxe.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LAxe.bmp",.FrameIndex = {0} });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LHoe.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LHoe.bmp",.FrameIndex = {0} });
  
    Tool["Pick"]->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DPick.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Pick"]->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DPick.bmp",.FrameIndex = {4} });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DAxe.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DAxe.bmp",.FrameIndex = {4} });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DHoe.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DHoe.bmp",.FrameIndex = {4} });

    Tool["Pick"]->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UPick.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Pick"]->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UPick.bmp",.FrameIndex = {4} });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UAxe.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Axe"]->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UAxe.bmp",.FrameIndex = {4} });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UHoe.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Hoe"]->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UHoe.bmp",.FrameIndex = {4} });

    //최초 애니메이션 설정
    PlayerRender->ChangeAnimation("DIdle");

    Tool["Pick"]->ChangeAnimation("RIdle");
    Tool["Axe"]->ChangeAnimation("RIdle");
    Tool["Hoe"]->ChangeAnimation("RIdle");

    Tool["Pick"]->Off();
    Tool["Axe"]->Off();
    Tool["Hoe"]->Off();
}


void Player::CreatePlayerAnimation(std::string_view State, std::vector<int> _FrameIndex, std::vector<float> _Frametime, int Dir)
{
    if (Dir == 0)
    {
        PlayerRender->CreateAnimation({ .AnimationName = State, .ImageName = "Player.bmp",.FrameIndex = _FrameIndex,.FrameTime = _Frametime });
    }
    else if (Dir == Act::Left)
    {
        PlayerRender->CreateAnimation({ .AnimationName = State, .ImageName = "PlayerLeft.bmp",.FrameIndex = _FrameIndex,.FrameTime = _Frametime });
    }
}

void Player::ChangePlayerAnimation(std::string_view _Act)
{
    PlayerRender->ChangeAnimation(_Act);
}
