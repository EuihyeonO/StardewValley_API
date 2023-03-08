#include "Title.h"
#include "Player.h"
#include "ContentsCore.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/Button.h>

#include <iostream>

Title* Title::globalTitle = nullptr;

Title::Title()
{
    globalTitle = this;
}

Title::~Title()
{
}

void Title::Start()
{
   
    ObjectInit();
    ButtonInit();
}

void Title::Update(float _DeltaTime)
{
    FadeOut(_DeltaTime);
    ChangeLevelToHouse();

    SetObjectAlpha(_DeltaTime);
    
    ObjectMove(_DeltaTime);
    CloudReSet();

    TimeCount();

    if (isSet == 1)
    {
        if (GetLevel()->GetCameraPos().y > 0)
        {
            MoveMountain(_DeltaTime);
        }

        else if(GetLevel()->GetCameraPos().y <= 0)
        {
            GetLevel()->SetCameraPos({ 0,0 });
            isCameraSet = 1;
        }
    }

    if (isCameraSet == 1)
    {
        if (mytime >= 25)
        {
            NewGame->GetButtonCollision()->On();
            NewGame->GetButtonRender()->On();

            if (false == isNewButtonSoundOn)
            {
                GameEngineResources::GetInst().SoundPlay("ButtonOn.wav");
                isNewButtonSoundOn = true;
            }
        }

        if (mytime >= 25.25)
        {
            ExitGame->GetButtonCollision()->On();
            ExitGame->GetButtonRender()->On();

            if (false == isExitButtonSoundOn)
            {
                GameEngineResources::GetInst().SoundPlay("ButtonOn.wav");
                isExitButtonSoundOn = true;
            }
        }
    }

    if (false == GameEngineInput::IsKey("LevelChange"))
    {
        GameEngineInput::CreateKey("LevelChange", 'P');
    }

    if (true == GameEngineInput::IsDown("LevelChange"))
    {
        ContentsCore::SetNextMap("Farm");
    }

}

void Title::Render(float _Time)
{


}

void Title::ObjectInit()
{
    intro1 = CreateRender("intro1.bmp", 0);
    intro1->SetScaleToImage();
    intro1->SetPosition({ 0,0 });
    intro1->GetImage()->GetImageScale().half();
    intro1->SetAlpha(0);
    IntroScale = intro1->GetImage()->GetImageScale();

    TitleName = CreateRender("TitleName.BMP", 5);
    TitleName->SetScaleToImage();
    TitleName->SetPosition({ 0, -480 });

    TitleMountain2 = CreateRender("TitleMountain2.bmp", 3);
    TitleMountain2->SetScaleToImage();
    TitleMountain2->SetPosition({ -100,IntroScale.hy() - 238.0f });
    TitleMountain2->SetAlpha(0);

    TitleMountain1 = CreateRender("TitleMountain1.bmp", 4);
    TitleMountain1->SetScaleToImage();
    TitleMountain1->SetPosition({ 0,IntroScale.hy() - 213.0f });
    TitleMountain1->SetAlpha(0);

    Cloud1 = CreateRender("Cloud1.bmp", 2);
    Cloud1->SetScaleToImage();
    Cloud1->SetPosition({ 0,-100 });
    Cloud1->SetAlpha(0);

    Cloud2 = CreateRender("Cloud2.bmp", 2);
    Cloud2->SetScaleToImage();
    Cloud2->SetPosition({ 300, -500 });
    Cloud2->SetAlpha(0);

    Cloud3 = CreateRender("Cloud3.bmp", 2);
    Cloud3->SetScaleToImage();
    Cloud3->SetPosition({ 500, -300 });
    Cloud3->SetAlpha(0);

    Cloud4 = CreateRender("Cloud4.bmp", 3);
    Cloud4->SetScaleToImage();
    Cloud4->SetPosition({ 500, -300 });
    Cloud4->SetAlpha(0);

    Cloud5 = CreateRender("Cloud5.bmp", 3);
    Cloud5->SetScaleToImage();
    Cloud5->SetPosition({ 500, -460 });
    Cloud5->SetAlpha(0);

    Tree = CreateRender("TitleTree.bmp", 5);
    Tree->SetScaleToImage();
    Tree->SetPosition({ 0,IntroScale.hy() - 200.0f });
    Tree->SetAlpha(0);

    Bird1 = CreateRender("Bird.bmp", 5);
    Bird1->CreateAnimation({ .AnimationName = "BirdFlying1",.ImageName = "Bird.bmp",.FrameIndex = {0,1,2,3,4,5},.FrameTime = {0.5,0.5,0.5,0.5,0.5,0.5} });
    Bird1->SetScale({ 52, 36 });
    Bird1->SetAlpha(0);
    Bird1->SetPosition({ 0,IntroScale.hy() - 213.0f });
    Bird1->ChangeAnimation("BirdFlying1");

    Bird2 = CreateRender("Bird.bmp", 5);
    Bird2->CreateAnimation({ .AnimationName = "BirdFlying2",.ImageName = "Bird.bmp",.FrameIndex = {4,5,0,1,2,3},.FrameTime = {0.5,0.5,0.5,0.5,0.5,0.5} });
    Bird2->SetScale({ 52, 36 });
    Bird2->SetAlpha(0);
    Bird2->SetPosition({ 100,IntroScale.hy() - 213.0f });
    Bird2->ChangeAnimation("BirdFlying2");

    BlackImage = CreateRender("BlackMap.bmp", 10000);
    BlackImage->SetScaleToImage();
    BlackImage->SetPosition(-(intro1->GetImage()->GetImageScale().half()) + GameEngineWindow::GetScreenSize().half());
    BlackImage->SetAlpha(0);

    GetLevel()->SetCameraPos({ 0, IntroScale.y - 768 });

    SetPos(IntroScale.half());
}


