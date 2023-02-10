#include "Farm.h"
#include "Player.h"
#include "ContentsEnum.h"

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
    SetPos({ 1280,512 });

    GameEngineRender* Farm = CreateRender("Farm.bmp", 0);
    GameEngineRender* FarmLayer = CreateRender("FarmLayer.bmp", 2);

    PortalToVillage = CreateCollision(ActorType::Portal);
    PortalToVillage->SetScale({ 50, 200 });
    PortalToVillage->SetPosition({1280, 0});

    Farm->SetScaleToImage();
    FarmLayer->SetScaleToImage();
}

void Farm::Update(float _DeltaTime)
{
}

void Farm::Render(float _Time)
{
    if (true == GameEngineInput::IsPress("Debug"))
    {
        if (GameEngineInput::IsDown("Debug"))
        {
            if (isDebug == false)
            {
                isDebug = true;
            }
            else
            {
                isDebug = false;
            }
        }     
    }

    if (isDebug == true)
    {
        HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
        Rectangle(_hdc, PortalToVillage->GetActorPlusPos().x - GetLevel()->GetCameraPos().x - 25.0f,
                        PortalToVillage->GetActorPlusPos().y - GetLevel()->GetCameraPos().y - 100.0f,
                        PortalToVillage->GetActorPlusPos().x - GetLevel()->GetCameraPos().x + 25.0f,
                        PortalToVillage->GetActorPlusPos().y - GetLevel()->GetCameraPos().y + 100.0f);
    }
}