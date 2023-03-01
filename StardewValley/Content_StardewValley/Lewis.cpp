#include "Lewis.h"

#include <GameEngineCore/GameEngineRender.h>

Lewis::Lewis()
{
}

Lewis::~Lewis()
{
}

void Lewis::Start()
{
    LewisRender = CreateRender("Lewis.bmp", 100);
    LewisRender->SetScaleToImage();
    LewisRender->SetPosition({ 1600, 1250 });
}
void Lewis::Update(float _DeltaTime)
{

}
void Lewis::Render(float _Time)
{

}