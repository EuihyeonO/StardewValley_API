#include "NpcCommonData.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"
#include "globalInterface.h"
#include "AffectionBox.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineInput.h>


#include <time.h>


NpcCommonData::NpcCommonData()
{
}

NpcCommonData::~NpcCommonData()
{
}

void NpcCommonData::SetBodyRender(const std::string_view& _ImageName, float4 _pos)
{
    BodyRender = CreateRender(_ImageName, 50);
    BodyRender->SetScaleToImage();
    BodyRender->SetPosition(_pos);
}

void NpcCommonData::SetCollision()
{
    float4 Scale = BodyRender->GetScale();

    BodyCollision = CreateCollision(ActorType::NPC);
    BodyCollision->SetScale({ Scale.x, Scale.y *(0.5f)});
    BodyCollision->SetPosition(BodyRender->GetPosition() + float4{ 0, Scale.y * (0.25f)});

    OrderCollision = CreateCollision(ActorType::OrderChange);
    OrderCollision->SetScale(BodyRender->GetScale());
    OrderCollision->SetPosition(BodyRender->GetPosition());
}

void NpcCommonData::RenderOrderUpdate()
{
    if (true == OrderCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::FullPlayer), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        int YDistance = BodyRender->GetPosition().y - Player::GetPlayer()->GetPos().y;
   
        if (YDistance >= 0)
        {
            BodyRender->SetOrder(60);
        }
        else
        {
            BodyRender->SetOrder(40);
        }
    }
}

void NpcCommonData::SetTextRender(float4 _pos)
{

    TextBox_Common = CreateRender(NpcName + "TextBox_Common.bmp", 250);
    TextBox_Common->Off();
    TextBox_Common->EffectCameraOff();
    TextBox_Common->SetPosition({ 640, 568 });
    TextBox_Common->SetScaleToImage();

    TextBox_Happy = CreateRender(NpcName + "TextBox_Happy.bmp", 250);
    TextBox_Happy->Off();
    TextBox_Happy->EffectCameraOff();
    TextBox_Happy->SetPosition({ 640, 568 });
    TextBox_Happy->SetScaleToImage();


    TextBox_Angry = CreateRender(NpcName + "TextBox_Angry.bmp", 250);
    TextBox_Angry->Off();
    TextBox_Angry->EffectCameraOff();
    TextBox_Angry->SetPosition(_pos);
    TextBox_Angry->SetScaleToImage();

    TextBoxShadow = CreateRender("TextBoxShodow.bmp", 250);
    TextBoxShadow->Off();
    TextBoxShadow->EffectCameraOff();
    TextBoxShadow->SetPosition(_pos);
    TextBoxShadow->SetScaleToImage();
    TextBoxShadow->SetAlpha(100);

    NoticeTextBox = CreateRender("SmallText.bmp", 500);
    NoticeTextBox->SetScaleToImage();
    NoticeTextBox->EffectCameraOff();
    NoticeTextBox->SetPosition({ 640, 690 });
    NoticeTextBox->Off();

    Text = CreateRender(251);
    Text->SetText(" ");
    CopyText = " ";
}

void NpcCommonData::InteractUpdate()
{
    if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::PlayerInteract), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if (GameEngineInput::IsDown("KeyInteract"))
        {
            isKeyInteract = true;
        }
    }

    else
    {
        isKeyInteract = false;
    }
}

void NpcCommonData::TextBoxOnOff(float _DeltaTime, const std::string& CommonText, const std::string& HappyText, const std::string& AngryText)
{
    if (true == IsTextUpdate() && true == isSetText && true == GameEngineInput::IsDown("KeyInteract"))
    {
        TextBoxOff();
    }
    else if (true == isKeyInteract)
    {
        TextBoxOn(_DeltaTime, CommonText, HappyText, AngryText);
    }
}

bool NpcCommonData::IsTextUpdate()
{
    //텍스트 창이 셋중 하나라도 켜있다면 업데이트 중이다.
    return (TextBox_Angry->IsUpdate() || TextBox_Common->IsUpdate() || TextBox_Happy->IsUpdate());
}

