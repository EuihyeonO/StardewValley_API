#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Inventory.h"
#include "Player.h"
#include "UI.h"

Inventory* Inventory::GlobalInventory = nullptr;

//����, ���۹� ���� ������Ʈ�� item* �� ��������� ������, Ư�� �Լ��� ����Ǹ� �����Ҵ� �� �������� �̹���, �̸��� ������ �� �κ��丮�� itemlist�� ������ ����

Inventory::Inventory()
{
    GlobalInventory = this;
}

Inventory::~Inventory()
{
    //������ �޸� ����
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
    //������ ���߿� �ٲ�� �� (life�� 0�� �Ǿ� �ٸ� �̹����� render�ǰ� �ִ� crops�� �浹 ��)
    if (GameEngineInput::IsDown("MakeItem"))
    {
        std::string_view String = "PickIcon.BMP";
        //createrender�� ��������� �ƴ϶�, update�� ������� �ʴ´�.
        Item* NewItem = new Item(String);
        NewItem->SetItemRender(CreateRender(String, 2));
        //item�� actor�� ���� �ʿ�� ���� �� inventory�� update�Ǹ� ���� update�ǵ��� ����
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