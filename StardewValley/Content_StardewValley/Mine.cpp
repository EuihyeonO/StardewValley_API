#include "Mine.h"
#include "ContentsEnum.h"
#include "ContentsCore.h"
#include "Player.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <string>

Mine::Mine()
{
}

Mine::~Mine()
{
}

void Mine::Start()
{
    SetPos({ 640,384 });

    GameEngineRender* Mine = CreateRender("Mine.BMP", 0);
    GameEngineRender* MineLayer = CreateRender("MineLayer.BMP", 100);

    Mine->SetScaleToImage();
    MineLayer->SetScaleToImage();

    BlackMap = CreateRender("BlackMap.bmp", 1000);
    BlackMap->SetScaleToImage();
    BlackMap->SetAlpha(0);

    PortalToFarm = CreateCollision(ActorType::Portal);
    PortalToFarm->SetScale({ 20, 50 });
    PortalToFarm->SetPosition({ 0, -340 });
}

void Mine::Update(float _DeltaTime)
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());
    FadeInAndOut(_DeltaTime);
}

void Mine::Render(float _Time)
{
    if (GameEngineInput::IsDown("Debug") == true)
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

    HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
    if (isDebug == true) 
    {
        Rectangle(hdc, PortalToFarm->GetActorPlusPos().ix() - 10, PortalToFarm->GetActorPlusPos().iy() - 25, PortalToFarm->GetActorPlusPos().ix() + 10, PortalToFarm->GetActorPlusPos().iy() + 25);
    }
}

std::string Mine::isCollision_PortalToPlayer()
{
    if (PortalToFarm != nullptr)
    {

        if (true == PortalToFarm->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
        {
            if (GameEngineInput::IsDown("KeyInteract") == true)
            {
                isFading = 1;
                Player::GetPlayer()->PlayerStop();
                Player::ChangePlayerIdle("U");
                alpha = 0;
                PortalToFarm->Off();
            }
        }
    }
    return "Default";
}

void Mine::FadeInAndOut(float _DeltaTime)
{
    if (isFading == 1 && alpha < 255)
    {
        BlackMap->SetPosition(-GetPos() + BlackMap->GetScale().half() + GetLevel()->GetCameraPos());
        BlackMap->SetAlpha(static_cast<int>(alpha));
        alpha += _DeltaTime * 250;
    }
    else if (isFading == 1 && alpha >= 255)
    {
        isFading = 0;

        Player::GetPlayer()->PlayerStopOff();
        ContentsCore::SetNextMap("Farm");
    }
    else if (isFading == 2 && alpha > 0)
    {
        BlackMap->SetPosition(-GetPos() + BlackMap->GetScale().half() + GetLevel()->GetCameraPos());
        Player::ChangePlayerIdle("D");
        BlackMap->SetAlpha(static_cast<int>(alpha));
        alpha -= _DeltaTime * 250;
    }
    else if (alpha <= 0)
    {
        alpha = 0;
        isFading = 0;

        Player::GetPlayer()->PlayerStopOff();
    }
}

void Mine::PortalFarmOn()
{
    PortalToFarm->On();
}

void Mine::SetIsFading(int _num)
{
    isFading = _num;
    alpha = 255;
}