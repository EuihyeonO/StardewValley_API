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
}

void Item::SetItemRender(GameEngineRender* _Render)
{
    RenderImage = _Render;

    RenderImage->SetScale({ 45, 45 });
    RenderImage->Off();

}