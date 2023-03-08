#include "AffectionBox.h"
#include "globalInterface.h"

#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineString.h>

AffectionBox* AffectionBox::globalAffectionBox = nullptr;

AffectionBox::AffectionBox()
{
    globalInterface::AddAffectionToList(this);
}

AffectionBox::~AffectionBox()
{
}

void AffectionBox::Start()
{
    AffectionBoxRender = CreateRender("AffectionBox.bmp", 150);
    AffectionBoxRender->SetScaleToImage();
    AffectionBoxRender->SetPosition({ 640, 384 });
    AffectionBoxRender->EffectCameraOff();
    AffectionBoxRender->Off();

    HaleyHeart = CreateRender("Heart.bmp", 151);
    HaleyHeart->SetScale({316, 28});
    HaleyHeart->SetPosition({ 680, 170 });
    HaleyHeart->EffectCameraOff();
    HaleyHeart->Off();

    SamHeart = CreateRender("Heart.bmp", 151);
    SamHeart->SetScale({ 316, 28 });
    SamHeart->SetPosition({ 680, 315 });
    SamHeart->EffectCameraOff();
    SamHeart->Off();

    PennyHeart = CreateRender("Heart.bmp", 151);
    PennyHeart->SetScale({ 316, 28 });
    PennyHeart->SetPosition({ 680, 460 });
    PennyHeart->EffectCameraOff();
    PennyHeart->Off();

    LewisHeart = CreateRender("Heart.bmp", 151);
    LewisHeart->SetScale({ 316, 28 });
    LewisHeart->SetPosition({ 680, 605 });
    LewisHeart->EffectCameraOff();
    LewisHeart->Off();

    HaleyGiftCountRender = CreateRender("GiftCount.bmp", 151);
    HaleyGiftCountRender->SetScale({ 61, 30 });
    HaleyGiftCountRender->EffectCameraOff();
    HaleyGiftCountRender->SetFrame(0);
    HaleyGiftCountRender->SetPosition({ 953, 186 });
    HaleyGiftCountRender->Off();
    
    SamGiftCountRender = CreateRender("GiftCount.bmp", 151);
    SamGiftCountRender->SetScale({ 61, 30 });
    SamGiftCountRender->EffectCameraOff();
    SamGiftCountRender->SetFrame(0);
    SamGiftCountRender->SetPosition({ 953, 330 });
    SamGiftCountRender->Off();


    PennyGiftCountRender = CreateRender("GiftCount.bmp", 151);
    PennyGiftCountRender->SetScale({ 61, 30 });
    PennyGiftCountRender->EffectCameraOff();
    PennyGiftCountRender->SetFrame(0);
    PennyGiftCountRender->SetPosition({ 953, 475 });
    PennyGiftCountRender->Off();

    LewisGiftCountRender = CreateRender("GiftCount.bmp", 151);
    LewisGiftCountRender->SetScale({ 61, 30 });
    LewisGiftCountRender->EffectCameraOff();
    LewisGiftCountRender->SetFrame(0);
    LewisGiftCountRender->SetPosition({ 953, 620 });
    LewisGiftCountRender->Off();
}

void AffectionBox::Update(float _DeltaTime)
{
    HeartIndexUpdate();
    GiftCountIndexUpdate();
}

void AffectionBox::Render(float _Time)
{

}

void AffectionBox::AffectionBoxOn()
{
    AffectionBoxRender->On();

    HaleyHeart->On();
    SamHeart->On();
    PennyHeart->On();
    LewisHeart->On();


    HaleyGiftCountRender->On();
    SamGiftCountRender->On();
    PennyGiftCountRender->On();
    LewisGiftCountRender->On();
}

void AffectionBox::AffectionBoxOff()
{
    AffectionBoxRender->Off();

    HaleyHeart->Off();
    SamHeart->Off();
    PennyHeart->Off();
    LewisHeart->Off();

    HaleyGiftCountRender->Off();
    SamGiftCountRender->Off();
    PennyGiftCountRender->Off();
    LewisGiftCountRender->Off();
}

void AffectionBox::AffectionUp(std::string& _Name)
{
    std::string NpcName = GameEngineString::ToUpper(_Name);

    if ("HALEY" == NpcName && HaleyAffection< 10)
    {
        ++HaleyAffection;
    }
    else if ("SAM" == NpcName && SamAffection< 10)
    {
        ++SamAffection;
    }
    else if ("PENNY" == NpcName && PennyAffection< 10)
    {
        ++PennyAffection;
    }
    else if ("LEWIS" == NpcName && LewisAffection< 10)
    {
        ++LewisAffection;
    }
}

void AffectionBox::AffectionDown(std::string& _Name)
{
    std::string NpcName = GameEngineString::ToUpper(_Name);

    if ("HALEY" == NpcName && HaleyAffection > 0)
    {
        --HaleyAffection;
    }
    else if ("SAM" == NpcName && SamAffection > 0)
    {
        --SamAffection;
    }
    else if ("PENNY" == NpcName && PennyAffection > 0)
    {
        --PennyAffection;
    }
    else if ("LEWIS" == NpcName && LewisAffection > 0)
    {
        --LewisAffection;
    }
}

void AffectionBox::HeartIndexUpdate()
{
    HaleyHeart->SetFrame(HaleyAffection);
    SamHeart->SetFrame(SamAffection);
    PennyHeart->SetFrame(PennyAffection);
    LewisHeart->SetFrame(LewisAffection);
}

void AffectionBox::GiftCountUp(std::string& _Name)
{
    std::string NpcName = GameEngineString::ToUpper(_Name);

    if ("HALEY" == NpcName && HaleyGiftCount < 2)
    {
        ++HaleyGiftCount;
    }
    else if ("SAM" == NpcName && SamGiftCount < 2)
    {
        ++SamGiftCount;
    }
    else if ("PENNY" == NpcName && PennyGiftCount < 2)
    {
        ++PennyGiftCount;
    }
    else if ("LEWIS" == NpcName && LewisGiftCount < 2)
    {
        ++LewisGiftCount;
    }
}
void AffectionBox::GiftCountClear()
{
    HaleyGiftCount = 0;
    SamGiftCount = 0;
    PennyGiftCount = 0;
    LewisGiftCount = 0;
}

void AffectionBox::GiftCountIndexUpdate()
{
    HaleyGiftCountRender->SetFrame(HaleyGiftCount);
    SamGiftCountRender->SetFrame(SamGiftCount);
    PennyGiftCountRender->SetFrame(PennyGiftCount);
    LewisGiftCountRender->SetFrame(LewisGiftCount);
}

int AffectionBox::GetGiftCount(std::string _NpcName)
{
    std::string Name = GameEngineString::ToUpper(_NpcName);


    if ("HALEY" == Name)
    {
        return HaleyGiftCount;
    }
    else if ("SAM" == Name)
    {
        return SamGiftCount;
    }
    else if ("PENNY" == Name)
    {
        return PennyGiftCount;
    }
    else if ("LEWIS" == Name)
    {
        return LewisGiftCount;
    }

    return -1;
}