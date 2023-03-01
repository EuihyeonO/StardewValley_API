#include "Marlon.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "globalInterface.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/Button.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

Marlon::Marlon()
{
}

Marlon::~Marlon()
{
}

void GiveHammer(Button* _btn)
{
    globalInterface::CreateItemToAllInventory("HammerIcon.bmp", static_cast<int>(ItemType::Hammer));
}

void Marlon::Start()
{
    MarlonRender = CreateRender("Marlon.bmp", 30);
    MarlonRender->SetScaleToImage();
    MarlonRender->SetPosition({ 835, 440 });

    MarlonText = CreateRender("MarlonTextBox.bmp", 250);
    MarlonText->Off();
    MarlonText->EffectCameraOff();
    MarlonText->SetPosition({ 640, 568 });

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
    OkayButton->SetPos(GetLevel()->GetCameraPos() + float4{440, 650});
    OkayButton->SetRenderOrder(300);
    OkayButton->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    OkayButton->GetButtonRender()->Off();

    OkayButton->SetClickCallBack(GiveHammer);
}

void Marlon::Update(float _DeltaTime)
{
    isCollision();
    isInteract();
    
    if (isCollided == true && isKeyInteract == true)
    {
        TextBoxOn(_DeltaTime);
    }
    else if (isKeyInteract == false)
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

void Marlon::isInteract()
{
    if (GameEngineInput::IsDown("KeyInteract") == true)
    {
        if (isKeyInteract == false) 
        {
            isKeyInteract = true;
        }
        else
        {
            isKeyInteract = false;
        }
    }
}

void Marlon::TextBoxOn(float _DeltaTime)
{
    Player::GetPlayer()->PlayerStop();

    MarlonText->On();
    MarlonTextShadow->On();

    if (isButtonOn == true)
    {
        OkayButton->GetButtonRender()->On();
        OkayButton->SetPos(GetLevel()->GetCameraPos() + float4{440, 620});
    }

    Scale.x += 1280.0f * 3 * _DeltaTime;
    Scale.y += 400.0f * 3 * _DeltaTime;

    if (Scale.x >= 1280)
    {
        Scale.x = 1280;
        isButtonOn = true;
    }
    if (Scale.y >= 400)
    {
        Scale.y = 400;
    }

    MarlonText->SetScale(Scale);
    MarlonTextShadow->SetScale(Scale);
}

void Marlon::TextBoxOff()
{
    Player::GetPlayer()->PlayerStopOff();
    MarlonText->Off();
    MarlonTextShadow->Off();

    isButtonOn = false;

    if(isButtonOn == false)
    {
        OkayButton->GetButtonRender()->Off();
    }

    Scale = { 0,0 };

    MarlonText->SetScale(Scale);
    MarlonTextShadow->SetScale(Scale);
}