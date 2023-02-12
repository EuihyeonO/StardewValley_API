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

void Player::CreateToolAnimation()
{
    //도구 애니메이션
    std::vector<int> _RHeavyTool(5);
    _RHeavyTool = { 0, 1, 2, 3, 4, 5 };
    std::vector<float> _RHeavyToolFrame(5);
    _RHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 0.075f };

    std::vector<int> _RWatering(6);
    _RWatering = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _RWateringFrame(6);
    _RWateringFrame = { 0.075f, 0.1f, 0.15f, 0.15f, 0.2f, 0.1f };


    std::vector<int> _LHeavyTool(5);
    _LHeavyTool = { 5, 4, 3, 2, 1, 0 };
    std::vector<float> _LHeavyToolFrame(5);
    _LHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 0.075f };

    std::vector<int>  _LWatering(6);
    _LWatering = { 4, 3, 2, 1, 0, 0 };
    std::vector<float> _LWateringFrame(6);
    _LWateringFrame = { 0.075f, 0.1f, 0.15f, 0.15f, 0.2f, 0.1f };

    std::vector<int> _DHeavyTool(6);
    _DHeavyTool = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _DHeavyToolFrame(6);
    _DHeavyToolFrame = { 0.15f, 0.04f, 0.04f, 0.17f, 0.075f, 100.0f };

    std::vector<int> _DWatering(6);
    _DWatering = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _DWateringFrame(6);
    _DWateringFrame = { 0.075f, 0.1f, 0.15f, 0.15f, 0.2f, 0.1f };


    std::vector<int> _UHeavyTool(6);
    _UHeavyTool = { 0, 1, 2, 3, 4, 4 };
    std::vector<float> _UHeavyToolFrame(6);
    _UHeavyToolFrame = { 0.1f, 0.04f, 0.04f, 0.22f, 0.075f, 0.01f };

    std::vector<int> _UWatering(4);
    _UWatering = { 0, 1, 2, 2 };
    std::vector<float> _UWateringFrame(4);
    _UWateringFrame = { 0.075f, 0.1f, 0.5f, 0.1f };


    Tool["Pick"] ->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Pick.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Pick"] ->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Pick.bmp",.FrameIndex = {0} });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Axe.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Axe.bmp",.FrameIndex = {0} });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "RHeavyTool", .ImageName = "Hoe.bmp",.FrameIndex = _RHeavyTool,.FrameTime = _RHeavyToolFrame });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Hoe.bmp",.FrameIndex = {0} });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "RWatering", .ImageName = "Watering.bmp",.FrameIndex = _RWatering,.FrameTime = _RWateringFrame });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "RIdle", .ImageName = "Watering.bmp",.FrameIndex = {0} });
    
    Tool["Pick"] ->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LPick.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Pick"] ->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LPick.bmp",.FrameIndex = {0} });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LAxe.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LAxe.bmp",.FrameIndex = {0} });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "LHeavyTool", .ImageName = "LHoe.bmp",.FrameIndex = _LHeavyTool,.FrameTime = _LHeavyToolFrame });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LHoe.bmp",.FrameIndex = {0} });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "LWatering", .ImageName = "LWatering.bmp",.FrameIndex = _LWatering,.FrameTime = _LWateringFrame });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "LIdle", .ImageName = "LWatering.bmp",.FrameIndex = {0} });

    Tool["Pick"] ->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DPick.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Pick"] ->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DPick.bmp",.FrameIndex = {4} });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DAxe.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DAxe.bmp",.FrameIndex = {4} });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "DHeavyTool", .ImageName = "DHoe.bmp",.FrameIndex = _DHeavyTool,.FrameTime = _DHeavyToolFrame });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DHoe.bmp",.FrameIndex = {4} });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "DWatering", .ImageName = "DWatering.bmp",.FrameIndex = _DWatering,.FrameTime = _DWateringFrame });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "DIdle", .ImageName = "DWatering.bmp",.FrameIndex = {4} });

    Tool["Pick"] ->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UPick.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Pick"] ->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UPick.bmp",.FrameIndex = {4} });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UAxe.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Axe"] ->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UAxe.bmp",.FrameIndex = {4} });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "UHeavyTool", .ImageName = "UHoe.bmp",.FrameIndex = _UHeavyTool,.FrameTime = _UHeavyToolFrame });
    Tool["Hoe"] ->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UHoe.bmp",.FrameIndex = {4} });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "UWatering", .ImageName = "UWatering.bmp",.FrameIndex = _UWatering,.FrameTime = _UWateringFrame });
    Tool["Watering"] ->CreateAnimation({ .AnimationName = "UIdle", .ImageName = "UWatering.bmp",.FrameIndex = {4} });


    Tool["Pick"] ->ChangeAnimation("RIdle");
    Tool["Axe"] ->ChangeAnimation("RIdle");
    Tool["Hoe"] ->ChangeAnimation("RIdle");
    Tool["Watering"] ->ChangeAnimation("RIdle");

    Tool["Pick"] ->Off();
    Tool["Axe"] ->Off();
    Tool["Hoe"] ->Off();
    Tool["Watering"] ->Off();
}