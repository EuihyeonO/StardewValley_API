#include <GameEnginePlatform/GameEngineWindow.h>

#include "Item.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"
#include "globalValue.h"

#include <string_view>

Item::Item()
{
}

Item::~Item()
{
}

void Item::ItemInit(std::string_view& _ItemName, int _ItemType)
{
    Itemtype = _ItemType;
    ItemName = _ItemName;

    //QuantityText = CreateRender(202); 

    QuantityRender.SetOwner(this);
    QuantityRender.SetImage("Number.bmp", { 20,20 }, 202, RGB(255, 255, 255), "Number.bmp");
    QuantityRender.SetValue(1);
    QuantityRender.SetAlign(Align::Right);
    QuantityRender.SetCameraEffect(true);

    SetItemRender(_ItemName);

    if (Itemtype == static_cast<int>(ItemType::Crops))
    {
        RenderImage->SetPosition(Player::GetPlayer()->GetPos()+ float4{0, -50});
        RenderImage->Off();

        SetItemisHarvesting();

        return;
    }

    RenderImage->SetScaleToImage();
}

void Item::SetItemRender(std::string_view& _ItemName)
{
    RenderImage = CreateRender(_ItemName, 201);
    RenderImage->SetScaleToImage();
}


void Item::Start()
{
}

void Item::Update(float _DeltaTime)
{
    if (Player::GetPlayer()->GetPlayerAnimationFrame() == 56 || 
        Player::GetPlayer()->GetPlayerAnimationFrame() == 60 || 
        Player::GetPlayer()->GetPlayerAnimationFrame() == 64 || 
        Player::GetPlayer()->GetPlayerAnimationFrame() == 65)
    {
        if (CopyImage != nullptr)
        {
            if (Player::GetPlayer()->GetDir() == "U")
            {
                CopyImage->SetOrder(1);
            }

            CopyImage->On();         
        }

        if (Player::GetPlayer()->GetDir() == "U")
        {
            RenderImage->SetOrder(1);
        }
        RenderImage->On();
    }

    if (Player::GetPlayer()->isPlayerAnimationEnd() == true)
    {
        if (CopyImage != nullptr)
        {
            CopyImage->Off();
            CopyImage = nullptr;          
        }

        isHarvesting = false;

        RenderImage->SetScaleToImage();
        RenderImage->SetOrder(150);       
    }

    UpdateQuantity();
}

void Item::Render(float _Time)
{
}

void Item::SetItemisHarvesting()
{
    isHarvesting = true;
    
    if (Quantity > 1)
    {
        CopyImage = CreateRender(ItemName, 2);
        CopyImage->SetScale({ 64, 64 });
        CopyImage->SetPosition(Player::GetPlayer()->GetPos() + float4{ 0, -50 });
        CopyImage->Off();
    }

    else
    {
        RenderImage->SetPosition(Player::GetPlayer()->GetPos() + float4{ 0, -50 });
        RenderImage->SetScale({ 64, 64 });
    }
}

void Item::UpdateQuantity()
{
    if (Itemtype == static_cast<int>(ItemType::Axe) ||
        Itemtype == static_cast<int>(ItemType::Watering) ||
        Itemtype == static_cast<int>(ItemType::Hoe) ||
        Itemtype == static_cast<int>(ItemType::Pick))
    {
        QuantityRender.Off();
    }
    QuantityRender.SetValue(Quantity);
    QuantityRender.SetRenderPos(RenderImage->GetPosition() + float4(23, 23));
   // QuantityText->SetText(std::to_string(Quantity), 25, "Sandoll ¹Ì»ý");
    //QuantityText->SetPosition(RenderImage->GetPosition() + float4(20,10));
}

int Item::GetSeedFloor()
{
    if (ItemName == "SeedParsnip.bmp")
    {
        return SeedName::Parsnip;
    }
    else
    {
        return -1;
    }
}