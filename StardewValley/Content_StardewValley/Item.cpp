#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Item.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"
#include "globalValue.h"

#include <string_view>
#include <string>

Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
}

void Item::Update(float _DeltaTime)
{
    UpdateQuantity();
    UpdatePos();
    InfoBoxOnOff();
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
}

int Item::GetSeedFloor()
{
    if (ItemName == "SeedParsnip.bmp")
    {
        return SeedName::Parsnip;
    }
    else if (ItemName == "SeedCauliflower.bmp")
    {
        return SeedName::Cauliflower;
    }
    else if (ItemName == "SeedGarlic.bmp")
    {
        return SeedName::Garlic;
    }
    else if (ItemName == "SeedBean.bmp")
    {
        return SeedName::Bean;
    }
    return -1;
}

void Item::ItemInit(std::string_view& _ItemName, int _ItemType)
{
    Itemtype = _ItemType;
    ItemName = _ItemName;
    
    //QuantityText = CreateRender(202); 

    QuantityRender.SetOwner(this);
    QuantityRender.SetImage("Number.bmp", { 13,20 }, 202, RGB(255, 255, 255), "Number.bmp");
    QuantityRender.SetValue(1);
    QuantityRender.SetAlign(Align::Right);
    QuantityRender.SetCameraEffect(true);

    SetItemRender(_ItemName);
    InitPrice();
    ItemCollision = CreateCollision(ActorType::Item);
    ItemCollision->SetScale(RenderImage->GetScale());

    RenderImage->SetScaleToImage();
}

void Item::SetItemRender(std::string_view& _ItemName)
{

    std::string ItemName = _ItemName.data();

    std::string InfoItemName = "Info" + ItemName;


    RenderImage = CreateRender(_ItemName, 201);
    InfoRenderImage = CreateRender(InfoItemName, 250);
    RenderImage->SetScaleToImage();
    InfoRenderImage->SetScaleToImage();
    InfoRenderImage->SetPosition(RenderImage->GetScale().half());
    InfoRenderImage->Off();
}

void Item::UpdatePos()
{
    float4 RenderPos = RenderImage->GetPosition();

    ItemCollision->SetPosition(RenderPos - float4{22.5f, 22.5f});
    InfoRenderImage->SetPosition(RenderImage->GetPosition() + InfoRenderImage->GetScale().half());
}

void Item::InfoBoxOnOff()
{
    if (true == ItemCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Mouse) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if(globalValue::isUpdate_CurLevelInventory(GetLevel()->GetName()) == true)
        {
            InfoRenderImage->On();
        }
    }
    else
    {
        InfoRenderImage->Off();
    }
}

bool Item::isCollisionToMouse()
{
    return ItemCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Mouse) , .TargetColType = CT_Rect, .ThisColType = CT_Rect });
}

void Item::InitPrice()
{
    if (ItemName == "IconBean.BMP")
    {
        Price = 120;
    }
    else if (ItemName == "IconCauliflower.BMP")
    {
        Price = 175;
    }
    else if (ItemName == "IconParsnip.BMP")
    {
        Price = 35;
    }
    else if (ItemName == "IconGarlic.BMP")
    {
        Price = 60;
    }
    else
    {
        Price = 0;
    }
}

bool Item::isAbleToSell()
{
    if (Itemtype == static_cast<int>(ItemType::Crops))
    {
        return true;
    }
    else
    {
        return false;
    }
}