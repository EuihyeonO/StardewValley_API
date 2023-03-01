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
    SamRender = CreateRender("Sam.bmp", 100);
    SamRender->SetScaleToImage();
    SamRender->SetPosition({ 300, 600 });
}

void Sam::Update(float _DeltaTime)
{
}

void Sam::Render(float _Time)
{

}