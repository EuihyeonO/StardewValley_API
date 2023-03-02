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
    std::vector<int> GetItem(2);
    GetItem = { 69, 69 };
    std::vector<float> GetItemFrame(2);
    GetItemFrame = { 1.0f, 0.1f };

    //아래쪽 기반 움직임
    std::vector<int> DIdle(1);
    DIdle = { 0 };

    std::vector<int> DMove(8);
    DMove = { 0, 1, 2, 3, 4, 5, 6, 7 };
    std::vector<float> DMoveFrame(8);
    DMoveFrame = { 0.09f, 0.06f, 0.12f, 0.06f, 0.09f, 0.06f, 0.12f, 0.06f };

    std::vector<int> DHeavyTool(6);
    DHeavyTool = { 30, 31, 32, 33, 34, 34 };
    std::vector<float> DHeavyToolFrame(6);
    DHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 100.0f };

    std::vector<int> DWatering(4);
    DWatering = { 48, 49, 50, 50};
    std::vector<float> DWateringFrame(4);
    DWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f};

    std::vector<int> DHarvesting(5);
    DHarvesting = { 66, 67, 68, 69, 69 };
    std::vector<float> DHarvestingFrame(5);
    DHarvestingFrame = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

    std::vector<int> DAttack(7);
    DAttack = { 84, 85, 86, 87, 88, 89, 89 };
    std::vector<float> DAttackFrame(7);
    DAttackFrame = { 0.055f, 0.045f, 0.025f, 0.025f, 0.025f, 0.1f };

    //오른쪽 기반 움직임
    std::vector<int> RIdle(1);
    RIdle = { 12 };

    std::vector<int> RMove(6);
    RMove = { 12, 13, 14, 15, 16, 17 };
    std::vector<float> RMoveFrame(6);
    RMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> RHeavyTool(5);
    RHeavyTool = { 36, 37, 38, 39, 40, 40 };
    std::vector<float> RHeavyToolFrame(6);
    RHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    std::vector<int> RWatering(4);
    RWatering = { 54, 55, 56, 56 };
    std::vector<float> RWateringFrame(4);
    RWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };

    std::vector<int> RHarvesting(5);
    RHarvesting = { 72, 73, 74, 75, 75 };
    std::vector<float> RHarvestingFrame(5);
    RHarvestingFrame = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

    std::vector<int> RAttack(7);
    RAttack = { 90, 91, 92, 93, 94, 95, 95 };
    std::vector<float> RAttackFrame(7);
    RAttackFrame = { 0.055f, 0.045f, 0.025f, 0.025f, 0.025f, 0.1f };

    //위쪽 기반 움직임
    std::vector<int> UIdle(1);
    UIdle = { 18 };
    std::vector<int> UMove(8);
    UMove = { 18, 19, 20, 21, 22, 23, 24, 25 };
    std::vector<float> UMoveFrame(8);
    UMoveFrame = { 0.09f, 0.06f, 0.12f, 0.06f, 0.09f, 0.06f, 0.12f, 0.06f };

    std::vector<int> UHeavyTool(6);
    UHeavyTool = { 42, 43, 44, 45, 46, 46 };
    std::vector<float> UHeavyToolFrame(6);
    UHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    std::vector<int> UWatering(4);
    UWatering = { 60, 61, 62, 62 };
    std::vector<float> UWateringFrame(4);
    UWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };

    std::vector<int> UHarvesting(5);
    UHarvesting = { 78, 79, 80, 81, 81 };
    std::vector<float> UHarvestingFrame(5);
    UHarvestingFrame = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

    std::vector<int> UAttack(7);
    UAttack = { 96, 97, 98, 99, 100, 101, 101 };
    std::vector<float> UAttackFrame(7);
    UAttackFrame = { 0.055f, 0.045f, 0.025f, 0.025f, 0.025f, 0.1f, 0.025f };


    //왼쪽 기반 움직임
    std::vector<int> LIdle(1);
    LIdle = { 0 };
    std::vector<int> LMove(6);
    LMove = { 0, 1, 2, 3, 4, 5 };
    std::vector<float> LMoveFrame(6);
    LMoveFrame = { 0.09f, 0.14f, 0.1f, 0.09f, 0.14f, 0.10f };

    std::vector<int> LHeavyTool(5);
    LHeavyTool = { 6, 7, 8, 9, 10, 10 };
    std::vector<float> LHeavyToolFrame(6);
    LHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.075f };

    std::vector<int> LWatering(4);
    LWatering = { 12, 13, 14, 14 };
    std::vector<float> LWateringFrame(4);
    LWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };

    std::vector<int> LHarvesting(5);
    LHarvesting = { 18, 19, 20, 21, 21 };
    std::vector<float> LHarvestingFrame(5);
    LHarvestingFrame = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

    std::vector<int> LAttack(7);
    LAttack = { 24, 25, 26, 27, 28, 29, 29 };
    std::vector<float> LAttackFrame(7);
    LAttackFrame = { 0.055f, 0.045f, 0.025f, 0.025f, 0.025f, 0.1f };

    CreatePlayerAnimation("GetItem", GetItem, GetItemFrame);

    CreatePlayerAnimation("DIdle", DIdle, { 1.0f });
    CreatePlayerAnimation("DMove", DMove, DMoveFrame);
    CreatePlayerAnimation("DHeavyTool", DHeavyTool, DHeavyToolFrame);
    CreatePlayerAnimation("DWatering", DWatering, DWateringFrame);
    CreatePlayerAnimation("DHarvesting", DHarvesting, DHarvestingFrame);
    CreatePlayerAnimation("DAttack", DAttack, DAttackFrame);

    CreatePlayerAnimation("RIdle", RIdle, { 1.0f });
    CreatePlayerAnimation("RMove", RMove, RMoveFrame);
    CreatePlayerAnimation("RHeavyTool", RHeavyTool, RHeavyToolFrame);
    CreatePlayerAnimation("RWatering", RWatering, RWateringFrame);
    CreatePlayerAnimation("RHarvesting", RHarvesting, RHarvestingFrame);
    CreatePlayerAnimation("RAttack", RAttack, RAttackFrame);

    CreatePlayerAnimation("UIdle", UIdle, { 1.0f });
    CreatePlayerAnimation("UMove", UMove, UMoveFrame);
    CreatePlayerAnimation("UHeavyTool", UHeavyTool, UHeavyToolFrame);
    CreatePlayerAnimation("UWatering", UWatering, UWateringFrame);
    CreatePlayerAnimation("UHarvesting", UHarvesting, UHarvestingFrame);
    CreatePlayerAnimation("UAttack", UAttack, UAttackFrame);

    CreatePlayerAnimation("LIdle", LIdle, { 1.0f }, Act::Left);
    CreatePlayerAnimation("LMove", LMove, LMoveFrame, Act::Left);
    CreatePlayerAnimation("LHeavyTool", LHeavyTool, LHeavyToolFrame, Act::Left);
    CreatePlayerAnimation("LWatering", LWatering, LWateringFrame, Act::Left); 
    CreatePlayerAnimation("LHarvesting", LHarvesting, LHarvestingFrame, Act::Left);
    CreatePlayerAnimation("LAttack", LAttack, LAttackFrame, Act::Left);
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

void Player::SetPlayerAlpha(int _Alpha)
{
    MyPlayer->PlayerRender->SetAlpha(_Alpha);
}

