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
    DHeavyTool = { 66, 67, 68, 69, 70, 70 };
    std::vector<float> DHeavyToolFrame(6);
    DHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 100.0f };

    std::vector<int> DWatering(4);
    DWatering = { 54, 55, 25, 25};
    std::vector<float> DWateringFrame(4);
    DWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f};

    //오른쪽 기반 움직임
    std::vector<int> RIdle(1);
    RIdle = { 6 };
    std::vector<int> RMove(6);
    RMove = { 6, 21, 17, 6, 20, 11 };
    std::vector<float> RMoveFrame(6);
    RMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> RHeavyTool(5);
    RHeavyTool = { 48, 49, 50, 51, 52, 52 };
    std::vector<float> RHeavyToolFrame(6);
    RHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    std::vector<int> RWatering(4);
    RWatering = { 58, 59, 45, 45 };
    std::vector<float> RWateringFrame(4);
    RWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };

    //위쪽 기반 움직임
    std::vector<int> UIdle(1);
    UIdle = { 12 };
    std::vector<int> UMove(8);
    UMove = { 12, 13, 22, 13, 12, 14, 23, 14 };
    std::vector<float> UMoveFrame(8);
    UMoveFrame = { 0.09f, 0.06f, 0.12f, 0.06f, 0.09f, 0.06f, 0.12f, 0.06f };

    std::vector<int> UHeavyTool(6);
    UHeavyTool = { 36, 37, 38, 63, 62, 62 };
    std::vector<float> UHeavyToolFrame(6);
    UHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    std::vector<int> UWatering(4);
    UWatering = { 62, 63, 46, 46 };
    std::vector<float> UWateringFrame(4);
    UWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };
    //왼쪽 기반 움직임
    std::vector<int> LIdle(1);
    LIdle = { 11 };
    std::vector<int> LMove(6);
    LMove = { 11, 20, 12, 11, 21, 6 };
    std::vector<float> LMoveFrame(6);
    LMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> LHeavyTool(5);
    LHeavyTool = { 53, 52, 51, 50, 49, 49 };
    std::vector<float> LHeavyToolFrame(6);
    LHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.075f };

    std::vector<int> LWatering(4);
    LWatering = { 54, 55, 44, 44 };
    std::vector<float> LWateringFrame(4);
    LWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };

    CreatePlayerAnimation("DIdle", DIdle, { 1.0f });
    CreatePlayerAnimation("DMove", DMove, DMoveFrame);
    CreatePlayerAnimation("DHeavyTool", DHeavyTool, DHeavyToolFrame);
    CreatePlayerAnimation("DWatering", DWatering, DWateringFrame);

    CreatePlayerAnimation("RIdle", RIdle, { 1.0f });
    CreatePlayerAnimation("RMove", RMove, RMoveFrame);
    CreatePlayerAnimation("RHeavyTool", RHeavyTool, RHeavyToolFrame);
    CreatePlayerAnimation("RWatering", RWatering, RWateringFrame);

    CreatePlayerAnimation("UIdle", UIdle, { 1.0f });
    CreatePlayerAnimation("UMove", UMove, UMoveFrame);
    CreatePlayerAnimation("UHeavyTool", UHeavyTool, UHeavyToolFrame);
    CreatePlayerAnimation("UWatering", UWatering, UWateringFrame);

    CreatePlayerAnimation("LIdle", LIdle, { 1.0f }, Act::Left);
    CreatePlayerAnimation("LMove", LMove, LMoveFrame, Act::Left);
    CreatePlayerAnimation("LHeavyTool", LHeavyTool, LHeavyToolFrame, Act::Left);
    CreatePlayerAnimation("LWatering", LWatering, LWateringFrame, Act::Left);

    CreateToolAnimation();
    //최초 애니메이션 설정
    PlayerRender->ChangeAnimation("DIdle");
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
