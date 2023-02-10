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
    ButtonRender = CreateRender();
    ButtonCollision = CreateCollision();
}

void Button::SetRenderOrder(int _Value)
{
    ButtonRender->SetOrder(_Value);
}

void Button::SetScale(float4 _Scale)
{
    Scale = _Scale;
    ButtonCollision->SetScale(Scale);
    // Render->SetScale(_Scale);
}

void Button::Update(float _DeltaTime)
{
    State = ButtonState::Release;

    if (true == ButtonCollision->Collision({ .TargetGroup = PointTargetGroup, .TargetColType = CollisionType::CT_Point, .ThisColType = ButtonCollisionType }))
    {
        if (true == GameEngineInput::IsUp("EngineMouseLeft") && nullptr != ClickPtr)
        {
            ClickPtr();
        }
        else if (true == GameEngineInput::IsFree("EngineMouseLeft"))
        {
            State = ButtonState::Hover;
        }
        else if (true == GameEngineInput::IsPress("EngineMouseLeft"))
        {
            State = ButtonState::Press;
        }
    }

    switch (State)
    {
    case ButtonState::Release:
        CurImageName = ReleaseImageName;
        ButtonRender->SetImage(ReleaseImageName);
        ButtonRender->SetScale(Scale);
        break;
    case ButtonState::Press:
        CurImageName = PressImageName;
        ButtonRender->SetImage(PressImageName);
        ButtonRender->SetScale(Scale);
        break;
    case ButtonState::Hover:
        CurImageName = HoverImageName;
        ButtonRender->SetImage(HoverImageName);
        ButtonRender->SetScale(Scale);
        break;
    default:
        break;
    }
}