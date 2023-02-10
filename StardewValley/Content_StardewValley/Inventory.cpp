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
    QuickSlotUpdate();
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

        QuickSlotRender->Off();

        UI::GetUI()->UI_ONOFF();
    }

    else
    {
        InventoryRender->Off();

        QuickSlotRender->On();


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
    CameraPos = GetLevel()->GetCameraPos();
    float4 Screensize = GameEngineWindow::GetScreenSize();

    InventoryRender = CreateRender("Inventory.bmp", 2);

    InventoryRender->SetPosition(CameraPos+(GameEngineWindow::GetScreenSize().half()));
    InventoryRender->SetScaleToImage();
    InventoryRender->Off();

    QuickSlotRender = CreateRender("QuickSlot.bmp", 2);
    QuickSlotRender->SetScaleToImage();
    QuickSlotRender->SetPosition({ CameraPos.x + (Screensize.x / 2.0f) , CameraPos.y + Screensize.y - 45.0f });

    SelectedLine = CreateRender("SelectedLine.BMP", 2);
    SelectedLine->SetScaleToImage();

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
        GlobalInventory->SetItemPos();
        GlobalInventory->SelectedLine->SetPosition(GetSelectedItem()->GetItemRenderPos());
    }
}

void Inventory::CameraPosUpdate()
{
    CameraPos = GetLevel()->GetCameraPos();
}

void Inventory::QuickSlotUpdate()
{
    CameraPosUpdate();
    float4 Screensize = GameEngineWindow::GetScreenSize();

    QuickSlotRender->SetPosition({ CameraPos.x + (Screensize.x / 2.0f) , CameraPos.y + Screensize.y - 45.0f });   
}

void Inventory::SetItemPos()
{
    if(QuickSlotRender->IsUpdate() == false)
    {
        for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
        {
            if (ItemOrder < 10)
            {
                GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 353.0f + (ItemOrder) * 64, 172.0f });
            }
            else if (ItemOrder < 20)
            {
                GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 353.0f + (ItemOrder - 10) * 64, 172.0f + 64 });
            }
            else if (ItemOrder < 30)
            {
                GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 353.0f + (ItemOrder - 20) * 64, 172.0f + 128 });
            }
        }
    }   

    else if (QuickSlotRender->IsUpdate() == true)
    {
        for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
        {
            if (ItemOrder >= 10)
            {
                return;
            }
            GlobalInventory->ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 353.0f + (ItemOrder) * 64, 723.0f });
        }
    }

    GlobalInventory->SelectedLine->SetPosition(GetSelectedItem()->GetItemRenderPos());
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
    }
    else if (GlobalInventory->SelecetedItemIndex + 1 < GlobalInventory->ItemList.size())
    {
        GlobalInventory->SelectedItem = GlobalInventory->ItemList[GlobalInventory->SelecetedItemIndex + 1 ];
        ++(GlobalInventory->SelecetedItemIndex);
    }
}