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
        TextBoxOnOff(_DeltaTime, " ��縦 ���� ������ ��� �͵� ������, \n  ���� ���׸� ���ƺ��� �͵� ���ܴ�. ", "�ƴ� �� ���Ѱ�.. ����! ", " ���⸸ �ص� ��г������� �����̱�.. ");
    }
}
void Lewis::Render(float _Time)
{

}
