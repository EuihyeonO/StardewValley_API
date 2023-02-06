#include "Title.h"
#include "Player.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

#include <iostream>


Title::Title()
{
}

Title::~Title()
{
}

void Title::Start()
{
    SetPos({640, 750});

    intro1 = CreateRender("intro1.bmp", 0);
    intro1->SetScaleToImage();
    intro1->SetPosition({ 0,0 });

    //타이틀 화면 게임이름 창
    TitleName = CreateRender("TitleName.bmp", 2);
    TitleName->SetScaleToImage();
    TitleName->SetPosition({ 0, -530 });

    //타이틀 화면 하단 산맥
    TitleMountain2 = CreateRender("TitleMountain2.bmp", 2);
    TitleMountain1 = CreateRender("TitleMountain1.bmp", 2);
    Tree = CreateRender("TitleTree.bmp", 2);
}

void Title::Update(float _DeltaTime)
{

    mytime += _DeltaTime;

    //타이틀화면 배경

    TitleMountain2->SetScaleToImage();
    TitleMountain1->SetScaleToImage();
    Tree->SetScaleToImage();

    //산맥 위치 및 속도 설정
    TitleMountain2->SetPosition(Mountain2Pos);
    TitleMountain1->SetPosition(Mountain1Pos);
    Tree->SetPosition(TreePos);

    if (isSet == 0)
    {
        GetLevel()->SetCameraPos({ 0, 750 }); 
        isSet = 1;
    }

    if (GetLevel()->GetCameraPos().y > 0)
    {       
        if (mytime >= 1) 
        {

            Mountain2Pos += float4::Up * 20.0f * _DeltaTime;
            Mountain1Pos += float4::Down * 30.0f * _DeltaTime;
            TreePos += float4::Down * 10.0f * _DeltaTime;

            GetLevel()->SetCameraMove(float4::Up * 80.0f * _DeltaTime); //float4::Up * 70.0f * _DeltaTime
        }
    }
    else
    {
        GetLevel()->SetCameraPos(float4::Zero);
        isCameraSet = 1;
    }
    
    //타이틀 화면 구름
    {
       /* GameEngineRender* Render1 = CreateRender("cloud1.bmp", 1);
        Render1->SetScale({ 300, 133 });
        Render1->SetPosition({ 500, -250 });

        GameEngineRender* Render2 = CreateRender("cloud2.bmp", 1);
        Render2->SetScale({ 250, 112 });
        Render2->SetPosition({ 300, 160 });


        GameEngineRender* Render3 = CreateRender("cloud3.bmp", 1);
        Render3->SetScale({ 128, 72 });
        Render3->SetPosition({ -500, -200 });*/
    }

    //타이틀 화면 버튼 (시작하기, 불러오기 등)
    {   
        if (isCameraSet == 1)
        {
            //mytime += _DeltaTime;
            if(mytime >= 11)
            {
                GameEngineRender* Render1 = CreateRender("newgamebutton.bmp", 2);
                Render1->SetPosition({ -252, -150 }); //250
                Render1->SetScale({ 148,116 });

                if (mytime >= 11.25)
                {
                    Render1->SetScaleToImage();
                }
            }

            if (mytime >= 11.5)
            {
                GameEngineRender* Render2 = CreateRender("loadbutton.bmp", 2);
                Render2->SetPosition({ 0, -150 });
                Render2->SetScale({ 148,116 });

                if (mytime >= 11.75)
                {
                    Render2->SetScaleToImage();
                } 
            }

            if (mytime >= 12)
            {
                GameEngineRender* Render3 = CreateRender("ExitButton.bmp", 2);
                Render3->SetPosition({ 252, -150 });
                Render3->SetScale({ 148,116 });

                if (mytime >= 12.25)
                {
                    Render3->SetScaleToImage();
                }
            }
        }       
    }


    if (false == GameEngineInput::IsKey("LevelChange"))
    {
        GameEngineInput::CreateKey("LevelChange", 'P');
    }

    if (true == GameEngineInput::IsDown("LevelChange"))
    {
        GameEngineCore::GetInst()->ChangeLevel("Farm");
    }

}

void Title::Render(float _Time)
{


}