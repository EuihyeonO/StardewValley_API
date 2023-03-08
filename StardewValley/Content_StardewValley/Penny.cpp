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
        TextBoxOnOff(_DeltaTime, "������ ������ �� ���׿�. \n ���̵��� ���� �����ϰھ��. ", "������. �� �̰� ���� ����ϴµ�! ", " ��.. ������ �����Կ�. ");
    }
}
void Penny::Render(float _Time)
{

}