#include "Road.h"
#include "ContentsEnum.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatForm/GameEngineInput.h>
#include <GameEnginePlatForm/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>

Road::Road()
{
}

Road::~Road()
{
}

void Road::Start() 
{
    GameEngineRender* Road = CreateRender("Road.bmp", 0);
    GameEngineRender* RoadLayer = CreateRender("RoadLayer.bmp", 100);
    Road->SetScaleToImage();
    RoadLayer->SetScaleToImage();

    PortalToFarm = CreateCollision(ActorType::Portal);
    PortalToFarm->SetScale({ 50, 100 });
    PortalToFarm->SetPosition({ -940, 457 });

    GameEngineRender* Pierre = CreateRender("Pierre.bmp", 50);
    Pierre->SetScaleToImage();
    Pierre->SetPosition({ 470, -100 });

    SetPos({ 960, 823 });
}
void Road::Update(float _DeltaTime) 
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());
}
void Road::Render(float _Time) 
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

        Rectangle(_hdc, PortalToFarm->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 25,
            PortalToFarm->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 50,
            PortalToFarm->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 25,
            PortalToFarm->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 50);
    }
}


std::string Road::isCollision_PortalToPlayer()
{
    if (PortalToFarm != nullptr)
    {
        std::vector<GameEngineCollision*> Collisions;

        if (true == PortalToFarm->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                return "Farm";
            }
        }
    }
    return "Default";
}
