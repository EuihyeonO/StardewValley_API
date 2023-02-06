#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Farm.h"
#include "GlobalFunction.h"
#include "Inventory.h"



void Player::InitPlayer()
{
    PlayerRender = CreateRender(2);

    PlayerRender->SetScale({ 64, 128 });

    SetPos({ 1665,600 });

    GetLevel()->SetCameraPos({ GetPos().x - 640, GetPos().y -360});

}

void Player::InitTool()
{  
    Pick = CreateRender(2);
    Axe = CreateRender(2);
    Hoe = CreateRender(2); 

    Tool.insert({"Pick", Pick });
    Tool.insert({"Axe", Axe});
    Tool.insert({"Hoe", Hoe });

    CurTool = Tool["Pick"];   

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

int Player::GetKeyInput()
{
    if (Inventory::GetInventoryRender()->IsUpdate() == true)
    {

        if (true == GameEngineInput::IsDown("Menu"))
        {
            return Act::Menu;
        }
        
        return Act::Idle;
    }

    else
    {
        if (true == GameEngineInput::IsDown("Interact"))
        {
            return Act::Interact;
        }

        else if (true == GameEngineInput::IsDown("ToolChange"))
        {
            return Act::ToolChange;
        }
        
        else if (true == GameEngineInput::IsDown("Menu"))
        {
            return Act::Menu;
        }

        else if (true == GameEngineInput::IsPress("LMove") ||
                 true == GameEngineInput::IsPress("RMove") ||
                 true == GameEngineInput::IsPress("UMove") ||
                 true == GameEngineInput::IsPress("DMove")  )
        {
            return Act::Move;
        }
      
        else
        {
            return Act::Idle;
        }
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

        //임시용도
    case Act::ToolChange:
        ToolChange();
        break;
    }
}

void Player::Idle()
{
    ChangePlayerAnimation(Dir + "Idle");
}

void Player::ToolChange()
{
    if (CurTool == nullptr)
    {
        MsgAssert("CurTool이 설정되지 않았는데 변경하려 했습니다.");
    }

    if (CurTool == Tool["Axe"])
    {
        CurTool = Tool["Pick"];
    }
    else if (CurTool == Tool["Pick"])
    {
        CurTool = Tool["Hoe"];
    }
    else if(CurTool == Tool["Hoe"])
    {
        CurTool = Tool["Axe"];
    }
}

void Player::Move(float _DeltaTime)
{  
    float4 NextPos = GetPos();
    float4 NextCameraPos = GetLevel()->GetCameraPos();
    float4 MoveDir = { 0,0 };

    GameEngineImage* ColFarm = GameEngineResources::GetInst().ImageFind("FarmC.bmp");

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
    if (RGB(0, 0, 0) != ColFarm->GetPixelColor({ NextPos.x, NextPos.y}, RGB(0, 0, 0)))
    {
        SetPos(NextPos);  

        // 카메라가 멈추는 좌표를 맵의 크기에 따라 가변적이게 설정해야함
        if (NextPos.x >= 1960)
        {
            NextCameraPos.x = 1320;
        }
        if (NextPos.x <= 640)
        {
            NextCameraPos.x = 0;
        }
        if (NextPos.y >= 666)
        {
            NextCameraPos.y = 306;
        }
        if (NextPos.y <= 360)
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

    ChangePlayerAnimation(Dir + "HeavyTool");
    
    if (CurTool->IsUpdate() == true)
    {
        CurTool->ChangeAnimation("RIdle");
        CurTool->ChangeAnimation(Dir + "HeavyTool");
    }
}


void Player::CreatePlayerKey()
{
    if (false == GameEngineInput::IsKey("DMove"))
    {
        GameEngineInput::CreateKey("DMove", 'S');
        GameEngineInput::CreateKey("UMove", 'W');
        GameEngineInput::CreateKey("LMove", 'A');
        GameEngineInput::CreateKey("RMove", 'D');
    }

    if (false == GameEngineInput::IsKey("Interact"))
    {
        GameEngineInput::CreateKey("Interact", 'E');
    } 
    
    if (false == GameEngineInput::IsKey("Menu"))
    {
        GameEngineInput::CreateKey("Menu", VK_ESCAPE);
    }

    if (false == GameEngineInput::IsKey("ToolChange"))
    {
        GameEngineInput::CreateKey("ToolChange", 'F');
    }
}

bool Player::isInteract()
{
    if (CurTool->IsUpdate() == false)
    {
        return false;
    }
    
    if (PlayerRender->GetFrame() == 99)
    {
        CurTool->Off();
        return false;
    }

    return true;

}
bool Player::IsSameCurTool(std::string _ToolName)
{
    if (MyPlayer->CurTool == MyPlayer->Tool[_ToolName])
    {
        return true;
    }
    else
    {
        return false;
    }
}
