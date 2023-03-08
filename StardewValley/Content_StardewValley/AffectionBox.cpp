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
}

void AffectionBox::Update(float _DeltaTime)
{
    HeartIndexUpdate();
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
}

void AffectionBox::AffectionBoxOff()
{
    AffectionBoxRender->Off();
    HaleyHeart->Off();
    SamHeart->Off();
    PennyHeart->Off();
    LewisHeart->Off();
}

void AffectionBox::AffectionUp(std::string& _Name)
{
    std::string NpcName = GameEngineString::ToUpper(_Name);

    if ("HALEY" == NpcName && HaleyAffection<9)
    {
        ++HaleyAffection;
    }
    else if ("SAM" == NpcName && SamAffection<9)
    {
        ++SamAffection;
    }
    else if ("PENNY" == NpcName && PennyAffection<9)
    {
        ++PennyAffection;
    }
    else if ("LEWIS" == NpcName && LewisAffection<9)
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