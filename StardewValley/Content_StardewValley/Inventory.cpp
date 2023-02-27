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
#include "ContentsEnum.h"
#include "Pierre.h"

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
    SellItem();
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
        ItemList[i]->Off();
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
    InventoryRender->EffectCameraOff();

    QuickSlotRender = CreateRender("QuickSlot.bmp", 150);
    QuickSlotRender->SetScaleToImage();
    QuickSlotRender->SetPosition({ (Screensize.x / 2.0f) , Screensize.y - 45.0f });
    QuickSlotRender->EffectCameraOff();


    SelectedLine = CreateRender("SelectedLine.BMP", 150);
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


void Inventory::CreateItem(std::string_view _Name, int _ItemType)
{
    int ItemIndex = IsExistInInventory(_Name);

    if (-1 != ItemIndex)
    {
        ItemList[ItemIndex]->PlusQuntity();

        if (ItemList[ItemIndex]->GetItemType() == static_cast<int>(ItemType::Crops))
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

void Inventory::CameraPosUpdate()
{
    CameraPos = GetLevel()->GetCameraPos();
}

void Inventory::QuickSlotUpdate()
{   
    SelectedLine->SetPosition(SelectedItem->GetItemRenderPos());

    if (ItemList.size() >= 1)
    {
        SelectedLine->On();
    }
    else
    {
        SelectedItem = nullptr;
        SelectedLine->Off();
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
        if (0 >= ItemList[i]->GetQuantity())
        {
            ItemList[i]->Death();
            ItemList.erase(ItemList.begin() + i);
            ChangeSelectedItem();
            SetItemPos();
            break;
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

    if (QuickSlotOrder >= 3)
    {
        QuickSlotOrder = 0;
    }

    SetItemPos();
}

void Inventory::SellItem()
{
    if (isPierreInventory == false)
    {
        return;
    }

    size_t Size = ItemList.size();

    for (int i = 0; i < Size; i++)
    {
        if (ItemList[i]->isAbleToSell() == true && ItemList[i]->isCollisionToMouse() == true && GameEngineInput::IsDown("EngineMouseLeft") == true)
        {
            globalValue::AllInventoryDelete(i);
            globalValue::PlusToMoney(ItemList[i]->GetPrice());
            globalValue::PlusToTotalRevenue(ItemList[i]->GetPrice());
            globalValue::AllInventoryUpdate();
        }
    }
}
