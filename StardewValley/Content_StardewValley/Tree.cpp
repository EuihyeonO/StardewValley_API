#include "Tree.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>


Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::Start()
{
    SetPos({ 832, 768 });

    TreeRender = CreateRender("Tree.bmp", 52);
    TreeRender->SetScaleToImage();

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
}

void Tree::Render(float _Time)
{

}

void Tree::RenderOrderUpdate()
{
    if (TreeUnderRender->GetActorPlusPos().y >= Player::GetPlayer()->GetPos().y)
    {
        TreeUnderRender->SetOrder(51);
        TreeRender->SetOrder(52);
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
    }
    else if (true == isHit && true == Player::GetPlayer()->isPlayerAnimationEnd())
    {
        isHit = false;
    }

    if (Hp <= 0)
    {
        GameEngineResources::GetInst().SoundPlay("TreeDeath.wav");
        Death();
    }
}

