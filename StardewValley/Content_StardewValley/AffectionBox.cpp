#include "AffectionBox.h"
#include "globalInterface.h"
#include <GameEngineCore/GameEngineRender.h>

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
