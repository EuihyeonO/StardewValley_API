#include "House.h"
#include "ContentsEnum.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>

House::House()
{    
}

House::~House()
{
}

void House::Start()
{
    SetPos({ 640,384 });

    GameEngineRender* House = CreateRender("House.bmp", 0);
    House->SetScaleToImage();

    PortalToFarm = CreateCollision(ActorType::Portal);
    PortalToFarm->SetScale({ 60, 20 });
    PortalToFarm->SetPosition({ -165, 350 });
}

void House::Update(float _DeltaTime) 
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());
}

void House::Render(float _Time) 
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

    if (isDebug == true)
    {
        HDC _hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

        Rectangle(_hdc, PortalToFarm->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 30,
            PortalToFarm->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 10,
            PortalToFarm->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 30,
            PortalToFarm->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 10);
    }
}

std::string House::isCollision_PortalToPlayer()
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
