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
    SetName("Haley");
    SetTextRender();
}

void Haley::Update(float _DeltaTime)
{
    RenderOrderUpdate();
    InteractUpdate();
    TextBoxOnOff(_DeltaTime, "이 촌구석은 참 맘에 안들지만, 사진을 찍기에는 좋아. ", "우와 이거 좋아하는거 어떻게 알았어? 너무 고마워! ", " 이딴걸 줘서 뭐 어쩌라는거야? ");
}

void Haley::Render(float _Time)
{
}
