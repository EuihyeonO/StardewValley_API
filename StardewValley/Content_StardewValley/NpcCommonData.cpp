#include "NpcCommonData.h"
#include "ContentsEnum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>


NpcCommonData::NpcCommonData()
{
}

NpcCommonData::~NpcCommonData()
{
}

void NpcCommonData::SetBodyRender(const std::string_view& _ImageName, float4 _pos)
{
    BodyRender = CreateRender(_ImageName, 50);
    BodyRender->SetScaleToImage();
    BodyRender->SetPosition(_pos);
}

void NpcCommonData::SetCollision()
{
    float4 Scale = BodyRender->GetScale();

    BodyCollision = CreateCollision(ActorType::NPC);
    BodyCollision->SetScale({ Scale.x, Scale.y *(0.5f)});
    BodyCollision->SetPosition(BodyRender->GetPosition() + float4{ 0, Scale.y * (0.25f)});

    OrderCollision = CreateCollision(ActorType::OrderChange);
    OrderCollision->SetScale(BodyRender->GetScale());
    OrderCollision->SetPosition(BodyRender->GetPosition());
}

void NpcCommonData::RenderOrderUpdate()
{
    if (true == OrderCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::FullPlayer), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        int YDistance = BodyRender->GetPosition().y - Player::GetPlayer()->GetPos().y;
   
        if (YDistance >= 0)
        {
            BodyRender->SetOrder(60);
        }
        else
        {
            BodyRender->SetOrder(40);
        }
    }
}