void NpcCommonData::TextBoxOn(float _DeltaTime, const std::string& CommonText, const std::string& HappyText, const std::string& AngryText)
{

    Player::GetPlayer()->PlayerStop();
    std::string Dir = Player::GetPlayer()->GetDir();
    Player::ChangePlayerIdle(Dir);

    Scale.x += 1280.0f * 8.0f * _DeltaTime;
    Scale.y += 400.0f * 8.0f * _DeltaTime;

    std::string UpperItemName = GameEngineString::ToUpper(Inventory::GetInventory()->GetSelectedItem()->GetItemName());

    if (isInputText == false &&  2 > AffectionBox::GetGlobalAffectionBox()->GetGiftCount(NpcName))
    {
        if ("ICONPARSNIP.BMP" == UpperItemName) //조건에 따라 텍스트창 다르게 출력
        {   
            CopyOutPutTextBox = TextBox_Happy;
            CopyOutPutText = HappyText;
            globalInterface::AllAffectionUp(NpcName);
            globalInterface::AllGiftCountUp(NpcName);
            globalInterface::AllInventoryDelete();
            
        }
        else if ("ICONBRANCH.BMP" == UpperItemName)
        {
            CopyOutPutTextBox = TextBox_Angry;
            CopyOutPutText = AngryText;
            globalInterface::AllAffectionDown(NpcName);
            globalInterface::AllGiftCountUp(NpcName);
            globalInterface::AllInventoryDelete();
        }
        else
        {
            CopyOutPutTextBox = TextBox_Common;
            CopyOutPutText = CommonText;
        }

        isInputText = true;
    }

    else if (isInputText == false && 2 == AffectionBox::GetGlobalAffectionBox()->GetGiftCount(NpcName))
    {
        if ("ICONPARSNIP.BMP" == UpperItemName || "ICONBRANCH.BMP" == UpperItemName)
        {
            CopyOutPutTextBox = NoticeTextBox;
            CopyOutPutText = "오늘 선물을 줄 기회를 모두 소진하였습니다.";

        }
        else
        {
            CopyOutPutTextBox = TextBox_Common;
            CopyOutPutText = CommonText;
        }

        isInputText = true;
    }

    if (CopyOutPutTextBox != NoticeTextBox)
    {
        if (Scale.x >= 1280)
        {
            Scale.x = 1280;

            TextOn(CopyOutPutText);
        }

        if (Scale.y >= 400)
        {
            Scale.y = 400;
        }
    }
    else if (CopyOutPutTextBox == NoticeTextBox)
    {
        if (Scale.x >= 1000)
        {
            Scale.x = 1000;

            TextOn(CopyOutPutText);
        }

        if (Scale.y >= 150)
        {
            Scale.y = 150;
        }
    }


    {
        CopyOutPutTextBox->On();
        TextBoxShadow->On();

        CopyOutPutTextBox->SetScale(Scale);
        TextBoxShadow->SetScale(Scale);
    }
}

void NpcCommonData::TextBoxOff()
{
    TextOff();

    Player::GetPlayer()->PlayerStopOff();

    if (isSetText == true)
    {
        GameEngineResources::GetInst().SoundPlay("TalkBoxOff.wav");
    }

    TextBox_Angry->Off();
    TextBox_Common->Off();
    TextBox_Happy->Off();
    TextBoxShadow->Off();

    isSetText = false;
    isKeyInteract = false;

    Scale = { 0,0 };
}

void NpcCommonData::TextOn(const std::string& _Text)
{
    if (Talk == "")
    {
        Talk = _Text;
        Prevtime = clock();
    }


    Curtime = clock();
    Counttime += (Curtime - Prevtime) / 1000;
    CountSoundtime += Counttime;
    Prevtime = Curtime;

    Text->SetText(CopyText, 50, "Sandoll 미생", TextAlign::Left);
    Text->SetPosition({ 35,420 });
    Text->EffectCameraOff();
    Text->SetTextBoxScale({ 1280, 500 });
    Text->On();

    if (Counttime >= 0.01f)
    {
        if (StringIndex != Talk.size())
        {
            CopyText.push_back(Talk[StringIndex]);
            StringIndex++;
        }
        Counttime = 0;
    }

    if (CountSoundtime >= 0.065f)
    {
        if (StringIndex != Talk.size())
        {
            GameEngineResources::GetInst().SoundPlay("TalkBoxOn.wav");
            CountSoundtime = 0;
        }
    }

    if (StringIndex >= Talk.size())
    {
        isKeyInteract = false;
        isSetText = true;
    }
}

void NpcCommonData::TextOff()
{
    Talk.clear();
    Talk = "";

    CopyText.clear();
    CopyText = " ";
    StringIndex = 0;

    Text->Off();

    isInputText = false;
    CopyOutPutText.clear();
    CopyOutPutTextBox = nullptr;
}