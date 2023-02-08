#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>

static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);


class CollisionFunctionInit
{
public:
    CollisionFunctionInit()
    {
        ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
        ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
        ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
        ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
    }
    ~CollisionFunctionInit()
    {

    }
};

CollisionFunctionInit Init = CollisionFunctionInit();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
    float4 Len = _Left.Position - _Right.Position;
    float Size = Len.Size();
    float RadiusSum = _Left.Scale.hx();
    return RadiusSum > Size;
}

bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
    float4 Len = _Left.Position - _Right.Position;
    float Size = Len.Size();
    float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();
    return RadiusSum > Size;
}

bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
    if (_Left.Bot() <= _Right.Top())
    {
        return false;
    }

    if (_Left.Top() >= _Right.Bot())
    {
        return false;
    }

    if (_Left.Left() >= _Right.Right())
    {
        return false;
    }

    if (_Left.Right() <= _Right.Left())
    {
        return false;
    }

    return true;
}

bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
    if (_Left.Bot() <= _Right.Position.y)
    {
        return false;
    }

    if (_Left.Top() >= _Right.Position.y)
    {
        return false;
    }

    if (_Left.Left() >= _Right.Position.x)
    {
        return false;
    }

    if (_Left.Right() <= _Right.Position.x)
    {
        return false;
    }

    return true;
}

void GameEngineCollision::SetOrder(int _Order)
{
    GameEngineComponent::SetOrder(_Order);
    GetActor()->GetLevel()->PushCollision(this);
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
    if (false == IsUpdate())
    {
        return false;
    }

    std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

    for (GameEngineCollision* OtherCollision : _TargetGroup)
    {
        if (OtherCollision == this)
        {
            continue;
        }

        if (false == OtherCollision->IsUpdate())
        {
            continue;
        }

        CollisionType Type = _Parameter.ThisColType;
        CollisionType OtherType = _Parameter.TargetColType;

        if (nullptr == ColFunctionPtr[Type][OtherType])
        {
            MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
        }

        if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
        {
            return true;
        }
    }
    return false;
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
    if (false == IsUpdate())
    {
        return false;
    }

    _Collision.clear();

    std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

    SetDebugRenderType(_Parameter.ThisColType);

    for (GameEngineCollision* OtherCollision : _TargetGroup)
    {
        if (false == OtherCollision->IsUpdate())
        {
            continue;
        }

        CollisionType Type = _Parameter.ThisColType;
        CollisionType OtherType = _Parameter.TargetColType;

        OtherCollision->SetDebugRenderType(OtherType);

        if (nullptr == ColFunctionPtr[Type][OtherType])
        {
            MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
        }

        if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
        {
            _Collision.push_back(OtherCollision);
        }
    }

    return _Collision.size() != 0;
}

CollisionData GameEngineCollision::GetCollisionData()
{
    return { GetActorPlusPos(), GetScale() };
}

void GameEngineCollision::DebugRender()
{
    HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
    float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();
    switch (DebugRenderType)
    {
    case CT_Point:
        break;
    case CT_CirCle:
    {
        int Radius = GetScale().hix();
        Ellipse(BackBufferDc,
            DebugRenderPos.ix() - Radius,
            DebugRenderPos.iy() - Radius,
            DebugRenderPos.ix() + Radius,
            DebugRenderPos.iy() + Radius);
        break;
    }
    case CT_Rect:
    {
        Rectangle(BackBufferDc,
            DebugRenderPos.ix() - GetScale().hix(),
            DebugRenderPos.iy() - GetScale().hiy(),
            DebugRenderPos.ix() + GetScale().hix(),
            DebugRenderPos.iy() + GetScale().hiy());
        break;
    }
    case CT_Max:
        break;
    default:
        break;
    }
}