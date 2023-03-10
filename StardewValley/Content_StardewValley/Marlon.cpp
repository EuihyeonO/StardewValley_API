#include "Marlon.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "globalSound.h"
#include "globalInterface.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/Button.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <time.h>

Marlon* Marlon::GlobalMarlon = nullptr;

Marlon::Marlon()
{
    GlobalMarlon = this;
}

Marlon::~Marlon()
{
}

void GiveHammer(Button* _btn)
{
    globalInterface::CreateItemToAllInventory("HammerIcon.bmp", static_cast<int>(ItemType::Hammer));
    Marlon::GetGlobalMarlon()->TextBoxOff();
    Player::GetPlayer()->GetItem("HammerIcon.bmp");
    GameEngineResources::GetInst().SoundPlay("GetItem.wav");
}

void refusing(Button* _btn)
{
    Marlon::GetGlobalMarlon()->TextBoxOff();
}

void Marlon::Start()
{

    MarlonT = CreateRender(10000);
    MarlonT->SetText(" ");

    MarlonRender = CreateRender("Marlon.bmp", 30);
    MarlonRender->SetScaleToImage();
    MarlonRender->SetPosition({ 835, 440 });

    MarlonText = CreateRender("MarlonTextBox.bmp", 250);
    MarlonText->Off();
    MarlonText->EffectCameraOff();
    MarlonText->SetPosition({ 640, 568 });

    MarlonSecondText = CreateRender("MarlonTextBox2.bmp", 250);
    MarlonSecondText->SetScaleToImage();
    MarlonSecondText->SetPosition({ 640, 568 });
    MarlonSecondText->Off();
    MarlonSecondText->EffectCameraOff();

    MarlonTextShadow = CreateRender("TextBoxShodow.bmp", 250);
    MarlonTextShadow->Off();
    MarlonTextShadow->EffectCameraOff();
    MarlonTextShadow->SetPosition({ 640, 568 });
    MarlonTextShadow->SetAlpha(100);

    MarlonCollision = CreateCollision(ActorType::NPC);
    MarlonCollision->SetScale(MarlonRender->GetScale());
    MarlonCollision->SetPosition({ 835, 440 });

    OkayButton = GetLevel()->CreateActor<Button>();
    OkayButton->SetReleaseImage("SelectedButtonRelease.bmp");
    OkayButton->SetHoverImage("SelectedButton.bmp");
    OkayButton->SetPressImage("SelectedButton.bmp");
    OkayButton->SetScale({ 798, 64 });
    OkayButton->SetPos(GetLevel()->GetCameraPos() + float4{440, 620});
    OkayButton->SetRenderOrder(300);
    OkayButton->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    OkayButton->GetButtonRender()->Off();
    OkayButton->GetButtonCollision()->Off();

    OkayButton->SetClickCallBack(GiveHammer);  
    
    NoButton = GetLevel()->CreateActor<Button>();
    NoButton->SetReleaseImage("SelectedButtonRelease.bmp");
    NoButton->SetHoverImage("SelectedButton.bmp");
    NoButton->SetPressImage("SelectedButton.bmp");
    NoButton->SetScale({ 798, 64 });
    NoButton->SetPos(GetLevel()->GetCameraPos() + float4{440, 694});
    NoButton->SetRenderOrder(300);
    NoButton->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    NoButton->GetButtonRender()->Off();
    NoButton->GetButtonCollision()->Off();

    NoButton->SetClickCallBack(refusing);
}

void Marlon::Update(float _DeltaTime)
{
    isCollision();
    isDownKeyInteract();

    if (true == isCollided && true == isKeyInteract)
    {
        TextBoxOn(_DeltaTime);
    }

    if (true == isSetText && true == GameEngineInput::IsDown("KeyInteract"))
    {
        TextBoxOff();
    }

}

void Marlon::Render(float _Time)
{
}

void Marlon::isCollision()
{
    if (true == MarlonCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::PlayerInteract), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        isCollided = true;
    }
    else
    {
        isCollided = false;
    }
}

void Marlon::isDownKeyInteract()
{
    if (true == isCollided && GameEngineInput::IsDown("KeyInteract") == true)
    {
        if (isKeyInteract == false) 
        {
            isKeyInteract = true;
        }
    }
}

