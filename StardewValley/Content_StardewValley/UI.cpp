
#include <string>
#include <time.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "UI.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "Player.h"

UI* UI::GlobalUI = nullptr;

UI::UI()
{
    GlobalUI = this;
    globalInterface::AddUIToList(this);
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

    HPbar = CreateRender("HP.bmp", 201);
    HPbar->SetScaleToImage();

    Energybar = CreateRender("Energy.bmp", 201);
    Energybar ->SetScaleToImage();

    Screensize = GameEngineWindow::GetScreenSize();

    StatusBar->EffectCameraOff();
    HPbar->EffectCameraOff();
    TimeBar->EffectCameraOff();
    Energybar->EffectCameraOff();

    MoneyRender.SetOwner(this);
    MoneyRender.SetImage("NumberBig.bmp", { 18,24 }, 250, RGB(134, 134, 134), "NumberBig.bmp");
    MoneyRender.SetValue(0);
    MoneyRender.SetAlign(Align::Right);
    MoneyRender.SetCameraEffect(false);

    DayRender.SetOwner(this);
    DayRender.SetImage("NumberSmall.bmp", { 16,24 }, 250, RGB(134, 134, 134), "NumberSmall.bmp");
    DayRender.SetValue(0);
    DayRender.SetAlign(Align::Right);
    DayRender.SetCameraEffect(false);

    UIPosUpdate();
}

void UI::Update(float _DeltaTime)
{
    RenderMoney();  
    RenderDay();
    RenderHp();
    RenderEnergy();
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

void UI::RenderMoney()
{
    MoneyRender.SetValue(globalValue::GetMoney());
}

void UI::RenderDay()
{
    DayRender.SetValue(globalValue::GetDay());
}

void UI::UIPosUpdate()
{
    SetPos(CameraPos + Screensize.half());

    CameraPos = GetLevel()->GetCameraPos();

    //화면 우측상단 시간표시창
    TimeBar->SetPosition({ Screensize.hx() - 108.0f , 85.0f - Screensize.hy()});

    //화면 우측하단 체력바
    StatusBar->SetPosition({ Screensize.hx() - 36.5f, Screensize.hy() - 87.5f});

    //체력, 기력바
    HPbarPos = StatusBar->GetPosition() + float4{ 19, 18 } + float4{ 0, 64 };
    EnergybarPos = StatusBar->GetPosition() + float4{ -19, 18 } + float4{ 0, 64 };

    HPbar->SetPosition(HPbarPos + float4{ 0, -Energybar->GetScale().hy() });
    Energybar->SetPosition(EnergybarPos + float4{ 0, -Energybar->GetScale().hy() });

    //돈, 날짜 표시
    GlobalUI->DayRender.SetRenderPos({Screensize.hx() - 77.0f,  + 30.0f - Screensize.hy()});
    GlobalUI->MoneyRender.SetRenderPos({ Screensize.hx() - 32.0f, -Screensize.hy() + 150.0f });
}

void UI::SetUIpos(float4 _pos)
{
    float4 Screensize = GlobalUI->Screensize;

    GlobalUI->TimeBar->SetPosition({ _pos.x + Screensize.x - 108.0f , _pos.y + 85.0f });

    //화면 우측하단 체력바
    GlobalUI->StatusBar->SetPosition({ _pos.x + Screensize.x - 36.5f, _pos.y + Screensize.y - 87.5f });

    //돈, 날짜 표시
    GlobalUI->DayRender.SetRenderPos({ _pos.x + Screensize.x - 77.0f, _pos.y + 30.0f });

    GlobalUI->MoneyRender.SetRenderPos({ _pos.x + Screensize.x - 32.0f, _pos.y + 150.0f });
}

void UI::RenderHp()
{
    int HP = globalValue::GetHP();
    HPbar->SetScale({ HPbar->GetScale().x, static_cast<float>(HP)});
    HPbar->SetPosition(HPbarPos + float4{ 0, -HPbar->GetScale().hy() });
}

void UI::RenderEnergy()
{
    int Energy = globalValue::GetEnergy();
    Energybar->SetScale({Energybar->GetScale().x, static_cast<float>(Energy)});
    Energybar->SetPosition(EnergybarPos + float4{ 0, -Energybar->GetScale().hy() });
}