#include "Lewis.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "globalInterface.h"

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
    SetName("Lewis");
    SetTextRender();
}
void Lewis::Update(float _DeltaTime)
{
    RenderOrderUpdate();

    if (false == globalInterface::isMenuOpen())
    {
        InteractUpdate();
        TextBoxOnOff(_DeltaTime, " 농사를 짓고 열심히 사는 것도 좋지만, \n  가끔 동네를 돌아보는 것도 좋단다. ", "아니 이 귀한걸.. 고맙네! ", " 보기만 해도 기분나빠지는 물건이군.. ");
    }
}
void Lewis::Render(float _Time)
{

}
