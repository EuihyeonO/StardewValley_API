#include "Lewis.h"
#include "ContentsEnum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

Lewis::Lewis()
{
}

Lewis::~Lewis()
{
}

void Lewis::Start()
{
    SetBodyRender("Lewis.bmp", {1600, 1270});
    SetCollision();

}
void Lewis::Update(float _DeltaTime)
{
    RenderOrderUpdate();
}
void Lewis::Render(float _Time)
{

}
