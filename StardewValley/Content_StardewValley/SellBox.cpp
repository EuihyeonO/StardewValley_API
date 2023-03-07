#include "SellBox.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

SellBox::SellBox()
{

}

SellBox::~SellBox()
{

}

void SellBox::Start()
{
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

}

void SellBox::Update(float _DeltaTime)
{
    if (true == SellBoxCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::PlayerInteract), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if (SellBoxCoverRender->GetFrame() != 12)
        {
            SellBoxCoverRender->ChangeAnimation("CoverOpen");
        }
        else
        {
            SellBoxCoverRender->ChangeAnimation("OpenIdle");
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