#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Inventory.h"
#include "Player.h"
#include "UI.h"

Inventory* Inventory::GlobalInventory = nullptr;

//몬스터, 농작물 등의 오브젝트는 item* 를 멤버변수로 가지며, 특정 함수가 실행되면 동적할당 후 아이템의 이미지, 이름을 설정한 뒤 인벤토리의 itemlist에 들어가도록 구현

Inventory::Inventory()
{
    GlobalInventory = this;
}

Inventory::~Inventory()
{
    //아이템 메모리 해제
    for (int i = 0; i < ItemList.size(); i++)
    {
        if (ItemList[i] != nullptr)
        {
           delete ItemList[i];
        }
    }
}

void Inventory::Start()
{
    InitInventory();
    CreateItem("PickIcon.bmp");
    CreateItem("WateringIcon.bmp");
    CreateItem("AxeIcon.bmp");
    CreateItem("HoeIcon.bmp");
}

void Inventory::Update(float _DeltaTime)
{
    SetItemPos();
}

void Inventory::Render(float _Time)
{
}

void Inventory::OpenInventory()
{
    if(InventoryRender->IsUpdate() == false)
    {
        InventoryRender->SetPosition(GetLevel()->GetCameraPos() + (GameEngineWindow::GetScreenSize().half()));
        InventoryRender->On();

        if (SelectedItem != nullptr) 
        {
            SelectedLine->On();
        }

        AllItemOn();

        UI::GetUI()->UI_ONOFF();
    }

    else
    {
        InventoryRender->Off();
        SelectedLine->Off();

        AllItemOff();

        UI::GetUI()->UI_ONOFF();
    }
}

void Inventory::AllItemOn()
{
    for (size_t i = 0; i < GlobalInventory->ItemList.size(); i++)
    {
        GlobalInventory->ItemList[i]->GetRenderImage()->On();
    }
}


void Inventory::AllItemOff()
{
    for (size_t i = 0; i < GlobalInventory->ItemList.size(); i++)
    {
        GlobalInventory->ItemList[i]->GetRenderImage()->Off();
    }
}

void Inventory::InitInventory()
{
    InventoryRender = CreateRender("Inventory.bmp", 2);

    InventoryRender->SetPosition(GetLevel()->GetCameraPos()+(GameEngineWindow::GetScreenSize().half()));
    InventoryRender->SetScaleToImage();
    InventoryRender->Off();

    SelectedLine = CreateRender("SelectedLine.BMP", 2);
    SelectedLine->SetScaleToImage();
    SelectedLine->Off();

    ItemList.reserve(30);

    if (GameEngineInput::IsKey("ChangeItem") == false)
    {
        GameEngineInput::CreateKey("ChangeItem", VK_TAB);
    }

}

Item* Inventory::GetLastItem()
{
    size_t Num =GlobalInventory->ItemList.size();
    return GlobalInventory->ItemList[Num - 1];
}

void Inventory::CreateItem(std::string_view _Name)
{
    Item* NewItem = new Item(_Name);
    NewItem->SetItemRender(GlobalInventory->CreateRender(_Name, 2));
    GlobalInventory->ItemList.push_back(NewItem);

    if (GlobalInventory->SelectedItem == nullptr)
    {
        GlobalInventory->SelectedItem = GlobalInventory->ItemList[0];
    }
}

void Inventory::SetItemPos()
{
    for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
    {
        if(ItemOrder < 10)
        {
            GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder) * 64, 148.0f });
        }
        else if(ItemOrder < 20)
        {
            GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder - 10) * 64, 148.0f + 64 });
        }
        else if(ItemOrder < 30)
        {
            GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(GetLevel()->GetCameraPos() + float4{ 353.0f + (ItemOrder - 20) * 64, 148.0f + 128 });
        }
    }
}

std::string Inventory::GetSelectedItemName()
{
    if (GlobalInventory->SelectedItem != nullptr)
    {
        return GlobalInventory->SelectedItem->GetItemName();
    }
    else
    {
        return "";
    }
}

Item* Inventory::GetSelectedItem()
{
    if (GlobalInventory->SelectedItem != nullptr)
    {
        return GlobalInventory->SelectedItem;
    }
    else
    {
        return nullptr;
    }
}

void Inventory::ChangeSelectedItem()
{
    if (GlobalInventory->SelecetedItemIndex + 1 == GlobalInventory->ItemList.size())
    {
        GlobalInventory->SelectedItem = GlobalInventory->ItemList[0];
        GlobalInventory->SelecetedItemIndex = 0;
        GlobalInventory->SelectedLine->SetPosition(GetSelectedItem()->GetItemRenderPos());
    }
    else if (GlobalInventory->SelecetedItemIndex + 1 < GlobalInventory->ItemList.size())
    {
        GlobalInventory->SelectedItem = GlobalInventory->ItemList[GlobalInventory->SelecetedItemIndex + 1 ];
        ++(GlobalInventory->SelecetedItemIndex);
        GlobalInventory->SelectedLine->SetPosition(GetSelectedItem()->GetItemRenderPos());
    }
}