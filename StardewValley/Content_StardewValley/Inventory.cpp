#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

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
        delete ItemList[i];
    }
}

void Inventory::Start()
{
    InitInventory();
}

void Inventory::Update(float _DeltaTime)
{
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
        GlobalInventory->ItemList[i]->GetItemRender()->On();
    }
}


void Inventory::AllItemOff()
{
    for (size_t i = 0; i < GlobalInventory->ItemList.size(); i++)
    {
        GlobalInventory->ItemList[i]->GetItemRender()->Off();
    }
}

void Inventory::InitInventory()
{
    InventoryRender = CreateRender("Inventory.bmp", 2);
    InventoryRender->SetPosition(GetLevel()->GetCameraPos()+(GameEngineWindow::GetScreenSize().half()));
    InventoryRender->SetScaleToImage();
    InventoryRender->Off();

    ItemList.reserve(30);
}

Item* Inventory::GetLastItem()
{
    size_t Num =GlobalInventory->ItemList.size();
    return GlobalInventory->ItemList[Num - 1];
}