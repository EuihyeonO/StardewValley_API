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
}

void Inventory::Update(float _DeltaTime)
{
    //조건을 나중에 바꿔야 함 (life가 0이 되어 다른 이미지로 render되고 있는 crops와 충돌 등)
    if (GameEngineInput::IsDown("MakeItem"))
    {
        CreateItem("PickIcon.BMP");
    }

    SetItemPos();
}

void Inventory::Render(float _Time)
{
}

void Inventory::OpenInventory()
{
    if(GetInventoryRender()->IsUpdate() == false)
    {
        InventoryRender->SetPosition(GetLevel()->GetCameraPos() + (GameEngineWindow::GetScreenSize().half()));
        GetInventoryRender()->On();
        AllItemOn();

        UI::GetUI()->UI_ONOFF();
    }

    else
    {
        GetInventoryRender()->Off();
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

    ItemList.reserve(30);

    if (GameEngineInput::IsKey("MakeItem") == false)
    {
        GameEngineInput::CreateKey("MakeItem", 'I');
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