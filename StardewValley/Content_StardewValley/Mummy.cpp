#include "Mummy.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "Level_Mine.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <Vector>

int Mummy::AttackPower = 10;

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

    BodyRender->CreateAnimation({ .AnimationName = "DMove", .ImageName = "Mummy.bmp",.FrameIndex = {0, 1, 2, 3},.FrameTime = {0.2f, 0.2f, 0.2f, 0.2f} });
    BodyRender->CreateAnimation({ .AnimationName = "RMove", .ImageName = "Mummy.bmp",.FrameIndex = {4, 5, 6, 7},.FrameTime = {0.2f, 0.2f, 0.2f, 0.2f} });
    BodyRender->CreateAnimation({ .AnimationName = "UMove", .ImageName = "Mummy.bmp",.FrameIndex = {8, 9, 10, 11},.FrameTime = {0.2f, 0.2f, 0.2f, 0.2f} });
    BodyRender->CreateAnimation({ .AnimationName = "LMove", .ImageName = "Mummy.bmp",.FrameIndex = {12, 13, 14, 15},.FrameTime = {0.2f, 0.2f, 0.2f, 0.2f} });
    BodyRender->CreateAnimation({ .AnimationName = "Death", .ImageName = "Mummy.bmp",.FrameIndex = {16, 17, 18, 19, 19},.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });
    BodyRender->CreateAnimation({ .AnimationName = "Birth", .ImageName = "Mummy.bmp",.FrameIndex = {19, 18, 17, 16, 16},.FrameTime = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f} });
   

    HalfBodyCollision = CreateCollision(ActorType::Monster);
    HalfBodyCollision->SetScale({ 64, 64 });
    HalfBodyCollision->SetPosition({ 0, 32 });
    HalfBodyCollision->SetDebugRenderType(CT_Rect);

    FullBodyCollision = CreateCollision(ActorType::FullMonster);
    FullBodyCollision->SetScale({ 64, 128 });

}

void Mummy::Update(float _DeltaTime)
{
    if (isBirth == true) 
    {
        BodyRender->ChangeAnimation("Birth");

        if (BodyRender->IsAnimationEnd() == true)
        {
            SetDir();
            isBirth = false;
        }
    }

    if (isBirth == false)
    {
        RenderOrderUpdate();
        MoveToPlayer(_DeltaTime);

        hitByPlayer(_DeltaTime);
        Dead();
    }

}

void Mummy::Render(float _Time)
{

    //HalfBodyCollision->DebugRender();

    //std::vector<GameEngineCollision*> CollisionList = Level_Mine::GetLevelMineController()->GetOnCollisionList();
    //

    //for (int i = 0; i < CollisionList.size(); i++)
    //{
    //    if (CollisionList[i]->IsUpdate() == true)
    //    {
    //        CollisionList[i]->DebugRender();
    //    }
    //}

    //if (true == HalfBodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Stone), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    //{
    //    int a = 0;
    //}
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
        isHit = true;
        --HP;
        GameEngineResources::GetInst().SoundPlay("MummyHit.wav");
    }

    if (isHit == true && Accel > 0)
    {
        float4 Pos = GetPos() - Player::GetPlayer()->GetPos();
        Pos.Normalize();
        Accel -= 0.01f;

        float4 NextPos = GetPos() + Pos * Accel * _DeltaTime * 100.0f;
        GameEngineImage* ColMap = GameEngineResources::GetInst().ImageFind("MineC.bmp");

        if (false == HalfBodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Stone) + 1, .TargetColType = CT_Rect, .ThisColType = CT_Rect }) &&
            Level_Mine::GetLevelMineController()->CheckUpdateTile(NextPos + float4{0, 32}) == -1 &&
            RGB(0,0,0) != ColMap->GetPixelColor(NextPos,RGB(0, 0, 0)))
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
        SetDir();

        isHit = false;
        Accel = 15;
    }
}

void Mummy::Dead()
{
    if (HP == 0 && false == DeadAnimationStart)
    {
        GameEngineResources::GetInst().SoundPlay("MummyDie.wav");
        BodyRender->ChangeAnimation("Death");
        DeadAnimationStart = true;
    }

    else if (true == DeadAnimationStart && true == BodyRender->IsAnimationEnd())
    {
        Level_Mine::SubNumOfMummy();
        Level_Mine::GetLevelMineController()->DeleteMummyToLst(this);
        Death();
    }
}

void Mummy::MoveToPlayer(float _DeltaTime)
{
    if (static_cast<int>(DestiPos.x) == static_cast<int>(GetPos().x) && static_cast<int>(DestiPos.y) == static_cast<int>(GetPos().y))
    {
        DestiPos = { 0,0 };
    }

    if (DestiPos == float4{ 0,0 })
    {
        SetDir();
    }

    if (DestiPos != float4{ 0, 0 })
    {
        if (true == HalfBodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Stone) + 1, .TargetColType = CT_Rect, .ThisColType = CT_Rect }) && isCol == false)
        {
            SetDir();
            isCol = true;
        }
        else if (false == HalfBodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Stone) + 1, .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
        {
            isCol = false;
        }

        if (DestiPos != float4{ 0, 0 })
        {
            if (HP >= 1)
            {
                BodyRender->ChangeAnimation(Dir + "Move");
                float4 NextPos = GetPos() + DirVector * _DeltaTime * 64;

                FullBodyCollision->SetPosition(NextPos);

                {
                    GameEngineImage* ColMap = GameEngineResources::GetInst().ImageFind("MineC.bmp");
                    float4 DirPos = { 0,0 };
                   
                    if (Dir == "R")
                    {
                        DirPos = { 32.1,0 };
                    }
                    else if (Dir == "L")
                    {
                        DirPos = { -32.1,0 };
                    }
                    else if (Dir == "D")
                    {
                        DirPos = { 0, 64.1 };
                    }
                    else if (Dir == "U")
                    {
                        DirPos = { 0, -64.1 };
                    }

                    if (Level_Mine::GetLevelMineController()->CheckUpdateTile(NextPos + DirPos) != -1)
                    {
                        SetDir();
                    }

                    else if (RGB(0, 0, 0) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)) &&
                        isHit == false)
                    {
                        SetPos(NextPos);
                    }

                }

                FullBodyCollision->SetPosition({ 0,0 });
            }
        }
    }
}

void Mummy::SetDir()
{
    {
        float4 NextPos = GetPos();
        GameEngineImage* ColMap = GameEngineResources::GetInst().ImageFind("MineC.bmp");

        while (1)
        {
            int X = GameEngineRandom::MainRandom.RandomInt(0, 3);

            if (X == 0)
            {
                NextPos += {64, 0};
                Dir = "R";
            }
            else if (X == 1)
            {
                NextPos += {-64, 0};
                Dir = "L";
            }
            else if (X == 2)
            {
                NextPos += {0, 64};
                Dir = "D";
            }
            else if (X == 3)
            {
                NextPos += {0, -64};
                Dir = "U";
            }

            if (NextPos.x <=1280 && NextPos.x >= 0 && NextPos.y >= 0 && NextPos.y <=768 &&
                Level_Mine::GetLevelMineController()->CheckUpdateTile(NextPos) == -1 &&
                RGB(0, 0, 0) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
            {
                break;
            }
            NextPos = GetPos();
        }

        DestiPos = NextPos;
        DirVector = DestiPos - GetPos();
        DirVector.Normalize();
    }
}