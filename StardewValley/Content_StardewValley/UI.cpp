
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

    //UI위치의 기준이 될 값들(카메라위치, 스크린의 크기 등) 기초설정
    float4 Screensize = GameEngineWindow::GetScreenSize();
    CameraPos = GetLevel()->GetCameraPos();

    //화면 하단중앙 퀵슬롯

    Quickslot->SetPosition({ CameraPos.x + (Screensize.x / 2.0f) , CameraPos.y + Screensize.y - 45.0f });
    Quickslot->SetScaleToImage();

    //화면 우측상단 시간표시창
    TimeBar->SetPosition({ CameraPos.x + Screensize.x - 108.0f , CameraPos.y + 85.0f });
    TimeBar->SetScaleToImage();

    //화면 우측하단 체력바
    StatusBar->SetPosition({ CameraPos.x + Screensize.x - 36.5f, CameraPos.y + Screensize.y - 87.5f });
    StatusBar->SetScaleToImage();
    
    //우측 상단에 시간 표시
    {
        HDC hdc = GameEngineWindow::GetWindowBackBufferHdc();
        EndTime = clock();

        size_t mytime = EndTime - StartTime;
        if (mytime >= 1000)
        {
            GlobalTime += 1;
            StartTime = clock();
        }

        time = std::to_string(GlobalTime) + "초";

        // 핸들  X좌표 Y좌표 문자열 문자열길이
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