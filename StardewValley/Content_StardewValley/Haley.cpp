#include "Haley.h"
#include "ContentsEnum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
Haley::Haley()
{
}

Haley::~Haley()
{
}

void Haley::Start()
{
    SetBodyRender("Haley.bmp", { 450, 270 });
    SetCollision();
}

void Haley::Update(float _DeltaTime)
{
    RenderOrderUpdate();
}

void Haley::Render(float _Time)
{
}
