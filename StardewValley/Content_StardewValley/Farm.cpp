#include "Farm.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineResources.h>

#include <vector>

Farm::Farm()
{
}

Farm::~Farm()
{
}

void Farm::Start()
{
    SetPos({ 1300,513 });

    GameEngineRender* Farm = CreateRender("Farm.bmp", 0);
    GameEngineRender* FarmLayer = CreateRender("FarmLayer.bmp", 2);

    Farm->SetScaleToImage();
    FarmLayer->SetScaleToImage();
}

void Farm::Update(float _DeltaTime)
{
}

void Farm::Render(float _Time)
{

}