void Marlon::TextBoxOn(float _DeltaTime)
{


    Player::GetPlayer()->PlayerStop();
    std::string Dir = Player::GetPlayer()->GetDir();
    Player::ChangePlayerIdle(Dir);

    Scale.x += 1280.0f * 8.0f * _DeltaTime;
    Scale.y += 400.0f * 8.0f * _DeltaTime;

    if (Scale.x >= 1280)
    {
        Scale.x = 1280;


        isButtonOn = true;
        isSetText = true;

        TextOn();
    }

    if (Scale.y >= 400)
    {
        Scale.y = 400;
    }


    if (globalInterface::IsInInventory("HammerIcon.bmp") == false)
    {

        MarlonText->On();
        MarlonTextShadow->On();

        MarlonText->SetScale(Scale);
        MarlonTextShadow->SetScale(Scale);

        if (isButtonOn == true)
        {
            OkayButton->GetButtonRender()->On();
            OkayButton->GetButtonCollision()->On();
            OkayButton->SetPos(GetLevel()->GetCameraPos() + float4{ 440, 620 });

            NoButton->GetButtonRender()->On();
            NoButton->GetButtonCollision()->On();
            NoButton->SetPos(GetLevel()->GetCameraPos() + float4{ 440, 684 });
        }
    }

    else
    {

        MarlonSecondText->On();
        MarlonTextShadow->On();

        MarlonSecondText->SetScale(Scale);
        MarlonTextShadow->SetScale(Scale);
    }
}

void Marlon::TextBoxOff()
{
    TextOff();

    if (isSetText == true)
    {
        GameEngineResources::GetInst().SoundPlay("TalkBoxOff.wav");
    }

    isSetText = false;

    Player::GetPlayer()->PlayerStopOff();

    if (MarlonSecondText->IsUpdate() == false) 
    {
        MarlonText->Off();
        MarlonTextShadow->Off();

        isButtonOn = false;

        if (isButtonOn == false)
        {
            OkayButton->GetButtonRender()->Off();
            OkayButton->GetButtonCollision()->Off();

            NoButton->GetButtonRender()->Off();
            NoButton->GetButtonCollision()->Off();
        }

        isKeyInteract = false;       
    }

    else if(MarlonSecondText->IsUpdate() == true)
    {
        MarlonSecondText->Off();
        MarlonTextShadow->Off();

        isKeyInteract = false;
    }

    Scale = { 0,0 };
}

bool Marlon::isMarlonTextOn()
{
    if (true == MarlonText->IsUpdate())
    {
        return true;
    }
    else if (true == MarlonSecondText->IsUpdate())
    {
        return true;
    }

    else return false;
}

void Marlon::TextOn()
{
    if (Talk == "" && globalInterface::IsInInventory("HammerIcon.bmp") == false)
    {
        Talk = "?? ???? ???????? ?????????? ?????????? ?? ???? ????? \n ?????? ???? ?????????? ???? ????????. \n ???? ???? ?????? ???? ?????? ?????????? ?? ???? ??????... ";
        prevtime = clock();
    }
    else if (Talk == "" && globalInterface::IsInInventory("HammerIcon.bmp") == true)
    {
        Talk = "?? ???? ???????? ?? ?? ??????..";
        prevtime = clock();
    }
    
    
    Curtime = clock();
    Counttime += (Curtime - prevtime) / 1000;
    CountSoundtime += Counttime;
    prevtime = Curtime;

    MarlonT->SetText(CopyTalk, 50, "Sandoll ????", TextAlign::Left);
    MarlonT->SetPosition({ 35,420 });
    MarlonT->EffectCameraOff();
    MarlonT->SetTextBoxScale({ 1280, 500 });
    MarlonT->On();

    if (Counttime >= 0.01f)
    {
        if (strindex != Talk.size())
        {
            CopyTalk.push_back(Talk[strindex]);
            strindex++;
        }
        Counttime = 0;    
    }

    if (CountSoundtime >= 0.065f)
    {
        if (strindex != Talk.size()) 
        {
            GameEngineResources::GetInst().SoundPlay("TalkBoxOn.wav");
            CountSoundtime = 0;
        }
    }

    if (strindex >= Talk.size())
    {
        isKeyInteract = false;
    }
}

void Marlon::TextOff()
{
    Talk.clear();
    Talk = "";

    CopyTalk.clear();
    CopyTalk = " ";
    strindex = 0;

    MarlonT->Off();
}