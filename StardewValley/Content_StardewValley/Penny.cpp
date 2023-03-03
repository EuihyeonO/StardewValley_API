#include "Penny.h"

#include <GameEngineCore/GameEngineRender.h>
Penny::Penny()
{
}

Penny::~Penny()
{
}

void Penny::Start()
{
    SetBodyRender("Penny.bmp", {1025, 770});
    SetCollision();
}
void Penny::Update(float _DeltaTime)
{
    RenderOrderUpdate();
}
void Penny::Render(float _Time)
{

}