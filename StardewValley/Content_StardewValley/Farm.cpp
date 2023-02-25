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

    BlackMap = CreateRender("BlackMap.bmp", 1000);
    BlackMap->SetScaleToImage();
    BlackMap->SetAlpha(0);

    PortalToVillage = CreateCollision(ActorType::Portal);
    PortalToVillage->SetScale({ 50, 200 });
    PortalToVillage->SetPosition({1280, 0});

    PortalToHouse = CreateCollision(ActorType::Portal);
    PortalToHouse->SetScale({ 50, 50 });
    PortalToHouse->SetPosition({ 365, -130 });

    PortalToMine = CreateCollision(ActorType::Portal);
    PortalToMine->SetScale({ 50, 50 });
    PortalToMine->SetPosition({ -540, -240 });

    Farm->SetScaleToImage();
    FarmLayer->SetScaleToImage();
}

void Farm::Update(float _DeltaTime)
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());
    FadeInAndOut(_DeltaTime);
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

        float4 Vscale = PortalToVillage->GetScale().half();
        float4 Hscale = PortalToHouse->GetScale().half();
        float4 Mscale = PortalToMine->GetScale().half();

        Rectangle(_hdc, PortalToVillage->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - Vscale.ix(),
                        PortalToVillage->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - Vscale.iy(),
                        PortalToVillage->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + Vscale.ix(),
                        PortalToVillage->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + Vscale.iy());

        Rectangle(_hdc, PortalToHouse->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - Hscale.ix(),
                        PortalToHouse->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - Hscale.iy(),
                        PortalToHouse->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + Hscale.ix(),
                        PortalToHouse->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + Hscale.iy());

        Rectangle(_hdc, PortalToMine->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - Mscale.ix(),
                        PortalToMine->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - Mscale.iy(),
                        PortalToMine->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + Mscale.ix(),
                        PortalToMine->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + Mscale.iy());

    }
}

std::string Farm::isCollision_PortalToPlayer()
{
    if(PortalToHouse != nullptr && PortalToVillage !=nullptr)
    {
        std::vector<GameEngineCollision*> Collisions;

        if (true == GameEngineInput::IsDown("KeyInteract") && true == PortalToHouse->Collision({.TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect}, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                Player::SetIsCollision(true);
                isFading = 1;
                NextMap = "House";
            }
        }

        else if (true == PortalToVillage->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                return "Road";
            }
        }

        else if (true == PortalToMine->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {                 
                isFading = 1;
                Player::GetPlayer()->PlayerStop();
                Player::ChangePlayerIdle("U");
                alpha = 0;
                PortalToMine->Off();
                NextMap = "Mine";
            }
        }

    }

    return "Default";   
}

void Farm::FadeInAndOut(float _DeltaTime)
{
    if (isFading == 1 && alpha<255)
    {
        BlackMap->SetPosition(-GetPos() + BlackMap->GetScale().half() + GetLevel()->GetCameraPos());
        BlackMap->SetAlpha(alpha);
        alpha += _DeltaTime * 250;
    }
    else if (isFading == 1 && alpha >= 255)
    {
        isFading = 0;
        Player::GetPlayer()->PlayerStopOff();
        ContentsCore::SetNextMap(NextMap);
    }  
    else if (isFading == 2 && alpha>0)
    {
        BlackMap->SetPosition(-GetPos() + BlackMap->GetScale().half() + GetLevel()->GetCameraPos());
        Player::ChangePlayerIdle("D");
        BlackMap->SetAlpha(alpha);
        alpha -= _DeltaTime * 250;
    }
    else if (alpha <= 0)
    {
        alpha = 0;
        isFading = 0;
        Player::GetPlayer()->PlayerStopOff();
    }
}

void Farm::PortalMineOn()
{
    PortalToMine->On();
}

void Farm::SetIsFading(int _num)
{
    isFading = _num;
    alpha = 255;
}