void Title::CloudReSet()
{
    if (Cloud1->GetActorPlusPos().x <= -(Cloud1->GetScale().hx()))
    {
        Cloud1->SetPosition({ 640 + Cloud1->GetScale().hx() , Cloud1->GetPosition().y });
    }

    if (Cloud2->GetActorPlusPos().x <= -(Cloud2->GetScale().hx()))
    {
        Cloud2->SetPosition({ 640 + Cloud2->GetScale().hx() , Cloud2->GetPosition().y });
    }

    if (Cloud3->GetActorPlusPos().x <= -(Cloud3->GetScale().hx()))
    {
        Cloud3->SetPosition({ 640 + Cloud3->GetScale().hx() , Cloud3->GetPosition().y });
    }

    if (Cloud4->GetActorPlusPos().x <= -(Cloud4->GetScale().hx()))
    {
        Cloud4->SetPosition({ 640 + Cloud4->GetScale().hx() , Cloud4->GetPosition().y });
    }

    if (Cloud5->GetActorPlusPos().x <= -(Cloud5->GetScale().hx()))
    {
        Cloud5->SetPosition({ 640 + Cloud5->GetScale().hx() , Cloud5->GetPosition().y });
    }
}

void Title::SetObjectAlpha(float _DeltaTime)
{
    if (Alpha >= 255)
    {
        Alpha = 255;
        isSet = 1;
    }
    else if (Alpha < 255)
    {
        Alpha += (_DeltaTime * 50);
    }

    TitleMountain1->SetAlpha(static_cast<int>(Alpha));
    TitleMountain2->SetAlpha(static_cast<int>(Alpha));
    intro1->SetAlpha(static_cast<int>(Alpha));
    Tree->SetAlpha(static_cast<int>(Alpha));
    Bird1->SetAlpha(static_cast<int>(Alpha));
    Bird2->SetAlpha(static_cast<int>(Alpha));

    if (Alpha < 150)
    {
        Cloud1->SetAlpha(static_cast<int>(Alpha));
        Cloud2->SetAlpha(static_cast<int>(Alpha));
        Cloud3->SetAlpha(static_cast<int>(Alpha));
        Cloud4->SetAlpha(static_cast<int>(Alpha));
        Cloud5->SetAlpha(static_cast<int>(Alpha));
    }
}

