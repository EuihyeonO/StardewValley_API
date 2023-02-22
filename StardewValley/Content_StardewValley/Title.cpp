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


Title::Title()
{
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

    mytime += _DeltaTime;
    
    if (Alpha >= 255)
    {
        Alpha = 255;
        isSet = 1;
    }
    else if(Alpha<255)
    {
        Alpha = mytime * 50;        
    }

    TitleMountain1->SetAlpha(Alpha);
    TitleMountain2->SetAlpha(Alpha);
    intro1->SetAlpha(Alpha);
    Tree->SetAlpha(Alpha);
    Bird1->SetAlpha(Alpha);
    Bird2->SetAlpha(Alpha);


    Bird1->SetMove({ float4::Left * _DeltaTime * 15.0f });
    Bird2->SetMove({ float4::Left * _DeltaTime * 15.0f });

    Cloud1->SetMove({ float4::Left * _DeltaTime * 25.0f });

    if (isSet == 1)
    {
        if(GetLevel()->GetCameraPos().y > 0)
        {
            if (mytime >= 7.5 && mytime < 8)
            {

                GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

                TitleMountain1->SetMove(float4::Up * _DeltaTime * 20.0f);
                TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);
                Tree->SetMove(float4::Up * _DeltaTime * 5.0f);
            }
            else if (mytime >= 8 && mytime <10)
            {
                GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

                Accel1 += _DeltaTime;

                TitleMountain1->SetMove(float4::Up * _DeltaTime * 20.0f);
                TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);
                Tree->SetMove(float4::Down * Accel1 * 0.3f);
            }
            else if (mytime >= 10 && mytime < 11.5)
            {
                Accel2 += _DeltaTime;

                GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);

                TitleMountain2->SetMove(float4::Up * _DeltaTime * 20.0f);

                TitleMountain1->SetMove(float4::Down * Accel2 * 0.3f);
                Tree->SetMove(float4::Down * Accel1 * 0.3f);
            }
            else if (mytime >= 11.5)
            {
                Accel3 += _DeltaTime;

                GetLevel()->SetCameraMove(float4::Up * _DeltaTime * 40.0f);
                
                TitleMountain2->SetMove(float4::Down * Accel3 * 0.3f);
                TitleMountain1->SetMove(float4::Down * Accel2 * 0.3f);
            }
        }

        else if (GetLevel()->GetCameraPos().y <= 0)
        {
            GetLevel()->SetCameraPos({ 0,0 });
            isCameraSet = 1;
        }
    }

    if (isCameraSet == 1)
    {
        if (mytime >= 25)
        {
            NewGame->GetButtonRender()->On();
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
    Cloud1->SetAlpha(150);
    Cloud1->EffectCameraOff();

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

    GetLevel()->SetCameraPos({ 0, IntroScale.y - 768 });

    SetPos(IntroScale.half());
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
    NewGame->GetButtonRender()->Off();
    //NewGame->SetClickCallBack();
}

