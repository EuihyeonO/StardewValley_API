#include <vector>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "ContentsEnum.h"
#include "Farm.h"
#include "Inventory.h"
#include "Level_Farm.h"
#include "Level_Road.h"
#include "Level_House.h"
#include "Level_Mine.h"
#include "globalValue.h"
#include "globalInterFace.h"
#include "globalSound.h"
#include "Pierre.h"
#include "SelectedLine.h"
#include "UI.h"
#include "Level_Mine.h"
#include "Marlon.h"


void Player::InitPlayer()
{

    PlayerRender = CreateRender(50);
    PlayerRender->SetScale({ 64, 128 });

    Shadow = CreateRender("Shadow.bmp", 49);
    Shadow->SetScaleToImage();
    Shadow->SetPosition({ 0, 60 });
    Shadow->SetAlpha(100);

    ColFullBody = CreateCollision(ActorType::FullPlayer);
    ColFullBody->SetScale({ 64, 128 });
    ColFullBody->SetPosition({ 0,0 });

    ColBody = CreateCollision(ActorType::Player);
    ColBody->SetScale({ 48,48 });
    ColBody->SetPosition({ 0,32 });

    ColInteract = CreateCollision(ActorType::PlayerInteract);
    ColInteract->SetScale({ 64, 64 });
    ColInteract->SetPosition({ 0,32 });

    HammerCollision = CreateCollision(ActorType::Hammer);
    HammerCollision->SetScale({ 64, 64 });
    HammerCollision->Off();
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
        globalSound::GetSoundPlayer()->WalkSoundOff();
        return;
    }

    if (isAbleAct == false)
    {
        globalSound::GetSoundPlayer()->WalkSoundOff();
        return;
    }

    int Act = GetKeyInput();

    switch (Act)
    {
    case Act::Idle:
        Idle();
        globalSound::GetSoundPlayer()->WalkSoundOff();
        break;
    case Act::Move:
        Move(_DeltaTime);
        globalSound::GetSoundPlayer()->WalkSoundOn();
        break;
    case Act::MouseInteract:
        Interact();
        break;
    case Act::KeyInteract:
        InteractToNPC();
        break;
    case Act::Menu:
        OpenMenu();
        break;
    case Act::ChangeQuickSlotItem:
        globalInterface::ChangeAllQuickSlotItem(inputNumberKey);    
        GameEngineResources::GetInst().SoundPlay("Itemswap.wav");
        break;
    case Act::ChangeQuickSlot:
        globalInterface::ChangeAllQuickSlot();
        break;
    }
}

void Player::Idle()
{
    ChangePlayerAnimation(Dir + "Idle");

    if (CurTool == Tool["Watering"] ||
        CurTool == Tool["Hoe"] ||
        CurTool == Tool["Hammer"] ||
        CurTool == Tool["Pick"] ||
        CurTool == Tool["Axe"]) 
    {
        CurTool->ChangeAnimation(Dir + "Idle");
    }
}

void Player::OpenMenu()
{
    globalInterface::MenuOnOff();
}


