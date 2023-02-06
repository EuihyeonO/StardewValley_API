
#include <string>
#include <time.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "UI.h"

UI* UI::GlobalUI = nullptr;

UI::UI()
{
    GlobalUI = this;
}

UI::~UI()
{
}

void UI::Start()
{
    StartTime = clock();

    CameraPos = GetLevel()->GetCameraPos();

    Quickslot = CreateRender("QuickSlot.BMP", 2);
    TimeBar = CreateRender("TimeBar.BMP", 2);
    StatusBar = CreateRender("StatusBar.BMP", 2);
}

void UI::Update(float _DeltaTime)
{

    //UI��ġ�� ������ �� ����(ī�޶���ġ, ��ũ���� ũ�� ��) ���ʼ���
    float4 Screensize = GameEngineWindow::GetScreenSize();
    CameraPos = GetLevel()->GetCameraPos();

    //ȭ�� �ϴ��߾� ������

    Quickslot->SetPosition({ CameraPos.x + (Screensize.x / 2.0f) , CameraPos.y + Screensize.y - 45.0f });
    Quickslot->SetScaleToImage();

    //ȭ�� ������� �ð�ǥ��â
    TimeBar->SetPosition({ CameraPos.x + Screensize.x - 108.0f , CameraPos.y + 85.0f });
    TimeBar->SetScaleToImage();

    //ȭ�� �����ϴ� ü�¹�
    StatusBar->SetPosition({ CameraPos.x + Screensize.x - 36.5f, CameraPos.y + Screensize.y - 87.5f });
    StatusBar->SetScaleToImage();
    
    //���� ��ܿ� �ð� ǥ��
    {
        HDC hdc = GameEngineWindow::GetWindowBackBufferHdc();
        EndTime = clock();

        size_t mytime = EndTime - StartTime;
        if (mytime >= 1000)
        {
            GlobalTime += 1;
            StartTime = clock();
        }

        time = std::to_string(GlobalTime) + "��";

        // �ڵ�  X��ǥ Y��ǥ ���ڿ� ���ڿ�����
        TextOut(hdc, 1150, 20, time.c_str(), time.size());
        SetBkMode(hdc, TRANSPARENT);
    }
}

void UI::Render(float _Time)
{
}

void UI::UI_ONOFF()
{
    if (Quickslot->IsUpdate() == true)
    {
        Quickslot->Off();
        TimeBar->Off();
        StatusBar->Off();
    }
    else
    {
        Quickslot->On();
        TimeBar->On();
        StatusBar->On();
    }
}