#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineMath.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Farm.h"
#include "Inventory.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "globalValue.h"
#include "Crops.h"


void Player::InitPlayer()
{
    PlayerRender = CreateRender(2);
    PlayerRender->SetScale({ 64, 128 });

    ColBody = CreateCollision(ActorType::Player);
    ColBody->SetScale({ 64,128 });
    ColBody->SetPosition({ 0,0 });
}


void Player::SetDir()
{
    if (true == GameEngineInput::IsPress("DMove"))
    {
        Dir = "D";
    }
    else if (true == GameEngineInput::IsPress("UMove"))
    {
        Dir = "U";
    }
    else if (true == GameEngineInput::IsPress("LMove"))
    {
        Dir = "L";
    }
    else if (true == GameEngineInput::IsPress("RMove"))
    {
        Dir = "R";
    }
}


void Player::ActingUpdate(float _DeltaTime)
{

    if(isInteract() == true)
    {
        return;
    }   

    int Act = GetKeyInput();

    switch (Act)
    {
    case Act::Idle:
        Idle();
        break;
    case Act::Move:
        Move(_DeltaTime);
        break;
    case Act::Interact:
        Interact(_DeltaTime);
        break;
    case Act::Menu:
        Inventory::GetInventory()->OpenInventory();
        break;
    case Act::ChangeItem:
        Inventory::ChangeSelectedItem();
        break;
    }
}

void Player::Idle()
{
    ChangePlayerAnimation(Dir + "Idle");
}


void Player::Move(float _DeltaTime)
{  
    float4 NextPos = GetPos();
    float4 NextCameraPos = GetLevel()->GetCameraPos();
    float4 MoveDir = { 0,0 };
    
    GameEngineImage* ColMap = nullptr;

    if (GetOwner()->GetName() == "Farm")
    {
        ColMap = GameEngineResources::GetInst().ImageFind("FarmC.bmp");
    }
    else if (GetOwner()->GetName() == "House")
    {
        ColMap = GameEngineResources::GetInst().ImageFind("HouseC.bmp");
    }

    //아래쪽 기반 이동
    if (true == GameEngineInput::IsPress("DMove"))
    {
        if (true == GameEngineInput::IsPress("LMove"))
        {            
            MoveDir += float4::Left;
            ChangePlayerAnimation("LMove");
        }

        else if (true == GameEngineInput::IsPress("RMove"))
        {
            MoveDir += float4::Right;
            ChangePlayerAnimation("RMove");
        }

        else
        {
            ChangePlayerAnimation("DMove");
        }

        MoveDir += float4::Down;
    }

    //위쪽기반 이동
    else if (true == GameEngineInput::IsPress("UMove"))
    {
        if (true == GameEngineInput::IsPress("LMove"))
        {
            MoveDir += float4::Left;
            ChangePlayerAnimation("LMove");
        }

        else if (true == GameEngineInput::IsPress("RMove"))
        {
            MoveDir += float4::Right;
            ChangePlayerAnimation("RMove");
        }

        else
        {
            ChangePlayerAnimation("UMove");
        }

        MoveDir += float4::Up;   
    }

    //우측이동
    else if (true == GameEngineInput::IsPress("RMove"))
    {
        MoveDir += float4::Right;
        ChangePlayerAnimation("RMove");
    }  

    //좌측이동
    else if (true == GameEngineInput::IsPress("LMove"))
    {
        MoveDir += float4::Left;
        ChangePlayerAnimation("LMove");
    }

    //벽에 닿지 않는다면 이동하게 될 값
    NextPos += MoveDir * MoveSpeed * _DeltaTime;
    NextCameraPos += MoveDir * MoveSpeed * _DeltaTime;

    // 실제로 위치를 이동 (x, y중 한 쪽만 막혀있을 경우에도 움직일 수 있게 로직변경이 필요
    if (nullptr != ColMap && RGB(0, 0, 0) != ColMap->GetPixelColor({NextPos.x, NextPos.y}, RGB(0, 0, 0)))
    {
        SetPos(NextPos);  

        // 카메라가 멈추는 좌표를 맵의 크기에 따라 가변적이게 설정해야함
        if (NextPos.x >= globalValue::GetcameraLimitPos().x + GameEngineWindow::GetScreenSize().half().x)
        {
            NextCameraPos.x = globalValue::GetcameraLimitPos().x;
        }
        if (NextPos.x <= GameEngineWindow::GetScreenSize().half().x)
        {
            NextCameraPos.x = 0;
        }
        if (NextPos.y >= globalValue::GetcameraLimitPos().y + GameEngineWindow::GetScreenSize().half().y)
        {
            NextCameraPos.y = globalValue::GetcameraLimitPos().y;
        }
        if (NextPos.y <= GameEngineWindow::GetScreenSize().half().y)
        {
            NextCameraPos.y = 0;
        }

         GetLevel()->SetCameraPos(NextCameraPos);
    }

    SetDir();
}

void Player::Interact(float _DeltaTime)
{


    if (Dir[0] == 'R' || Dir[0] == 'L')
    {
        CurTool->SetScale({ 250, 250 });
    }
    else if (Dir[0] == 'D' || Dir[0] == 'U')
    {
        CurTool->SetScale({ 64, 250 });
    }

    CurTool->On();

    if (CurTool->IsUpdate() == true && CurTool != Tool["Watering"])
    {
        CurTool->ChangeAnimation("DIdle");
        CurTool->ChangeAnimation(Dir + "HeavyTool");
        ChangePlayerAnimation(Dir + "HeavyTool");
    }
    else if (CurTool->IsUpdate() == true && CurTool == Tool["Watering"])
    {
        CurTool->ChangeAnimation("DIdle");
        CurTool->ChangeAnimation(Dir + "Watering");  

        ChangePlayerAnimation(Dir + "Watering");
    }
}


bool Player::isInteract()
{
    if (CurTool->IsUpdate() == false)
    {
        return false;
    }
    
    if (PlayerRender->IsAnimationEnd() == true)
    {
        CurTool->Off();
        return false;
    }

    return true;

}


void Player::InteractToCrops()
{

    if (CurTool != Tool["Watering"])
    {
        return;
    }

    ColWatering->SetPosition(SetToolPos());

    if (CurTool->IsUpdate() == true)
    {
        std::vector<GameEngineCollision*> Collisions;
        if (true == ColWatering->Collision({ .TargetGroup = static_cast<int>(ActorType::Crops) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                GameEngineActor* ColActor = Collisions[i]->GetActor();
                dynamic_cast<Crops*>(ColActor)->GrowUp();
                dynamic_cast<Crops*>(ColActor)->CollisionOff();
            }
        }
    }
    else
    {
        for (int i = 0; i < Level_Farm::GetCropList().size(); i++)
        {
            if (Level_Farm::GetCropList()[i]->IsCollisionUpdate() == false && Level_Farm::GetCropList()[i]->isSet() == true)
            {
                Level_Farm::GetCropList()[i]->CollisionOn();
            }
        }
    }
}

void Player::ChangePlayerIdle()
{
    MyPlayer->ChangePlayerAnimation(MyPlayer->Dir + "Idle");
}