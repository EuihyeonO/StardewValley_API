#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineString.h>

#include "Item.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"
#include "globalValue.h"
#include "SellBox.h"
#include "globalInterface.h"

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
    RenderHarvesting();
}

void Item::Render(float _Time)
{
}


void Item::UpdateQuantity()
{
    if (Itemtype == static_cast<int>(ItemType::Axe) ||
        Itemtype == static_cast<int>(ItemType::Watering) ||
        Itemtype == static_cast<int>(ItemType::Hoe) ||
        Itemtype == static_cast<int>(ItemType::Pick) ||
        Itemtype == static_cast<int>(ItemType::Hammer))
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

    if (false == SellBox::IsBOxOn() && Itemtype == static_cast<int>(ItemType::Crops))
    {
        isHarvested = true;
    }

    if (true == SellBox::IsBOxOn())
    {
        isHarvested = false;
    }

    if (true == GameEngineInput::IsKey("MakeItem") && true == GameEngineInput::IsDown("MakeItem"))
    {
        isHarvested = false;
    }


    QuantityRender.SetOwner(this);
    QuantityRender.SetImage("Number.bmp", { 13,20 }, 202, RGB(255, 255, 255), "Number.bmp");
    QuantityRender.SetValue(1);
    QuantityRender.SetAlign(Align::Right);
    QuantityRender.SetCameraEffect(false);

    SetItemRender(_ItemName);

    InitPrice();
    ItemCollision = CreateCollision(ActorType::Item);
    ItemCollision->SetScale(RenderImage->GetScale());

    RenderImage->SetScaleToImage();
    RenderImage->EffectCameraOff();
}

void Item::SetItemRender(std::string_view& _ItemName)
{

    std::string ItemName = _ItemName.data();

    std::string InfoItemName = "Info" + ItemName;
    std::string CopyItemName = "H" + ItemName;


    RenderImage = CreateRender(_ItemName, 201);
    RenderImage->SetScaleToImage();
    InfoRenderImage = CreateRender(InfoItemName, 250);

    if (isHarvested == true)
    {
        Player::GetPlayer()->SetIsHarvesting();

        CopyImage = CreateRender(CopyItemName, 201);

        std::vector<int> DHarvesting(5);
        DHarvesting = { 0, 1, 2, 3, 3 };
        std::vector<float> DHarvestingFrame(5);
        DHarvestingFrame = { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };

        CopyImage->CreateAnimation({ .AnimationName = "Harvested", .ImageName = CopyItemName,.FrameIndex = DHarvesting,.FrameTime = DHarvestingFrame });
        CopyImage->CreateAnimation({ .AnimationName = "None", .ImageName = CopyItemName,.FrameIndex = {0},.FrameTime = {0} });

        CopyImage->SetScale({ 64,200 });
        CopyImage->Off();
    }

    InfoRenderImage->SetScaleToImage();
    InfoRenderImage->SetPosition(RenderImage->GetPosition());
    InfoRenderImage->Off();
    InfoRenderImage->EffectCameraOff();
}

void Item::UpdatePos()
{
    float4 RenderPos = RenderImage->GetPosition();
    float4 CameraPos = GetLevel()->GetCameraPos();

    ItemCollision->SetPosition(CameraPos + RenderPos);
    InfoRenderImage->SetPosition(RenderPos + InfoRenderImage->GetScale().half());
   
    float4 pos = ItemCollision->GetPosition();
}

void Item::InfoBoxOnOff()
{
    if (true == ItemCollision->Collision({ .TargetGroup = static_cast<int>(ActorType::Mouse) , .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
    {
        if(globalInterface::isUpdate_CurLevelInventory() == true)
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
    std::string UpperName = GameEngineString::ToUpper(ItemName);

    if (UpperName == "ICONBEAN.BMP")
    {
        Price = 120;
    }
    else if (UpperName == "ICONCAULIFLOWER.BMP")
    {
        Price = 175;
    }
    else if (UpperName == "ICONPARSNIP.BMP")
    {
        Price = 35;
    }
    else if (UpperName == "ICONGARLIC.BMP")
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
    if (Quantity>=1 && Itemtype == static_cast<int>(ItemType::Crops))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Item::GetSeedPrice(std::string& _ItemName)
{
    std::string Name = GameEngineString::ToUpper(_ItemName);

    if (Name == "SEEDBEAN.BMP")
    {
        return 60;
    }

    else if (Name == "SEEDCAULIFLOWER.BMP")
    {
        return 80;
    }

    else if (Name == "SEEDPARSNIP.BMP")
    {
        return 20;
    }

    else if (Name == "SEEDGARLIC.BMP")
    {
        return 40;
    }
    else
    {
        return 0;
    }
}

void Item::RenderHarvesting()
{
    if (CopyImage == nullptr)
    {
        return;
    }

    if (GetLevel()->GetName() != "Farm")
    {
        isHarvested = false;
        return;
    }

    if (true == SellBox::GetSellBoxInventory()->IsUpdate())
    {
        isHarvested = false;
        CopyImage->ChangeAnimation("None");
        CopyImage->Off();
    }

    if (isHarvested == true)
    {
        std::string PlayerDir = Player::GetPlayer()->GetDir();
        float4 PlayerPos = Player::GetPlayer()->GetPos();

        if (PlayerDir == "D") 
        {
            CopyImage->SetPosition(PlayerPos);
        }
        else if (PlayerDir == "L")
        {
            CopyImage->SetPosition(PlayerPos + float4(-32, 0));
        }
        else if (PlayerDir == "R")
        {
            CopyImage->SetPosition(PlayerPos + float4(32, 0));
        }
        if (PlayerDir == "U")
        {
            CopyImage->SetPosition(PlayerPos);
            CopyImage->SetOrder(49);
        }

        CopyImage->On();
        CopyImage->ChangeAnimation("Harvested");

        if (CopyImage->IsAnimationEnd() == true)
        {
            CopyImage->ChangeAnimation("None");
            CopyImage->Off();
            isHarvested = false;
            globalInterface::AllInventoryUpdate();
        }
    }
    else
    {
        CopyImage->ChangeAnimation("None");
        CopyImage->Off();
    }
}