#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Inventory.h"
#include "Level_Farm.h"
#include "globalValue.h"


Player* Player::MyPlayer = nullptr;

Player::Player()
{
     MyPlayer = this;
}

Player::~Player()
{
}

void Player::Start()
{
    InitPlayer();
    InitTool();
    CreatePlayerKey();
    CreateAllAnimation();  
}

void Player::Update(float _DeltaTime)
{
    isCollidedToNPC();
    CurToolTypeUpdate();
    ToolChange();
    ToolPosUpdate();
    HitByMonster(_DeltaTime);
    HammerCollisionUpdate();

    ActingUpdate(_DeltaTime);   

    dynamic_cast<Level_Farm*>(GetLevel())->CreateCrops("Parsnip");

}

void Player::Render(float _Time)
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
        HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

        Rectangle(DoubleDC,
            ColTool->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 25,
            ColTool->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 25,
            ColTool->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 25,
            ColTool->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 25  );

        Rectangle(DoubleDC,
            ColBody->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 24,
            ColBody->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 24,
            ColBody->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 24,
            ColBody->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 24  );
    }
}
