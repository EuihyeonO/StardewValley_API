#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Inventory.h"
#include "Player.h"
#include "UI.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "globalValue.h"
#include "ContentsEnum.h"

Inventory* Inventory::GlobalInventory = nullptr;

//몬스터, 농작물 등의 오브젝트는 item* 를 멤버변수로 가지며, 특정 함수가 실행되면 동적할당 후 아이템의 이미지, 이름을 설정한 뒤 인벤토리의 itemlist에 들어가도록 구현

Inventory::Inventory()
{
    GlobalInventory = this;
    globalValue::AddItemListToList(this);
}

Inventory::~Inventory()
{
}

void Inventory::Start()
{
    InitInventory();
}

void Inventory::Update(float _DeltaTime)
{
    CameraPosUpdate();
    ItemUpdate();
    QuickSlotUpdate();
    SetItemPos();

    size_t a = globalValue::GetUIList().size();
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

    InventoryRender = CreateRender("Inventory.bmp", 150);

    InventoryRender->SetPosition(CameraPos+(GameEngineWindow::GetScreenSize().half()));
    InventoryRender->SetScaleToImage();
    InventoryRender->Off();

    QuickSlotRender = CreateRender("QuickSlot.bmp", 150);
    QuickSlotRender->SetScaleToImage();
    QuickSlotRender->SetPosition({ CameraPos.x + (Screensize.x / 2.0f) , CameraPos.y + Screensize.y - 45.0f });

    SelectedLine = CreateRender("SelectedLine.BMP", 150);
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

void Inventory::CreateItem(std::string_view _Name, int _ItemType)
{
    int ItemIndex = IsExistInInventory(_Name);

    if (-1 != ItemIndex)
    {
        ItemList[ItemIndex]->PlusQuntity();

        if (ItemList[ItemIndex]->GetItemType() == static_cast<int>(ItemType::Crops))
        {
            ItemList[ItemIndex]->SetItemisHarvesting();
        }

        return;
    }

    ItemList.push_back(GetLevel()->CreateActor<Item>());
    ItemList[ItemList.size() - 1]->ItemInit(_Name, _ItemType);

    if (SelectedItem == nullptr)
    {
        SelectedItem = ItemList[0];
        SetItemPos();
        SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());
    }
}


void Inventory::CameraPosUpdate()
{
    CameraPos = GetLevel()->GetCameraPos();
}

void Inventory::QuickSlotUpdate()
{
    float4 Screensize = GameEngineWindow::GetScreenSize();

    QuickSlotRender->SetPosition(CameraPos + float4((Screensize.x / 2) , Screensize.y - 45.0f));
}

void Inventory::SetItemPos()
{

    HDC hdc = GameEngineWindow::GetWindowBackBufferHdc();

    // 핸들  X좌표 Y좌표 문자열 문자열길이
    std::string Quantity;

    if(QuickSlotRender->IsUpdate() == false)
    {
        for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
        {
            if (ItemList[ItemOrder]->GetIsHarvesting() == true)
            {
                return;
            }

            if (ItemOrder < 10)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 352.0f + (ItemOrder) * 64, 172.0f });            
            }
            else if (ItemOrder < 20)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 352.0f + (ItemOrder - 10) * 64, 172.0f + 64 });
            }
            else if (ItemOrder < 30)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 352.0f + (ItemOrder - 20) * 64, 172.0f + 128 });
            }  

            //아이템 개수출력
            if (ItemList[ItemOrder]->GetQuantity() > 1)
            {
                float4 ItemPos = ItemList[ItemOrder]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
            }
        }
    }   

    else if (QuickSlotRender->IsUpdate() == true)
    {
        size_t ant = GetNumOfItem();

        for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
        {
            if (ItemOrder >= 10)
            {
                return;
            }

            if (ItemList[ItemOrder]->GetIsHarvesting() == true)
            {
                return;
            }

            ItemList[ItemOrder]->GetRenderImage()->SetPosition(CameraPos + float4{ 352.0f + (ItemOrder) * 64, 723.0f });

            //아이템 개수출력
            if (ItemList[ItemOrder]->GetQuantity() > 1)
            {
                float4 ItemPos = ItemList[ItemOrder]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
            }
        }
    }

    if(ItemList.size()>=1)
    {
        SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());
    }

}


Item* Inventory::GetSelectedItem()
{
    if (SelectedItem != nullptr)
    {
        return SelectedItem;
    }
    else
    {
        return nullptr;
    }
}

void Inventory::ChangeSelectedItem()
{
    if (SelecetedItemIndex + 1 == ItemList.size())
    {
        SelectedItem = ItemList[0];
        SelecetedItemIndex = 0;
    }
    else if (SelecetedItemIndex + 1 < ItemList.size())
    {
        SelectedItem = ItemList[SelecetedItemIndex + 1 ];
        ++(SelecetedItemIndex);
    }
}

/*이미 있는 아이템이라면 인덱스를 반환, 없다면 -1을 반환*/
int Inventory::IsExistInInventory(std::string_view& _Name)
{
    size_t size = ItemList.size();

    for (int i = 0; i < size; i++)
    {
        if (_Name == ItemList[i]->GetItemName())
        {
            return i;
        }
    }

    return -1;
}

void Inventory::CopyItemList(Inventory* _Inventory)
{      
    GlobalInventory = _Inventory;
}

void Inventory::ItemUpdate()
{
    size_t size = ItemList.size();

    for (int i = 0; i < size; i++)
    {
        if (0 >= ItemList[i]->GetQuantity())
        {
            ChangeSelectedItem();
            ItemList[i]->Death();
            ItemList.erase(ItemList.begin() + i);
        }
    }
}

std::string Inventory::GetSelectedItemName()
{
    if (SelectedItem != nullptr)
    {
        return SelectedItem->GetItemName();
    }
    else
    {
        return "";
    }
}