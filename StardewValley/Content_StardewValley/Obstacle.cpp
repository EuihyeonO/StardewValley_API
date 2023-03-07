#include "Obstacle.h"
#include "ContentsEnum.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <time.h>

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
    Obstacle1 = CreateRender("Obstacle1.bmp", 49);
    Obstacle1->SetScaleToImage();
    Obstacle1->SetPosition({ 955, 128 });

    ObstacleCollision1 = CreateCollision(ActorType::NPC);
    ObstacleCollision1->SetScale(Obstacle1->GetScale());
    ObstacleCollision1->SetPosition(Obstacle1->GetPosition());

    Obstacle2 = CreateRender("Obstacle2.bmp", 49);
    Obstacle2->SetScaleToImage();
    Obstacle2->SetPosition({ 955, 256 });

    ObstacleCollision2 = CreateCollision(ActorType::NPC);
    ObstacleCollision2->SetScale(Obstacle2->GetScale());
    ObstacleCollision2->SetPosition(Obstacle2->GetPosition());

    Obstacle3 = CreateRender("Obstacle3.bmp", 49);
    Obstacle3->SetScaleToImage();
    Obstacle3->SetPosition({ 955, 384 });

    ObstacleCollision3 = CreateCollision(ActorType::NPC);
    ObstacleCollision3->SetScale(Obstacle3->GetScale());
    ObstacleCollision3->SetPosition(Obstacle3->GetPosition());

    noticeTextBox = CreateRender("SmallText.bmp", 500);
    noticeTextBox->SetScaleToImage();
    noticeTextBox->EffectCameraOff();
    noticeTextBox->SetPosition({ 640, 690 });
    noticeTextBox->Off();

    noticeText = CreateRender(501);
    noticeText->EffectCameraOff();
    noticeText->SetPosition({ 640, 690 });
    noticeText->SetText(" ");

    noticeTextShadow = CreateRender("SmallTextShadow.bmp", 500);
    noticeTextShadow->SetScaleToImage();
    noticeTextShadow->EffectCameraOff();
    noticeTextShadow->SetPosition({ 640, 690 });
    noticeTextShadow->SetAlpha(100);
    noticeTextShadow->Off();
}
void Obstacle::Update(float _DeltaTime)
{
    KeyInteractUpdate();

    if (true == ObstacleCollision3->Collision({ .TargetGroup = static_cast<int>(ActorType::Tool), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if (true == noticeTextBox->IsUpdate() && true == isSetText && true == GameEngineInput::IsDown("KeyInteract"))
        { 
            NoticeTextBoxOff();
        }
        else if (true == isKeyInteract)
        {
            NoticeTextBoxOn(_DeltaTime);
        }

    }
   
}

void Obstacle::Render(float _Time)
{

}

void Obstacle::NoticeTextBoxOn(float _DeltaTime)
{
    Player::GetPlayer()->SetTrueToIsColToObstacle();
    Player::GetPlayer()->PlayerStop();

    std::string Dir = Player::GetPlayer()->GetDir();
    Player::ChangePlayerIdle(Dir);

    TextScale.x += 1000.0f * 8.0f * _DeltaTime;
    TextScale.y += 150.0f * 8.0f * _DeltaTime;

    if (TextScale.x >= 1000)
    {
        TextScale.x = 1000;

        NoticeTextOn();
    }

    if (TextScale.y >= 150)
    {
        TextScale.y = 150;
    }

    noticeTextBox->On();
    noticeTextShadow->On();

    noticeTextBox->SetScale(TextScale);
    noticeTextShadow->SetScale(TextScale);

}

void Obstacle::NoticeTextBoxOff()
{
    NoticeTextOff();
    Player::GetPlayer()->SetFalseToIsColToObstacle();
    Player::GetPlayer()->PlayerStopOff();

    if (isSetText == true)
    {
        GameEngineResources::GetInst().SoundPlay("TalkBoxOff.wav");
    }

    isSetText = false;

    noticeTextBox->Off();
    noticeTextShadow->Off();

    isKeyInteract = false;
    isSetText = false;
    TextScale = { 0,0 };
}

void Obstacle::KeyInteractUpdate()
{
    if (true == GameEngineInput::IsDown("KeyInteract"))
    {
        isKeyInteract = true;
    }

    if (false == ObstacleCollision3->Collision({ .TargetGroup = static_cast<int>(ActorType::Tool), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        isKeyInteract = false;
    }
}

void Obstacle::NoticeTextOn()
{
    if (noticeTextString == "")
    {
        noticeTextString = "장애물에 가로막혀 이동할 수 없습니다.";
        PrevTime = clock();
    }

    CurTime = clock();
    CountTime += (CurTime - PrevTime) / 1000;
    CountSoundTime += CountTime;
    PrevTime = CurTime;

    noticeText->SetText(CopyText, 50, "Sandoll 미생", TextAlign::Left);
    noticeText->SetPosition({ 175, 663 });
    noticeText->EffectCameraOff();
    noticeText->SetTextBoxScale({ 1000, 150 });
    noticeText->On();

    if (CountTime >= 0.01f)
    {
        if (StringIndex != noticeTextString.size())
        {
            CopyText.push_back(noticeTextString[StringIndex]);
            StringIndex++;
        }
        CountTime = 0;
    }

    if (CountSoundTime >= 0.065f)
    {
        if (StringIndex != noticeTextString.size())
        {
            GameEngineResources::GetInst().SoundPlay("TalkBoxOn.wav");
            CountSoundTime = 0;
        }
    }

    if (StringIndex >= noticeTextString.size())
    {
        isKeyInteract = false;
        isSetText = true;
    }
}

void Obstacle::NoticeTextOff()
{
    noticeTextString.clear();
    noticeTextString = "";

    CopyText.clear();
    CopyText = " ";
    StringIndex = 0;

    noticeText->Off();
}