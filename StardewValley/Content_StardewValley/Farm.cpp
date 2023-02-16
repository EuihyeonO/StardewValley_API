#include "Farm.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineResources.h>

#include <vector>
#include <string_view>

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
    GameEngineRender* FarmLayer = CreateRender("FarmLayer.bmp", 100);

    PortalToVillage = CreateCollision(ActorType::Portal);
    PortalToVillage->SetScale({ 50, 200 });
    PortalToVillage->SetPosition({1280, 0});

    PortalToHouse = CreateCollision(ActorType::Portal);
    PortalToHouse->SetScale({ 50, 50 });
    PortalToHouse->SetPosition({ 365, -150 });


    Farm->SetScaleToImage();
    FarmLayer->SetScaleToImage();
}

void Farm::Update(float _DeltaTime)
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());
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

        Rectangle(_hdc, PortalToVillage->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 25,
                        PortalToVillage->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 100,
                        PortalToVillage->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 25,
                        PortalToVillage->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 100);

        Rectangle(_hdc, PortalToHouse->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 25,
                        PortalToHouse->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 25,
                        PortalToHouse->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 25,
                        PortalToHouse->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 25);
    }
}

std::string Farm::isCollision_PortalToPlayer()
{
    if(PortalToHouse != nullptr && PortalToVillage !=nullptr)
    {
        std::vector<GameEngineCollision*> Collisions;

        if (true == GameEngineInput::IsDown("Interact") && true == PortalToHouse->Collision({.TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect}, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                Player::SetIsCollision(true);
                return "House";
            }
        }

        else if (true == PortalToVillage->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                return "Road";
            }
        }
    }

    return "Default";   
}
