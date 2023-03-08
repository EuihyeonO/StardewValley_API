#include "Sam.h"
#include "globalInterface.h"

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
    SetName("Sam");
    SetTextRender();
}

void Sam::Update(float _DeltaTime)
{
    RenderOrderUpdate();

    if (false == globalInterface::isMenuOpen())
    {
        InteractUpdate();
        TextBoxOnOff(_DeltaTime, " 정말 공연하기 좋은 날씨잖아! 안그래? ", "오예! 이거 내가 제일 좋아하는 거야! ", " 넌 정말 뭘 모르는구나, 그치? ");
    }
}

void Sam::Render(float _Time)
{

}