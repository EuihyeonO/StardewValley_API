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
    ItemOrder = Inventory::GetInventory()->GetNumOfItem();
    ItemName = _ItemName;
    
    SetItemRender(_ItemName);

    if (Itemtype == static_cast<int>(ItemType::Crops))
    {
        RenderImage->SetPosition(Player::GetPlayer()->GetPos()+ float4{0, -50});
        RenderImage->Off();

        SetItemisHarvesting();

        return;
    }

    RenderImage->SetScale({ 45, 45 });
}

void Item::SetItemRender(std::string_view& _ItemName)
{
    RenderImage = CreateRender(_ItemName, 2);
    RenderImage->SetScale({ 45, 45 });
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

        RenderImage->SetScale({ 45, 45 });
        RenderImage->SetOrder(2);       
    }
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