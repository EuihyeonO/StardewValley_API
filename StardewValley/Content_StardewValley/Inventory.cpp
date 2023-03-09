#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/NumberRenderObject.h>

#include "Inventory.h"
#include "Player.h"
#include "UI.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "globalValue.h"
#include "globalInterface.h"
#include "ContentsEnum.h"
#include "Pierre.h"
#include "SellBox.h"

Inventory* Inventory::GlobalInventory = nullptr;

//몬스터, 농작물 등의 오브젝트는 item* 를 멤버변수로 가지며, 특정 함수가 실행되면 동적할당 후 아이템의 이미지, 이름을 설정한 뒤 인벤토리의 itemlist에 들어가도록 구현

Inventory::Inventory()
{   
    GlobalInventory = this;
    globalInterface::AddItemListToList(this);
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
    SellItem();
    RoadItem();
}

void Inventory::Render(float _Time)
{    
}

void Inventory::OpenInventory()
{
    if(InventoryRender->IsUpdate() == false)
    {
        InventoryRender->SetPosition((GameEngineWindow::GetScreenSize().half()));
        InventoryRender->On();
        QuickSlotRender->Off();
        
        CurGold.SetValue(globalValue::GetMoney());
        CurGold.On();

        TotalGold.SetValue(globalValue::GetTotalRevenue());
        TotalGold.On();
        SetItemPos();
    }

    else
    {
        InventoryRender->Off();
        CurGold.Off();
        TotalGold.Off();
        QuickSlotRender->On();

        SetItemPos();

    }
}

void Inventory::InventoryOn()
{
    InventoryRender->SetPosition((GameEngineWindow::GetScreenSize().half()));
    InventoryRender->On();
    QuickSlotRender->Off();

    CurGold.SetValue(globalValue::GetMoney());
    CurGold.On();

    TotalGold.SetValue(globalValue::GetTotalRevenue());
    TotalGold.On();
    SetItemPos();
}

void Inventory::InventoryOff()
{
    InventoryRender->Off();
    CurGold.Off();
    TotalGold.Off();
    QuickSlotRender->On();

    SetItemPos();
}

void Inventory::AllItemOn()
{
    for (size_t i = 0; i < ItemList.size(); i++)
    {
        ItemList[i]->On();
    }
}


void Inventory::AllItemOff()
{
    for (size_t i = 0; i < ItemList.size(); i++)
    {
        if(false == isPierreInventory && false == ItemList[i]->GetIsHarvested())
        {
            ItemList[i]->Off();
        }
        else if (true == isPierreInventory)
        {
            ItemList[i]->Off();
        }
    }
}


void Inventory::InitInventory()
{
    Screensize = GameEngineWindow::GetScreenSize();

    CameraPos = GetLevel()->GetCameraPos();

    InventoryRender = CreateRender("Inventory.bmp", 152);

    InventoryRender->SetPosition(CameraPos+(GameEngineWindow::GetScreenSize().half()));
    InventoryRender->SetScaleToImage();
    InventoryRender->Off();
    InventoryRender->EffectCameraOff();

    QuickSlotRender = CreateRender("QuickSlot.bmp", 152);
    QuickSlotRender->SetScaleToImage();
    QuickSlotRender->SetPosition({ (Screensize.x / 2.0f) , Screensize.y - 45.0f });
    QuickSlotRender->EffectCameraOff();


    SelectedLine = CreateRender("SelectedLine.BMP", 152);
    SelectedLine->SetScaleToImage();
    SelectedLine->EffectCameraOff();

    ItemList.reserve(30);

    CurGold.SetOwner(this);
    CurGold.SetImage("NumberSmall.bmp", { 16, 24 }, 202, RGB( 134, 134, 134 ), "NumberSmall.bmp");
    CurGold.SetValue(0);
    CurGold.SetAlign(Align::Right);
    CurGold.SetCameraEffect(false);
    CurGold.SetRenderPos({ 810, 507 });
    CurGold.Off();

    TotalGold.SetOwner(this);
    TotalGold.SetImage("NumberSmall.bmp", { 16, 24 }, 202, RGB(134, 134, 134), "NumberSmall.bmp");
    TotalGold.SetValue(0);
    TotalGold.SetAlign(Align::Right);
    TotalGold.SetCameraEffect(false);
    TotalGold.SetRenderPos({ 810, 567 });
    TotalGold.Off();

    if (GameEngineInput::IsKey("ChangeQuickSlot") == false)
    {
        GameEngineInput::CreateKey("ChangeQuickSlot", VK_TAB);
    }

}


