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
    PennyRender = CreateRender("Penny.bmp", 100);
    PennyRender->SetScaleToImage();
    PennyRender->SetPosition({ 1025, 770 });
}
void Penny::Update(float _DeltaTime)
{

}
void Penny::Render(float _Time)
{

}