void Player::Move(float _DeltaTime)
{  
    float4 NextPos = GetPos();
    float4 NextCameraPos = GetLevel()->GetCameraPos();
    float4 MoveDir = { 0,0 };
    
    std::string MapName = GetLevel()->GetName() + "C";

    ColMap = GameEngineResources::GetInst().ImageFind(MapName + ".bmp");

    //�Ʒ��� ��� �̵�
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

    //���ʱ�� �̵�
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

    //�����̵�
    else if (true == GameEngineInput::IsPress("RMove"))
    {
    MoveDir += float4::Right;
    ChangePlayerAnimation("RMove");
    }

    //�����̵�
    else if (true == GameEngineInput::IsPress("LMove"))
    {
    MoveDir += float4::Left;
    ChangePlayerAnimation("LMove");
    }

    NextPos += MoveDir * MoveSpeed * _DeltaTime;
    NextCameraPos += MoveDir * MoveSpeed * _DeltaTime;

    ColBody->SetMove(MoveDir * MoveSpeed * _DeltaTime);

    // ������ ��ġ�� �̵� (x, y�� �� �ʸ� �������� ��쿡�� ������ �� �ְ� ���������� �ʿ�
    if (nullptr != ColMap && 
        RGB(0, 0, 0) != ColMap->GetPixelColor({ NextPos.x, NextPos.y }, RGB(0, 0, 0)) && 
        false == Level_Mine::GetLevelMineController()->isCollisionToTile(NextPos) &&
        false == ColBody->Collision({ .TargetGroup = static_cast<int>(ActorType::NPC), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
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
    ColBody->SetPosition({ 0, 32 });
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

    if (CurTool == Tool["Hammer"])
    {
        CurTool->SetScale({ 250, 250 });
    }

    CurTool->On();
    
    InteractToTile();

    if (isHarvesting == true || CurTool == Tool["Default"] || Marlon::GetGlobalMarlon()->isMarlonTextOn() == true)
    {
        return;
    }


    CurTool->ChangeAnimation(Dir + "Idle");

    if (CurTool->IsUpdate() == true && CurTool == Tool["Watering"])
    {
        CurTool->ChangeAnimation(Dir + "Watering");
        ChangePlayerAnimation(Dir + "Watering");

        GameEngineResources::GetInst().SoundPlay("Watering.wav");
    }
    else if (CurTool->IsUpdate() == true && CurTool == Tool["Hammer"])
    {
        CurTool->ChangeAnimation(Dir + "Hammer");
        ChangePlayerAnimation(Dir + "Attack");

        GameEngineResources::GetInst().SoundPlay("Hammer.wav");
    }
    else if (CurTool->IsUpdate() == true)
    {
        CurTool->ChangeAnimation(Dir + "HeavyTool");
        ChangePlayerAnimation(Dir + "HeavyTool");

        if (CurTool == Tool["Hoe"])
        {
            GameEngineResources::GetInst().SoundPlay("HoeHit.wav");
        }

        else if (CurTool == Tool["Pick"])
        {
            GameEngineResources::GetInst().SoundPlay("Pick.wav");
        }
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

        if (CurTool != nullptr) 
        {
            //CurToo�� OnOff�� ��ȣ�ۿ��������� �Ǵ��ϴ� ���� ���� 
            CurTool->Off();
        }

        if (GetItemRender != nullptr) 
        {
            //������ ȹ�� �ִϸ��̼��� ������� ����Off
            GetItemRender->Off();
        }

        if (ColTool != nullptr)
        {
            //��ȣ�ۿ뵿�� �浹�˻�� �� 1���� �ϸ� �Ǳ⶧���� ��ȣ�ۿ��� ���۵Ǹ� �浹�� ���ٰ� ������ �ٽ� �浹�� ��
            ColTool->On();
        }

        if(isHarvesting == true)
        {
            //��Ȯ �ִϸ��̼��� ������ false�� ����
            isHarvesting = false;
        }

        return false;
    }

    else 
    {
        return true;
    }
}

void Player::ChangePlayerIdle(const std::string& _Dir)
{
    MyPlayer->ChangePlayerAnimation(_Dir + "Idle");
    if (MyPlayer->CurTool == MyPlayer->Tool["Watering"] ||
        MyPlayer->CurTool == MyPlayer->Tool["Hoe"] ||
        MyPlayer->CurTool == MyPlayer->Tool["Hammer"] ||
        MyPlayer->CurTool == MyPlayer->Tool["Pick"] ||
        MyPlayer->CurTool == MyPlayer->Tool["Axe"]) 
    {
        MyPlayer->CurTool->ChangeAnimation(_Dir + "Idle");
    }

    MyPlayer->Dir = _Dir;
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
    std::string name = GetLevel()->GetName();

    if (GetLevel()->GetName() != "Farm" && GetLevel()->GetName() != "Mine")
    {
        return;
    }
   
    float4 MousePos = GetLevel()->GetMousePosToCamera();
    float4 PlayerPos = GetPos();

    if (CurTool == Tool["Pick"] && CurTool->IsUpdate() == true)
    {
        if (Level_Mine::GetLevelMineController()->isToolCollisionToTile() == true)
        {
            Level_Mine::GetLevelMineController()->SubToStoneLife(ColTool->GetActorPlusPos());
        }
    }

    if (isFront(MousePos) != true)
    {
        return;
    }


    if (nullptr != ColMap && RGB(255, 0, 255) != ColMap->GetPixelColor(MousePos, RGB(255, 0, 255)))
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
        globalInterface::CreateItemToAllInventory(SeedIndex);
        Level_Farm::DeleteTileToList(SeedIndex, MousePos);
        Harvesting();

        GameEngineResources::GetInst().SoundPlay("Harvest.wav");
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
        if (globalInterface::GetSelectedItem()->GetItemType() == static_cast<int>(ItemType::Seed))
        {
            int Floor = globalInterface::GetSelectedItem()->GetSeedFloor();

            globalInterface::AllInventoryDelete();
            
            GameEngineRender* Tile = Level_Farm::GetTileMap()->GetTile(Floor, MousePos);

            Level_Farm::SetSeedPos(MousePos, Floor);
            Level_Farm::GetTileMap()->SetTileFrame(Floor, MousePos, 0);

            Tile->SetOrder(150);

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

int Player::GetToolFrame()
{
    return MyPlayer->CurTool->GetFrame();
}

void Player::isCollidedToNPC()
{
    if (true == ColInteract->Collision({ .TargetGroup = static_cast<int>(ActorType::NPC), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        isColToNPC = true;
    }
    else
    {
        isColToNPC = false;
    }
}

void Player::GetItem(const std::string_view& _itemName)
{
    PlayerRender->ChangeAnimation("Didle");
    CurTool->On();
    CurTool->SetScale({ 0,0 });

    PlayerRender->ChangeAnimation("GetItem");

    GetItemRender = CreateRender(_itemName, 200);
    GetItemRender->SetPosition({ 0, -48 });
    GetItemRender->SetScale({ 64, 64 });
    GetItemRender->On();

    Dir = "D";
}


void Player::HammerCollisionUpdate()
{
    if (Dir == "U")
    {
        HammerCollision->SetPosition({ 0, -32 });
    }
    else if (Dir == "D")
    {
        HammerCollision->SetPosition({ 0, 32 });
    }
    else if (Dir == "R")
    {
        HammerCollision->SetPosition({ 32,0 });
    }
    else if (Dir == "L")
    {
        HammerCollision->SetPosition({ -32, 0 });
    }

    if (CurTool == Tool["Hammer"] && true == CurTool->IsUpdate())
    {
        HammerCollision->On();
    }
    else
    {
        HammerCollision->Off();
    }
}