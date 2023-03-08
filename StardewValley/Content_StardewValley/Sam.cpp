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
        TextBoxOnOff(_DeltaTime, " ���� �����ϱ� ���� �����ݾ�! �ȱ׷�? ", "����! �̰� ���� ���� �����ϴ� �ž�! ", " �� ���� �� �𸣴±���, ��ġ? ");
    }
}

void Sam::Render(float _Time)
{

}