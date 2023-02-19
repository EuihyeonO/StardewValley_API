
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
}

void UI::Update(float _DeltaTime)
{

    //UI��ġ�� ������ �� ����(ī�޶���ġ, ��ũ���� ũ�� ��) ���ʼ���  
    CameraPos = GetLevel()->GetCameraPos();

    //ȭ�� ������� �ð�ǥ��â
    TimeBar->SetPosition({ CameraPos.x + Screensize.x - 108.0f , CameraPos.y + 85.0f });

    //ȭ�� �����ϴ� ü�¹�
    StatusBar->SetPosition({ CameraPos.x + Screensize.x - 36.5f, CameraPos.y + Screensize.y - 87.5f });        
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