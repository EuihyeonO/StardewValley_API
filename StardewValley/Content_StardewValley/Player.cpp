#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Inventory.h"
#include "Crops.h"
#include "Level_Farm.h"


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
    ActingUpdate(_DeltaTime);
    
    isCollisionToPortal();

    InteractToCrops();  

    ToolChange();
    ToolPosUpdate();

    dynamic_cast<Level_Farm*>(GetLevel())->CreateCrops("Parsnip");
}

void Player::Render(float _Time)
{   
    if (GameEngineInput::IsKey("Debug") == false)
    {
        GameEngineInput::CreateKey("Debug", 'L');
    }

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
            ColPick->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 25,
            ColPick->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 25,
            ColPick->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 25,
            ColPick->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 25  );

        Rectangle(DoubleDC,
            ColBody->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() - 32,
            ColBody->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() - 64,
            ColBody->GetActorPlusPos().ix() - GetLevel()->GetCameraPos().ix() + 32,
            ColBody->GetActorPlusPos().iy() - GetLevel()->GetCameraPos().iy() + 64  );
    }


    
}
