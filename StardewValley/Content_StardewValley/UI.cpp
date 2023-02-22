
#include <string>
#include <time.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "UI.h"
#include "globalValue.h"

UI* UI::GlobalUI = nullptr;

UI::UI()
{
    GlobalUI = this;
    globalValue::AddUIToList(this);
}

UI::~UI()
{
}

void UI::Start()
{
    StartTime = clock();

    CameraPos = GetLevel()->GetCameraPos();

    TimeBar = CreateRender("TimeBar.BMP", 200);
    TimeBar->SetScaleToImage();

    StatusBar = CreateRender("StatusBar.BMP", 200);
    StatusBar->SetScaleToImage();

    Screensize = GameEngineWindow::GetScreenSize();

    MoneyRender.SetOwner(this);
    MoneyRender.SetImage("Number2.bmp", { 18,24 }, 250, RGB(255, 255, 255), "Number2.bmp");
    MoneyRender.SetValue(0);
    MoneyRender.SetAlign(Align::Right);
    MoneyRender.SetCameraEffect(true);
}

void UI::Update(float _DeltaTime)
{
    //UI��ġ�� ������ �� ����(ī�޶���ġ, ��ũ���� ũ�� ��) ���ʼ���  
    CameraPos = GetLevel()->GetCameraPos();

    //ȭ�� ������� �ð�ǥ��â
    TimeBar->SetPosition({ CameraPos.x + Screensize.x - 108.0f , CameraPos.y + 85.0f });

    //ȭ�� �����ϴ� ü�¹�
    StatusBar->SetPosition({ CameraPos.x + Screensize.x - 36.5f, CameraPos.y + Screensize.y - 87.5f });

    //
    MoneyRender.SetRenderPos({ CameraPos.x + Screensize.x - 32.0f, CameraPos.y + 150.0f });
    
    MoneyRender.SetValue(globalValue::GetMoney());
}

void UI::Render(float _Time)
{
}

void UI::UI_ONOFF()
{
    if (TimeBar->IsUpdate() == true)
    {
        TimeBar->Off();
        StatusBar->Off();
    }
    else
    {
        TimeBar->On();
        StatusBar->On();
    }
}

void UI::RenderMoney(int _Money)
{
    
}