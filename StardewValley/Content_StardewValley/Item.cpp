#include <GameEnginePlatform/GameEngineWindow.h>

#include "Item.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"

Item::Item()
{
}

Item::Item(std::string_view& _ItemName)
{
    ItemInit(_ItemName);
}

Item::~Item()
{
}

void Item::ItemInit(std::string_view& _ItemName)
{
    ItemOrder = Inventory::GetInventory()->GetNumOfItem();

    ItemName = _ItemName;
}



void Item::SetItemPos()
{
    //아이템의 개수에 따라 위치가 변해야 함

    //if(ItemOrder <=10)
    /*{
        RenderImage->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder-1) * 64, 148.0f});
    }
    else if(ItemOrder <= 20)
    {
        RenderImage->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder - 11) * 64, 148.0f + 64 });
    }
    else if(ItemOrder <= 30)
    {
        RenderImage->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder - 21) * 64, 148.0f + 128 });
    }*/
}

void Item::SetItemRender(GameEngineRender* _Render)
{
    RenderImage = _Render;
    RenderImage->SetScale({ 45, 45 });
    RenderImage->Off();

    SetItemPos();
}