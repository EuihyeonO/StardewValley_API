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

//����, ���۹� ���� ������Ʈ�� item* �� ��������� ������, Ư�� �Լ��� ����Ǹ� �����Ҵ� �� �������� �̹���, �̸��� ������ �� �κ��丮�� itemlist�� ������ ����

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
    Screensize = GameEngineWindow::GetScreenSize();

    CameraPos = GetLevel()->GetCameraPos();

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

    if (GameEngineInput::IsKey("ChangeQuickSlot") == false)
    {
        GameEngineInput::CreateKey("ChangeQuickSlot", VK_TAB);
    }

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

    QuickSlotRender->SetPosition(CameraPos + float4((Screensize.x / 2) , Screensize.y - 45.0f));
   
    if (ItemList.size() >= 1)
    {
        SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());
    }
}

void Inventory::SetItemPos()
{

    HDC hdc = GameEngineWindow::GetWindowBackBufferHdc();

    // �ڵ�  X��ǥ Y��ǥ ���ڿ� ���ڿ�����
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

            //������ �������
            if (ItemList[ItemOrder]->GetQuantity() > 1)
            {
                float4 ItemPos = ItemList[ItemOrder]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
            }
        }
    }   

    else if (QuickSlotRender->IsUpdate() == true)
    {
        size_t Num = GetNumOfItem();
        int StartNum = (QuickSlotOrder - 1) * 10;

        for (; StartNum < GetNumOfItem(); StartNum++)
        {

            if (ItemList[StartNum]->GetIsHarvesting() == true)
            {
                return;
            }

            ItemList[StartNum]->GetRenderImage()->SetPosition(CameraPos + float4{ 352.0f + (StartNum%10) * 64, 723.0f });

            //������ �������
            if (ItemList[StartNum]->GetQuantity() > 1)
            {
                float4 ItemPos = ItemList[StartNum]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
            }
        }
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

void Inventory::ChangeSelectedItem(int _InputKey)
{
    if (_InputKey > (QuickSlotOrder - 1) * 10 + ItemList.size())
    {
        return;
    }

    SelectedItemIndex = (QuickSlotOrder - 1) * 10 + _InputKey;
    SelectedItem = ItemList[SelectedItemIndex - 1];
}

/*�̹��ִ� �������̶�� �ε����� ��ȯ, ���ٸ� -1�� ��ȯ*/
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

void Inventory::ChangeGlobalInventory(Inventory* _Inventory)
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
            ChangeSelectedItem(--SelectedItemIndex);
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

void Inventory::ChangeQuickSlot()
{
    if (ItemList.size() <= 10)
    {
        return;
    }

    ++QuickSlotOrder;

    if (QuickSlotOrder > 3)
    {
        QuickSlotOrder = 0;
    }
}