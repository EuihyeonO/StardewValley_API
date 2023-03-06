#include "Tree.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "globalInterface.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>


Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::Start()
{
    //SetPos({ 832, 768 });

    TreeRender = CreateRender("Tree.bmp", 52);
    TreeRender->SetScale({176, 288});
    TreeRender->CreateAnimation({ .AnimationName = "Vib", .ImageName = "Tree.bmp",.FrameIndex = {1,2,3,4,4},.FrameTime = {0.05f, 0.05f, 0.05f, 0.05f, 0.05f} });
    TreeRender->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Tree.bmp",.FrameIndex = {0},.FrameTime = {1.0f} });
    TreeRender->ChangeAnimation("Idle");

    TreeUnderRender = CreateRender("TreeUnder.bmp", 51);
    TreeUnderRender->SetScaleToImage();
    TreeUnderRender->SetPosition({ 0, 120 });

    TreeCollision = CreateCollision(ActorType::Tree);
    TreeCollision->SetScale(TreeRender->GetScale());
    TreeCollision->SetPosition(TreeRender->GetPosition());

    TreeUnderCollision = CreateCollision(ActorType::NPC);
    TreeUnderCollision->SetScale(TreeUnderRender->GetScale());
    TreeUnderCollision->SetPosition(TreeUnderRender->GetPosition());
}

void Tree::Update(float _DeltaTime)
{
    RenderOrderUpdate();
    TreeHpUpdate();
    AbsorbToPlayer(_DeltaTime);
}

void Tree::Render(float _Time)
{

}

void Tree::RenderOrderUpdate()
{
    if (TreeUnderRender->GetActorPlusPos().y >= Player::GetPlayer()->GetPos().y)
    {
        TreeUnderRender->SetOrder(52);
        TreeRender->SetOrder(53);
    }
    else
    {
        TreeUnderRender->SetOrder(48);
        TreeRender->SetOrder(49);
    }
}

void Tree::TreeHpUpdate()
{
    if (false == isHit && true == TreeCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Axe), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        GameEngineResources::GetInst().SoundPlay("TreeHit.wav");
        --Hp;
        isHit = true;
        TreeRender->ChangeAnimation("Vib");
    }
    else if (true == isHit && true == Player::GetPlayer()->isPlayerAnimationEnd())
    {
        isHit = false;
        TreeRender->ChangeAnimation("Idle");
    }

    if (Hp <= 0)
    {
        TreeRender->Off();
        TreeUnderRender->Off();
        MakeDebris();
        isCompleteToAbsorb();

        if (true == isExistDebris && true == CompleteToAbsorb)
        {
            Death();
        }
    }
    
}


void Tree::MakeDebris()
{
    if (isExistDebris == false) 
    {
        GameEngineResources::GetInst().SoundPlay("TreeDeath.wav");

        for (int i = 0; i < 8; i++)
        {
            int X = GameEngineRandom::MainRandom.RandomInt(0, 1);
            if (X == 0)
            {
                DebrisList.push_back(CreateRender("TreeDebris1.bmp", 55));
                DebrisList[i]->SetScaleToImage();
            }
            else if (X == 1)
            {
                DebrisList.push_back(CreateRender("TreeDebris2.bmp", 55));
                DebrisList[i]->SetScaleToImage();
            }
        }

        float X, Y;

        for (int i = 0; i < DebrisList.size(); i++)
        {
            X = GameEngineRandom::MainRandom.RandomFloat(-50, 50);
            Y = GameEngineRandom::MainRandom.RandomFloat(-140, 80);

            DebrisList[i]->SetPosition({ X,Y });
        }

        isExistDebris = true;
    }
}

void Tree::AbsorbToPlayer(float _Deltatime)
{
    if (DebrisList.size() <= 0)
    {
        return;
    }
    float4 PlayerPos = Player::GetPlayer()->GetPos();


    Accel += 0.2f;

    for (int i = 0; i < DebrisList.size(); i++)
    {
        float4 DebrisPos = DebrisList[i]->GetActorPlusPos();
        float4 Dir = PlayerPos - DebrisPos;
        Dir.Normalize();
        DebrisList[i]->SetMove(Dir * Accel * _Deltatime * 30);
        
        float Distance = sqrt((PlayerPos.x - DebrisPos.x) * (PlayerPos.x - DebrisPos.x) + (PlayerPos.y - DebrisPos.y) * (PlayerPos.y - DebrisPos.y));
        
        if (Distance <= 3 && true == DebrisList[i]->IsUpdate())
        {
            DebrisList[i]->Off();
            GameEngineResources::GetInst().SoundPlay("ItemSwap.wav");
            globalInterface::CreateItemToAllInventory("IconBranch.bmp", static_cast<int>(ItemType::Etc));
        }
    }
}

void Tree::isCompleteToAbsorb()
{
    int Count = 0;

    for (int i = 0; i < DebrisList.size(); i++)
    {
        if (true == DebrisList[i]->IsUpdate())
        {
            ++Count;
        }
    }

    if (Count == 0)
    {
        CompleteToAbsorb = true;
    }
}