void Inventory::CreateItem(std::string_view _Name, int _ItemType, bool isHarvest)
{
    int ItemIndex = IsExistInInventory(_Name);

    if (-1 != ItemIndex)
    {
        ItemList[ItemIndex]->PlusQuntity();

        if (ItemList[ItemIndex]->GetItemType() == static_cast<int>(ItemType::Crops) && isHarvest == false)
        {
            ItemList[ItemIndex]->SetIsHarvestied();
        }

        return;
    }
         
    if (SelectedItemIndex< 0)
    {
        SelectedItemIndex = 0;
    }

    size_t size = ItemList.size();

    ItemList.push_back(GetLevel()->CreateActor<Item>());
    ItemList[ItemList.size() - 1]->ItemInit(_Name, _ItemType);

    if (true == isBoxInventory && false == SellBox::IsBOxOn())
    {
        ItemList[ItemList.size() - 1]->Off();
    }

    if (SelectedItem == nullptr)
    {
        SelectedItem = ItemList[0];
        SetItemPos();
        SelectedItemIndex = 0;
        SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());
    }

    CameraPosUpdate();
    SetItemPos();
}

void Inventory::CreateItem(int Seedtype)
{
    if (Seedtype == SeedName::Parsnip)
    {
        CreateItem("IconParsnip.BMP", static_cast<int>(ItemType::Crops));
        return;
    }
    else if (Seedtype == SeedName::Cauliflower)
    {
        CreateItem("IconCauliflower.BMP", static_cast<int>(ItemType::Crops));
        return;
    }
    else if (Seedtype == SeedName::Garlic)
    {
        CreateItem("IconGarlic.BMP", static_cast<int>(ItemType::Crops));
        return;
    }
    else if (Seedtype == SeedName::Bean)
    {
        CreateItem("IconBean.BMP", static_cast<int>(ItemType::Crops));
        return;
    }
}

void Inventory::CreateItem_Minaral(int _MinenalName)
{
    if (_MinenalName == static_cast<int>(MineralName::Stone))
    {
        CreateItem("IconStone.BMP", static_cast<int>(ItemType::Mineral));
        return;
    }
    else if (_MinenalName == static_cast<int>(MineralName::Topaz))
    {
        CreateItem("IconTopaz.BMP", static_cast<int>(ItemType::Mineral));
        return;
    }
    else if (_MinenalName == static_cast<int>(MineralName::Iron))
    {
        CreateItem("IconIron.BMP", static_cast<int>(ItemType::Mineral));
        return;
    }

}

void Inventory::CameraPosUpdate()
{
    CameraPos = GetLevel()->GetCameraPos();
}

void Inventory::QuickSlotUpdate()
{   
    SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());
    
    if (SelectedItem != nullptr)
    {
        SelectedItem->GetRenderImage()->SetScale({ 52,52 });
    }

    if (ItemList.size() >= 1)
    {
        SelectedLine->On();
    }
    else
    {
        SelectedItem = nullptr;
        SelectedLine->Off();
    }

    if (QuickSlotOrder > (ItemList.size()-1) / 10)
    {
        ChangeQuickSlot();
    }
}

