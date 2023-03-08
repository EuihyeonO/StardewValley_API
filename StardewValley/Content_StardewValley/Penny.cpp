#include "Penny.h"
#include "globalInterface.h"
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
    SetName("Penny");
    SetTextRender();
}
void Penny::Update(float _DeltaTime)
{
    RenderOrderUpdate();

    if (false == globalInterface::isMenuOpen())
    {
        InteractUpdate();
        TextBoxOnOff(_DeltaTime, "오늘은 날씨가 참 맑네요. \n 아이들이 정말 좋아하겠어요. ", "고마워요. 나 이거 정말 사랑하는데! ", " 뭐.. 마음만 받을게요. ");
    }
}
void Penny::Render(float _Time)
{

}