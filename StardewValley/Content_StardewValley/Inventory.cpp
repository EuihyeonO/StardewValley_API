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
        std::string_view String = "PickIcon.BMP";
        //createrender로 만들어진게 아니라서, update가 진행되지 않는다.
        Item* NewItem = new Item(String);
        NewItem->SetItemRender(CreateRender(String, 2));
        //item을 actor로 만들 필요는 없을 듯 inventory가 update되면 같이 update되도록 설계
        ItemList.push_back(NewItem);       
    }
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
        AllItemOff();
        GetInventoryRender()->Off();
        UI::GetUI()->UI_ONOFF();
    }
}

void Inventory::AllItemOn()
{
    for (size_t i = 0; i < GlobalInventory->ItemList.size(); i++)
    {
        //GlobalInventory->ItemList[i]->On();
    }
}


void Inventory::AllItemOff()
{
    for (size_t i = 0; i < GlobalInventory->ItemList.size(); i++)
    {
        //GlobalInventory->ItemList[i]->Off();
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