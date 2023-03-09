#include "SellBox.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "globalInterface.h"
#include "Inventory.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

Inventory* SellBox::BoxInventory = nullptr;

SellBox::SellBox()
{
}

SellBox::~SellBox()
{

}

void SellBox::Start()
{
    BoxInventory = GetLevel()->CreateActor<Inventory>();
    BoxInventory->Off();
    BoxInventory->SetOwnerToBox();

    SellBoxRender = CreateRender("SellBox.bmp", 48);
    SellBoxRender->SetScaleToImage();
    SellBoxRender->SetPosition({ 2116, 395});

    SellBoxCoverRender = CreateRender("SellBoxCover.bmp", 49);
    SellBoxCoverRender->SetScale({ 120, 100 });
    SellBoxCoverRender->SetPosition({ 2120, 343});

    SellBoxCoverRender->CreateAnimation({ .AnimationName = "CoverOpen", .ImageName = "SellBoxCover.bmp",.FrameIndex = {0,1,2,3,4,5,6,7,8,9,10,11,12},.FrameTime = {0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f} });
    SellBoxCoverRender->CreateAnimation({ .AnimationName = "CoverClose", .ImageName = "SellBoxCover.bmp",.FrameIndex = {12,11,10,9,8,7,6,5,4,3,2,1,0},.FrameTime = {0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f} });
    SellBoxCoverRender->CreateAnimation({ .AnimationName = "OpenIdle", .ImageName = "SellBoxCover.bmp",.FrameIndex = {12},.FrameTime = {0.02f} });
    SellBoxCoverRender->CreateAnimation({ .AnimationName = "CloseIdle", .ImageName = "SellBoxCover.bmp",.FrameIndex = {0},.FrameTime = {0.02f} });
    SellBoxCoverRender->ChangeAnimation("CloseIdle");

    SellBoxCollision = CreateCollision(ActorType::NPC);
    SellBoxCollision->SetScale(SellBoxRender->GetScale());
    SellBoxCollision->SetPosition(SellBoxRender->GetPosition());

    SellBoxInventoryRender = CreateRender("SellBoxInventory.bmp", 200);
    SellBoxInventoryRender->SetScaleToImage();
    SellBoxInventoryRender->SetPosition({640, 643});
    SellBoxInventoryRender->EffectCameraOff();
    SellBoxInventoryRender->Off();

    SelectedItem = CreateRender("SellBoxSelectedItem.bmp", 201);
    SelectedItem->SetScaleToImage();
    SelectedItem->SetPosition({ 640, 493 });
    SelectedItem->EffectCameraOff();
    SelectedItem->Off();
}

void SellBox::Update(float _DeltaTime)
{
    if (true == BoxInventory->IsUpdate())
    {
        globalInterface::AllInventoryItemOff();
    }

    if (true == SellBoxCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::PlayerInteract), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if (SellBoxCoverRender->GetFrame() != 12)
        {
            SellBoxCoverRender->ChangeAnimation("CoverOpen");

            if (isOnSound == false)
            {
                GameEngineResources::GetInst().SoundPlay("OpenBox.wav");
                isOnSound = true;
            }
        }
        else
        {
            SellBoxCoverRender->ChangeAnimation("OpenIdle");
            isOnSound = false;
            BoxOnOff();
        }
    }
    else
    {
        if (SellBoxCoverRender->GetFrame() != 0)
        {
            SellBoxCoverRender->ChangeAnimation("CoverClose");
        }
        else
        {
            SellBoxCoverRender->ChangeAnimation("CloseIdle");
        }
    }
}

void SellBox::Render(float _Time)
{

}

void SellBox::BoxOn()
{
    Player::GetPlayer()->PlayerStop();
    Player::ChangePlayerIdle("U");

    globalInterface::AllInventoryItemOff();

    BoxInventory->On();
    BoxInventory->SetAllItemPOrder(202);
    BoxInventory->AllItemOn();
    BoxInventory->SetItemPos();

    SellBoxInventoryRender->On();
    SelectedItem->On();
}

void SellBox::BoxOff()
{
    Player::GetPlayer()->PlayerStopOff();

    if (nullptr != BoxInventory->GetLastSellItem())
    {
        globalInterface::AllInventoryLastSellItemDeath();
    }

    globalInterface::AllInventoryItemOn();

    BoxInventory->Off();
    BoxInventory->AllItemOff();
    SellBoxInventoryRender->Off();
    SelectedItem->Off();
}

void SellBox::BoxOnOff()
{
    if (false == SellBoxInventoryRender->IsUpdate() && GameEngineInput::IsDown("KeyInteract"))
    {
        BoxOn();
    }
    else if (true == SellBoxInventoryRender->IsUpdate() && GameEngineInput::IsDown("KeyInteract"))
    {
        BoxOff();
    }
}

bool SellBox::IsBOxOn()
{
    return BoxInventory->IsUpdate();
}