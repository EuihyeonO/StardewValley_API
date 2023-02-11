#include <GameEnginePlatform/GameEngineWindow.h>

#include "Item.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Inventory.h"

#include <string_view>

Item::Item()
{
}

Item::~Item()
{
}

void Item::ItemInit(std::string_view& _ItemName)
{
    ItemOrder = Inventory::GetInventory()->GetNumOfItem();
    ItemName = _ItemName;

    SetItemRender(_ItemName);
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
}

void Item::Render(float _Time)
{
}
