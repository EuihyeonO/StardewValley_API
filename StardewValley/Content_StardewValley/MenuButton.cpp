#include "MenuButton.h"
#include "ContentsEnum.h"
#include "AffectionBox.h"
#include "globalInterface.h"

#include <GameEngineCore/Button.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

MenuButton* MenuButton::GlobalMenuButton = nullptr;

MenuButton::MenuButton()
{
    GlobalMenuButton = this;
}

MenuButton::~MenuButton()
{
}

void MenuChangeToAffection(Button* _btn)
{
    MenuButton::GetGlobalMenuButton()->SetAffectionButtonToSelectedPos();
    Inventory::GetInventory()->InventoryOff();
    AffectionBox::GetGlobalAffectionBox()->AffectionBoxOn();

    GameEngineResources::GetInst().SoundPlay("MenuChange.wav");
}

void MenuChangeToInventory(Button* _btn)
{
    MenuButton::GetGlobalMenuButton()->SetInventoryButtonToSelectedPos();
    AffectionBox::GetGlobalAffectionBox()->AffectionBoxOff();
    Inventory::GetInventory()->InventoryOn();

    GameEngineResources::GetInst().SoundPlay("MenuChange.wav");
}

void MenuButton::Start()
{
    InventoryButton = GetLevel()->CreateActor<Button>();

    InventoryButton->SetReleaseImage("InventoryButton.bmp");
    InventoryButton->SetHoverImage("InventoryButton.bmp");
    InventoryButton->SetPressImage("InventoryButton.bmp");
    InventoryButton->SetScale({ 64, 68 }); 
    InventoryButton->SetRenderOrder(150);
    InventoryButton->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    InventoryButton->SetClickCallBack(MenuChangeToInventory);
    InventoryButton->Off();

    AffectionButton = GetLevel()->CreateActor<Button>();

    AffectionButton->SetReleaseImage("AffectionButton.bmp");
    AffectionButton->SetHoverImage("AffectionButton.bmp");
    AffectionButton->SetPressImage("AffectionButton.bmp");
    AffectionButton->SetScale({ 64, 68 });
    AffectionButton->SetRenderOrder(100);
    AffectionButton->SetTargetCollisionGroup(static_cast<int>(ActorType::Mouse));
    AffectionButton->SetClickCallBack(MenuChangeToAffection);
    AffectionButton->Off();
}

void MenuButton::Update(float _DeltaTime)
{
}

void MenuButton::Render(float _Time)
{

}

void MenuButton::MenuButtonOn()
{
    InventoryButton->On();
    AffectionButton->On();

    InventoryButton->SetPos(GetLevel()->GetCameraPos()+ float4{ 316, 62 });
    AffectionButton->SetPos(GetLevel()->GetCameraPos()+ float4{ 380, 55 });
}

void MenuButton::MenuButtonOff()
{
    InventoryButton->Off();
    AffectionButton->Off();
}

void MenuButton::MenuButtonOnOff()
{
    if (InventoryButton->IsUpdate() == true)
    {
        MenuButtonOff();
    }
    else if (InventoryButton->IsUpdate() == false)
    {
        MenuButtonOn();
    }
}

void MenuButton::SetInventoryButtonToSelectedPos()
{
    InventoryButton->SetPos(GetLevel()->GetCameraPos() + float4{ 316, 62 });
    AffectionButton->SetPos(GetLevel()->GetCameraPos() + float4{ 380, 55 });
    InventoryButton->SetRenderOrder(153);
    AffectionButton->SetRenderOrder(100);
}

void MenuButton::SetAffectionButtonToSelectedPos()
{
    InventoryButton->SetPos(GetLevel()->GetCameraPos() + float4{ 316, 55 });
    AffectionButton->SetPos(GetLevel()->GetCameraPos() + float4{ 380, 62 });
    InventoryButton->SetRenderOrder(100);
    AffectionButton->SetRenderOrder(153);
}