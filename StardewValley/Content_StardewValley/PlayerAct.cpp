#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineTileMap.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Farm.h"
#include "Inventory.h"
#include "Level_Farm.h"
#include "Level_Road.h"
#include "Level_House.h"
#include "globalValue.h"
#include "Pierre.h"
#include "Crops.h"
#include "SelectedLine.h"
#include "UI.h"


void Player::InitPlayer()
{

    PlayerRender = CreateRender(50);
    PlayerRender->SetScale({ 64, 128 });

    ColFullBody = CreateCollision(ActorType::FullPlayer);
    ColFullBody->SetScale({ 64, 128 });
    ColFullBody->SetPosition({ 0,0 });

    ColBody = CreateCollision(ActorType::Player);
    ColBody->SetScale({ 64,64 });
    ColBody->SetPosition({ 0,32 });
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

    if (isInteract() == true)
    {
        return;
    }

    if (isAbleAct == false)
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
    case Act::MouseInteract:
        Interact();
        break;
    case Act::KeyInteract:
        InteractToNPC();
        break;
    case Act::Menu:
        OpenInventory();
        break;
    case Act::ChangeQuickSlotItem:
        globalValue::ChangeAllQuickSlotItem(inputNumberKey);
        break;
    case Act::ChangeQuickSlot:
        globalValue::ChangeAllQuickSlot();
        break;
    }
}

void Player::Idle()
{
    ChangePlayerAnimation(Dir + "Idle");
}

void Player::OpenInventory()
{
    globalValue::OpenInventory(GetLevel()->GetName());
}


void Player::Move(float _DeltaTime)
{  
    float4 NextPos = GetPos();
    float4 NextCameraPos = GetLevel()->GetCameraPos();
    float4 MoveDir = { 0,0 };
    
    std::string MapName = GetLevel()->GetName() + "C";

    ColMap = GameEngineResources::GetInst().ImageFind(MapName + ".bmp");

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

    NextPos += MoveDir * MoveSpeed * _DeltaTime;
    NextCameraPos += MoveDir * MoveSpeed * _DeltaTime;

    // 실제로 위치를 이동 (x, y중 한 쪽만 막혀있을 경우에도 움직일 수 있게 로직변경이 필요
    if (nullptr != ColMap && RGB(0, 0, 0) != ColMap->GetPixelColor({ NextPos.x, NextPos.y }, RGB(0, 0, 0)))
    {

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
        SetPos(NextPos);
    }

    SetDir();
}

void Player::Interact()
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

    InteractToTile();

    if (isHarvesting == true || CurTool == Tool["Default"])
    {
        return;
    }

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

        if(isHarvesting == true)
        {
            isHarvesting = false;
        }

        return false;
    }

    else 
    {
        return true;
    }
}