void Inventory::SetQuickSlotPos(float4 _Pos)
{
    float4 ScreenSize = GameEngineWindow::GetScreenSize();

    GlobalInventory->QuickSlotRender->SetPosition(_Pos + float4((ScreenSize.hx()), ScreenSize.y - 45.0f));
    GlobalInventory->SelectedLine->SetPosition(GlobalInventory->SelectedItem->GetItemRenderPos());
}


void Inventory::SetItemPos()
{
    HDC hdc = GameEngineWindow::GetWindowBackBufferHdc();
    CameraPos = GetLevel()->GetCameraPos();

    // 핸들  X좌표 Y좌표 문자열 문자열길이
    std::string Quantity;

    if (isBoxInventory == true)
    {
        if (false == IsUpdate())
        {
            return;
        }
        else
        {
            for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
            {

                if (ItemOrder < 10)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder) * 64, 580.0f });
                }
                else if (ItemOrder < 20)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder - 10) * 64, 580.0f + 64 });
                }
                else if (ItemOrder < 30)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder - 20) * 64, 580.0f + 128 });
                }

                //아이템 개수출력
                if (ItemList[ItemOrder]->GetQuantity() > 1)
                {
                    float4 ItemPos = ItemList[ItemOrder]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
                }
            }
        }
        return;
    }

    if (isPierreInventory == true)
    {
        if (Pierre::IsOpenShop() == false)
        {
            return;
        }

        else
        {

            for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
            {

                if (ItemOrder < 10)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 560.0f + (ItemOrder) * 64, 480.0f });
                }
                else if (ItemOrder < 20)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 560.0f + (ItemOrder - 10) * 64, 480.0f + 64 });
                }
                else if (ItemOrder < 30)
                {
                    ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 560.0f + (ItemOrder - 20) * 64, 480.0f + 128 });
                }

                //아이템 개수출력
                if (ItemList[ItemOrder]->GetQuantity() > 1)
                {
                    float4 ItemPos = ItemList[ItemOrder]->GetRenderImage()->GetPosition() - GetLevel()->GetCameraPos();
                }
            }
        }
        return;
    }

    if(QuickSlotRender->IsUpdate() == false)
    {
        for (int ItemOrder = 0; ItemOrder < GetNumOfItem(); ItemOrder++)
        {
                AllItemOn();

            if (ItemOrder < 10)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder) * 64, 172.0f });            
            }
            else if (ItemOrder < 20)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder - 10) * 64, 172.0f + 64 });
            }
            else if (ItemOrder < 30)
            {
                ItemList[ItemOrder]->GetRenderImage()->SetPosition(float4{ 352.0f + (ItemOrder - 20) * 64, 172.0f + 128 });
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
        size_t Num = GetNumOfItem();
        int StartNum = (QuickSlotOrder) * 10;

        AllItemOff();

        int count = 0;

        for (; StartNum < Num; StartNum++)
        {
            if (count >= 10)
            {
                return;
            }


            ItemList[StartNum]->GetRenderImage()->SetPosition(float4{ 352.0f + (StartNum%10) * 64, 723.0f });
            ItemList[StartNum]->On();

            ++count;
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
    if (_InputKey > ItemList.size() - (QuickSlotOrder) * 10)
    {
        return;
    }

    SelectedItemIndex = (QuickSlotOrder) * 10 + _InputKey- 1;
    SelectedItem = ItemList[SelectedItemIndex];
}

void Inventory::ChangeSelectedItem()
{
    --SelectedItemIndex;

    if (SelectedItemIndex <= 0)
    {
        SelectedItemIndex = 0;
    }

    SelectedItem = ItemList[SelectedItemIndex];
}

/*이미있는 아이템이라면 인덱스를 반환, 없다면 -1을 반환*/
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
        ItemList[i]->GetRenderImage()->SetScale({ 45,45 });

        if (0 >= ItemList[i]->GetQuantity())
        {
            ItemList[i]->Death();
            ItemList.erase(ItemList.begin() + i);
            ChangeSelectedItem();
            SetItemPos();
            --size;
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
    ++QuickSlotOrder;

    if (QuickSlotOrder > (ItemList.size()-1) / 10)
    {
        QuickSlotOrder = 0;
    }

    SetItemPos();
    ChangeSelectedItem(1);
}

void Inventory::SellItem()
{
    if (false == isPierreInventory && false == isBoxInventory)
    {
        return;
    }

    size_t Size = ItemList.size();

    for (int i = 0; i < Size; i++)
    {
        if (true == ItemList[i]->isAbleToSell() && true == ItemList[i]->isCollisionToMouse() && true == GameEngineInput::IsDown("EngineMouseLeft"))
        {
            if(true == isBoxInventory)
            {
                globalInterface::AllInventorySaveItem(ItemList[i]);
            }

            globalValue::PlusToMoney(ItemList[i]->GetPrice());
            globalValue::PlusToTotalRevenue(ItemList[i]->GetPrice());

            globalInterface::AllInventoryUpdate();
            GameEngineResources::GetInst().SoundPlay("Sell.wav");

            globalInterface::AllInventoryDelete(i);

            Size = ItemList.size();
        }
    }
}

bool Inventory::isInInventory(const std::string_view& _ItemName)
{
    for (int i = 0; i < ItemList.size(); i++)
    {
        if (ItemList[i]->GetItemName() == _ItemName)
        {
            return true;
        }
    }

    return false;
}


void Inventory::SetAllItemPOrder(int num)
{
    for (int i = 0; i < ItemList.size(); i++)
    {
        ItemList[i]->GetRenderImage()->SetOrder(num);
    }
}

void Inventory::SaveItem(Item* _item)
{
    std::string itemname = _item->GetItemName();
    int itemtype = _item->GetItemType();

    std::string_view CopyName = itemname;

    if (LastSellItem != nullptr && LastSellItemName == itemname)
    {
        NumOfLastSellItem += 1;
        LastSellItem->PlusQuntity();
    }

    else
    {
        if (LastSellItem != nullptr)
        {
            LastSellItem->Death();
        }

        LastSellItem = GetLevel()->CreateActor<Item>();

        LastSellItem->ItemInit(CopyName, itemtype);
        LastSellItem->SetPos({ 640, 490 });
        LastSellItem->GetRenderImage()->SetScale({ 55,55 });
        LastSellItem->GetRenderImage()->SetOrder(202);

        LastSellItemName = itemname;
        NumOfLastSellItem = 1;
    }
}

void Inventory::RoadItem()
{
    //if (false == isBoxInventory)
    //{
    //    return;
    //}
    //
    //if (false == IsUpdate())
    //{
    //    return;
    //}
    

    if (LastSellItem == nullptr)
    {
        return;
    }

    if (true == LastSellItem->isCollisionToMouse() && true == GameEngineInput::IsDown("EngineMouseLeft"))
    {
        std::string itemname = LastSellItem->GetItemName();
        int itemtype = LastSellItem->GetItemType();

        for(int i =0; i<LastSellItem->GetQuantity(); i++)
        {           
            if(true == isBoxInventory)
            {
                globalInterface::CreateItemToAllInventory(itemname, itemtype, true);
                globalValue::PlusToMoney(-LastSellItem->GetPrice());
                globalValue::PlusToTotalRevenue(-LastSellItem->GetPrice());
            }
        }

        LastSellItem->Off();
        LastSellItem->Death();
        LastSellItem = nullptr;
    }
}

void Inventory::LastSellItemDeath()
{
    if (nullptr != LastSellItem)
    {
        LastSellItem->Death();
        LastSellItem = nullptr;
    }
}

Item* Inventory::GetLastSellItem()
{
    if (nullptr != LastSellItem)
    {
        return LastSellItem;
    }

    else  nullptr;
}