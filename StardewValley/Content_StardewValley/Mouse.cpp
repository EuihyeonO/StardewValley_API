#include "Mouse.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
    GameEngineRender* render = CreateRender("Cursor.bmp", 205);
    render->SetScaleToImage();

    GameEngineCollision* collision = CreateCollision(static_cast<int>(ActorType::Mouse));
    SetPos(GetLevel()->GetMousePosToCamera());
    collision->SetPosition(float4{-20,-20 });
    ShowCursor(false);

    collision->SetScale({ 5, 5 });
}

void Mouse::Update(float _DeltaTime)
{
    SetPos(GetLevel()->GetMousePosToCamera());
}

void Mouse::Render(float _Time)
{

}