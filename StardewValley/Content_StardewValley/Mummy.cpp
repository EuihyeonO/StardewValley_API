#include "Mummy.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "Level_Mine.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineImage.h>

Mummy::Mummy()
{
}

Mummy::~Mummy()
{
}

void Mummy::Start()
{
    BodyRender = CreateRender(0);
    BodyRender->SetScale({ 64, 128 });

    BodyRender->CreateAnimation({ .AnimationName = "DMove", .ImageName = "Mummy.bmp",.FrameIndex = {0, 1, 2, 3},.FrameTime = {0.5f, 0.5f, 0.5f, 0.5f} });
    BodyRender->CreateAnimation({ .AnimationName = "RMove", .ImageName = "Mummy.bmp",.FrameIndex = {4, 5, 6, 7},.FrameTime = {0.5f, 0.5f, 0.5f, 0.5f} });
    BodyRender->CreateAnimation({ .AnimationName = "UMove", .ImageName = "Mummy.bmp",.FrameIndex = {8, 9, 10, 11},.FrameTime = {0.5f, 0.5f, 0.5f, 0.5f} });
    BodyRender->CreateAnimation({ .AnimationName = "LMove", .ImageName = "Mummy.bmp",.FrameIndex = {12, 13, 14, 15},.FrameTime = {0.5f, 0.5f, 0.5f, 0.5f} });
    BodyRender->CreateAnimation({ .AnimationName = "Death", .ImageName = "Mummy.bmp",.FrameIndex = {16, 17, 18, 19, 19},.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });
    
    BodyRender->ChangeAnimation(Dir + "Move");

    HalfBodyCollision = CreateCollision(ActorType::Monster);
    HalfBodyCollision->SetScale({ 64, 64 });
    HalfBodyCollision->SetPosition({ 0, 32 });
}

void Mummy::Update(float _DeltaTime)
{
    RenderOrderUpdate();
    hitByPlayer(_DeltaTime);
    Dead();
}

void Mummy::Render(float _Time)
{
}

void Mummy::RenderOrderUpdate()
{

    int YDistance = BodyRender->GetActorPlusPos().y - Player::GetPlayer()->GetPos().y;

    if (YDistance >= 0)
    {
        BodyRender->SetOrder(60);
    }
    else
    {
        BodyRender->SetOrder(40);
    }
}

void Mummy::hitByPlayer(float _DeltaTime)
{
    if (false == isHit && true == HalfBodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Hammer), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        HalfBodyCollision->Off();
        isHit = true;
        --HP;
    }

    if (isHit == true && Accel > 0)
    {
        float4 Pos = GetPos() - Player::GetPlayer()->GetPos();
        Pos.Normalize();
        Accel -= 0.001f;

        float4 NextPos = GetPos() + Pos * Accel * _DeltaTime * 100.0f;
        GameEngineImage* ColMap = GameEngineResources::GetInst().ImageFind("MineC.bmp");

        if (Level_Mine::GetLevelMineController()->CheckUpdateTile(NextPos + float4{ 0, 32 }) == -1 &&
            ColMap->GetPixelColor(NextPos, RGB(0, 0, 0) != RGB(0, 0, 0)))
        {
            SetPos(NextPos);
        }
        else
        {
            Accel = 0;
        }
    }
    else if (Accel <= 0 && true == Player::GetPlayer()->isPlayerAnimationEnd())
    {
        isHit = false;
        Accel = 15;
        HalfBodyCollision->On();
    }
}

void Mummy::Dead()
{
    if (HP == 0 && false == DeadAnimationStart)
    {
        BodyRender->ChangeAnimation("Death");
        DeadAnimationStart = true;
    }

    else if (true == DeadAnimationStart && true == BodyRender->IsAnimationEnd())
    {
        Death();
    }
}