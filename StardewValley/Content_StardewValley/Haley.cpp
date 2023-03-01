#include "Haley.h"

#include <GameEngineCore/GameEngineRender.h>
Haley::Haley()
{
}

Haley::~Haley()
{
}

void Haley::Start()
{
    HaleyRender = CreateRender("Haley.bmp", 100);
    HaleyRender->SetScaleToImage();
    HaleyRender->SetPosition({ 450, 270 });
}

void Haley::Update(float _DeltaTime)
{

}

void Haley::Render(float _Time)
{

}