void Player::InteractToCrops()
{
    ColTool->SetPosition(SetToolPos());

    if (CurTool->IsUpdate() == true)
    {
        std::vector<GameEngineCollision*> Collisions;
        if (true == ColTool->Collision({ .TargetGroup = static_cast<int>(ActorType::Crops) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
        {
            for (size_t i = 0; i < Collisions.size(); i++)
            {
                Crops* ColActor = dynamic_cast<Crops*>(Collisions[i]->GetActor());
               
                if (ColActor->GetLife() > 0 && CurTool == Tool["Watering"])
                {
                    ColActor->GrowUp();
                }

                else if (ColActor->GetLife() <= 0)
                {
                    SetIsHarvesting();
                    ColActor->Death();
                    Level_Farm::DeathCrops(ColActor);

                    globalValue::CreateItemToAllInventory(ColActor->GetName(), static_cast<int>(ItemType::Crops));
                }

                ColActor->CollisionOff();

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

void Player::ChangePlayerIdle(const std::string& _Dir)
{
    MyPlayer->ChangePlayerAnimation(_Dir + "Idle");
    MyPlayer->Dir = _Dir;
}


bool Player::isCollisionCrops()
{
    std::vector<GameEngineCollision*> Collisions;

    if (true == ColBody->Collision({ .TargetGroup = static_cast<int>(ActorType::Crops) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collisions))
    {
        if (Collisions.size() >= 1)
        {
            return true;
        }
    }

    return false;
}

void Player::Harvesting()
{
    if (isHarvesting == true)
    {
        CurTool->On();
        CurTool->SetScale({ 0,0 });

        ChangePlayerAnimation(Dir + "Harvesting");

        return;
    }
}

const float4 Player::GetDirPos()
{
    if (Dir == "R")
    {
        return float4::Right;
    }
    else if (Dir == "L")
    {
        return float4::Left;
    }
    else if (Dir == "U")
    {
        return float4::Up;
    }
    else if (Dir == "D")
    {
        return float4::Down;
    }

    else
    {
        return { 0,0 };
    }
}

void Player::InteractToTile()
{
    if (GetLevel()->GetName() != "Farm")
    {
        return;
    }
   
    float4 MousePos = GetLevel()->GetMousePosToCamera();
    float4 PlayerPos = GetPos();

    if (nullptr != ColMap && RGB(255, 0, 255) != ColMap->GetPixelColor(MousePos, RGB(255, 0, 255)))
    {
        return;
    }

    if (isFront(MousePos) != true)
    {
        return;
    }

    
    if (SelectedLine::IsLineOn() == false)
    {
        return;
    }
    
    int SeedIndex = Level_Farm::CheckUpdateTile(MousePos);
    int TileFrame = Level_Farm::GetTileMap()->GetTileFrame(0, MousePos);
    
    if (SeedIndex != -1 && Level_Farm::IsMaxGrow(MousePos, SeedIndex) == true)
    {
        isHarvesting = true;
        globalValue::CreateItemToAllInventory(SeedIndex);
        Level_Farm::DeleteTileToList(SeedIndex, MousePos);
        Harvesting();
        return;
    }

    else if (TileFrame == -1)
    {
        if (CurTool == Tool["Hoe"])
        {
            Level_Farm::GetTileMap()->SetTileFrame(0, MousePos, 0);
        }
    }

    else if (TileFrame == 0)
    {
        if (CurTool == Tool["Watering"])
        {
            Level_Farm::GetTileMap()->SetTileFrame(0, MousePos, 1);
        }
    }  

    else if (TileFrame == 1 && SeedIndex == -1)
    {
        if (globalValue::GetSelectedItem()->GetItemType() == static_cast<int>(ItemType::Seed))
        {
            int Floor = globalValue::GetSelectedItem()->GetSeedFloor();

            globalValue::AllInventoryDelete();
            
            GameEngineRender* Tile = Level_Farm::GetTileMap()->GetTile(Floor, MousePos);

            Level_Farm::SetSeedPos(MousePos, Floor);
            Level_Farm::GetTileMap()->SetTileFrame(Floor, MousePos, 0);

            Tile->SetOrder(200);

            Level_Farm::PlusOnTileToList(Tile);
        }
    }
}

const float4 Player::GetInteractPos()
{
    if (Dir == "D")
    {
        return GetPos() + GetDirPos() * float4(0, 80) ;
    }
    else if (Dir == "R" || Dir == "L")
    {
        return GetPos() + GetDirPos() * float4(64, 0) + float4(0, 32);
    }
    else if(Dir == "U")
    {
        return GetPos() + GetDirPos() * float4(64, 0);
    }
    else
    {
        return GetPos();
    }
}

void Player::InteractToNPC()
{
    Level_Road::NPCPierre->OpenPierreShop();
}

bool Player::isFront(float4 _pos)
{
    if (Dir == "D")
    {
        return _pos.y - 64 >= GetPos().y;
    }
    else if (Dir == "U")
    {
        return _pos.y - 63 <= GetPos().y;
    }
    else if (Dir == "L")
    {
        return _pos.x - 32<= GetPos().x;
    }
    else if (Dir == "R")
    {
        return _pos.x - 32 >= GetPos().x;
    }

    return false;
}