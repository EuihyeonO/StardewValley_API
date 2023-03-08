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
#include "globalInterface.h"


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
    AxeCollisionUpdate();

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
            AxeCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - AxeCollision->GetScale().hx(),
            AxeCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - AxeCollision->GetScale().hy(),
            AxeCollision->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + AxeCollision->GetScale().hx(),
            AxeCollision->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + AxeCollision->GetScale().hy());

    }

    if (GameEngineInput::IsKey("MakeItem") == false)
    {
        GameEngineInput::CreateKey("MakeItem", 'K');
    }

    if (GameEngineInput::IsDown("MakeItem") == true)
    {
        for (int i = 0; i < 10; i++) 
        {
            globalInterface::CreateItemToAllInventory("IconParsnip.bmp", static_cast<int>(ItemType::Crops));
            globalInterface::CreateItemToAllInventory("IconBranch.bmp", static_cast<int>(ItemType::Etc));
        }
    }
}