void Title::ObjectMove(float _DeltaTime)
{
    Bird1->SetMove({ float4::Left * _DeltaTime * 15.0f });
    Bird2->SetMove({ float4::Left * _DeltaTime * 15.0f });

    Cloud1->SetMove({ float4::Left * _DeltaTime * 25.0f });
    Cloud2->SetMove({ float4::Left * _DeltaTime * 30.0f });
    Cloud3->SetMove({ float4::Left * _DeltaTime * 55.0f });
    Cloud4->SetMove({ float4::Left * _DeltaTime * 75.0f });
    Cloud5->SetMove({ float4::Left * _DeltaTime * 80.0f });
}

void Title::TimeCount()
{
    if (isSet >= 1)
    {
        CurTime = clock();
        mytime += (CurTime - PrevTime) / 1000;
        PrevTime = CurTime;
    }
}

void Title::MoveMountain(float _DeltaTime)
{
    if (GetLevel()->GetCameraPos().y > 0)
    {
        if (mytime >= 7 && mytime < 9)
        {

            GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

            TitleMountain1->SetMove(float4::Up * _DeltaTime * 15.0f);
            TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);
            Tree->SetMove(float4::Up * _DeltaTime * 5.0f);
        }
        else if (mytime >= 9 && mytime < 11)
        {
            GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

            Accel1 += _DeltaTime;

            TitleMountain1->SetMove(float4::Up * _DeltaTime * 15.0f);
            TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);
            Tree->SetMove(float4::Down * Accel1 * 0.3f);
        }
        else if (mytime >= 11 && mytime < 13)
        {
            Accel2 += _DeltaTime;

            GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

            TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);

            TitleMountain1->SetMove(float4::Down * Accel2 * 0.3f);
            Tree->SetMove(float4::Down * Accel1 * 0.3f);
        }
        else if (mytime >= 13)
        {
            Accel3 += _DeltaTime;

            GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

            TitleMountain2->SetMove(float4::Down * Accel3 * 0.3f);
            TitleMountain1->SetMove(float4::Down * Accel2 * 0.3f);
        }
    }
}


void ChangeLevel(Button* _btn)
{
    GameEngineResources::GetInst().SoundPlay("ClickButton.wav");
    Title::GetGlobalTitle()->SetIsClicked();
}

void ExitThisGame(Button* _Btn)
{
    exit(0);
}

void Title::ButtonInit()
{
    NewGame = GetLevel()->CreateActor<Button>();
    NewGame->SetReleaseImage("newgamebutton.bmp");
    NewGame->SetHoverImage("newgamebuttonHover.bmp");
    NewGame->SetPressImage("newgamebuttonHover.bmp");
    NewGame->SetScale({ 222, 174 });
    NewGame->SetRenderOrder(10);
    NewGame->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    NewGame->SetPos(IntroScale.half() - float4(200, 100));
    NewGame->GetButtonCollision()->Off();
    NewGame->GetButtonRender()->Off();
    NewGame->SetClickCallBack(ChangeLevel);

    ExitGame = GetLevel()->CreateActor<Button>();
    ExitGame->SetReleaseImage("ExitButton.bmp");
    ExitGame->SetHoverImage("ExitButtonHover.bmp");
    ExitGame->SetPressImage("ExitButtonHover.bmp");
    ExitGame->SetScale({ 222, 174 });
    ExitGame->SetRenderOrder(10);
    ExitGame->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    ExitGame->SetPos(IntroScale.half() + float4(200, -100));
    ExitGame->GetButtonCollision()->Off();
    ExitGame->GetButtonRender()->Off();
    ExitGame->SetClickCallBack(ExitThisGame);
}


void Title::FadeOut(float _DeltaTime)
{

    if (BlackAlpha >= 255)
    {
        BlackAlpha = 255;
    }

    if (BlackAlpha < 255 && isClicked == true)
    {
        BlackAlpha += 1.0f;
        BlackImage->SetAlpha(BlackAlpha);
    }
}

void Title::SetIsClicked()
{
    isClicked = true;
}

void Title::ChangeLevelToHouse()
{
    if (BlackAlpha >= 255) 
    {
        if (mytime >= 10)
        {
            BlackAlpha = 255;
            mytime = 0;
        }

        if (mytime >= 2)
        {
            BlackAlpha = 255;
            ContentsCore::SetNextMap("House");
        }
    }
}