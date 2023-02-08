#include "Button.h"
#include <GameEnginePlatform/GameEngineInput.h>

Button::Button()
{
    State = ButtonState::Release;
}

Button::~Button()
{
}


void Button::SetTargetCollisionGroup(int _PointTargetGroup)
{
    PointTargetGroup = _PointTargetGroup;
    if (nullptr == ButtonCollision)
    {
        ButtonCollision = CreateCollision(PointTargetGroup);
    }
}


void Button::Start()
{
    Render = CreateRender();
}

void Button::SetRenderOrder(int _Value)
{
    Render->SetOrder(_Value);
}

void Button::SetScale(float4 _Scale)
{
    Render->SetScale(_Scale);
}

void Button::Update(float _DeltaTime)
{

    if (true == ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point, .ThisColType = ButtonCollisionType }))
    {
        if (true == GameEngineInput::IsDown("EngineMouseLeft") && nullptr != ClickPtr)
        {
            ClickPtr();
        }
    }

    switch (State)
    {
    case ButtonState::Release:
        CurImageName = ReleaseImageName;
        Render->SetImage(ReleaseImageName);
        break;
    case ButtonState::Press:
        CurImageName = PressImageName;
        Render->SetImage(PressImageName);
        break;
    case ButtonState::Hover:
        CurImageName = HoverImageName;
        Render->SetImage(HoverImageName);
        break;
    default:
        break;
    }
}