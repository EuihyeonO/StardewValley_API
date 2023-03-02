#include "House.h"
#include "ContentsEnum.h"
#include "ContentsCore.h"
#include "Player.h"
#include "Level_Farm.h"
#include "Level_Mine.h"
#include "globalValue.h"

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

    house = CreateRender("House.bmp", 0);
    house->SetScaleToImage();

    BedCollision = CreateCollision(ActorType::Bed);
    BedCollision->SetScale({ 10, 128 });
    BedCollision->SetPosition({ 290,200 });

    houseLayer = CreateRender("HouseLayer.bmp", 100);
    houseLayer->SetScaleToImage();

    BlackMap = CreateRender("BlackMap.bmp", 1000);
    BlackMap->SetScaleToImage();
    BlackMap->SetAlpha(0);

    PortalToFarm = CreateCollision(ActorType::Portal);
    PortalToFarm->SetScale({ 60, 20 });
    PortalToFarm->SetPosition({ -165, 350 });
}

void House::Update(float _DeltaTime) 
{
    ContentsCore::SetNextMap(isCollision_PortalToPlayer());  
    DoSleep(_DeltaTime);
    Sleep(_DeltaTime);

    FadeInAndOut(_DeltaTime);
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

        Rectangle(_hdc, BedCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 5,
            BedCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 64,
            BedCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 5,
            BedCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 64);

        Rectangle(_hdc, BedCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 5,
            BedCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 64,
            BedCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 5,
            BedCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 64);
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
                BlackMap->SetPosition(-GetPos() + BlackMap->GetScale().half() + GetLevel()->GetCameraPos());
                isFading = 1;
                alpha = 0;
                Player::GetPlayer()->PlayerStop();
                Player::ChangePlayerIdle("D");
                PortalToFarm->Off();
            }
        }
    }
    return "Default";
}


void House::Sleep(float _DeltaTime)
{
    if (isSleep == true)
    {
        if (alphacount == 1 && alpha > 0)
        {
            alpha -= _DeltaTime * 100;
            BlackMap->SetAlpha(static_cast<int>(alpha));
        }
        else if (alphacount == 1 && alpha <= 0)
        {
            isSleep = false;
            alphacount = 0;
            alpha = 0;
        }
        else if (alpha < 255) {

            alpha += _DeltaTime * 50;
            BlackMap->SetAlpha(static_cast<int>(alpha));
        }
        else if (alpha >= 255)
        {
            alphacount = 1;
            globalValue::DayPlus();
        }
    }
}

void House::DoSleep(float _DeltaTime)
{
    if (true == BedCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Player) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if (GameEngineInput::IsDown("KeyInteract") == true)
        {     
            isSleep = true;
            Level_Farm::Grow_Up();
            Level_Mine::DeleteTile();
            Level_Mine::SetTileObject();
            Player::GetPlayer()->PlayerStop();
        }
    }
}


void House::FadeInAndOut(float _DeltaTime)
{
    if (isFading == 1 && alpha < 255)
    {
        BlackMap->SetAlpha(static_cast<int>(alpha));
        alpha += _DeltaTime * 250;
        Player::GetPlayer()->PlayerStop();
    }
    else if (isFading == 1 && alpha >= 255)
    {
        isFading = 0;
        Player::GetPlayer()->PlayerStopOff();
        ContentsCore::SetNextMap("Farm");
    }
    else if (isFading == 2 && alpha > 0)
    {
        Player::ChangePlayerIdle("U");
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

void House::PortalFarmOn()
{
    PortalToFarm->On();
}

void House::SetIsFading(int _num)
{
    isFading = _num;
    alpha = 255;
}