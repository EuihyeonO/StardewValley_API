#include "Sam.h"

#include <GameEngineCore/GameEngineRender.h>
Sam::Sam()
{
}

Sam::~Sam()
{
}

void Sam::Start()
{
    SetBodyRender("Sam.bmp", { 300, 600 });
    SetCollision();
}

void Sam::Update(float _DeltaTime)
{
    RenderOrderUpdate();
}

void Sam::Render(float _Time)
{

}