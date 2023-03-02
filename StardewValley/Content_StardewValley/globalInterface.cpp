#include "globalInterface.h"
#include "globalValue.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "Level_Road.h"
#include "Level_Mine.h"
#include "MenuButton.h"
#include "UI.h"
#include "ContentsEnum.h"
#include "Pierre.h"
#include "AffectionBox.h"

#include <GameEnginePlatform/GameEngineInput.h>

std::vector<Inventory*> globalInterface::InventoryList;
std::vector<UI*> globalInterface::UIList;
std::vector<AffectionBox*> globalInterface::AffectionBoxList;
bool globalInterface::isOpenMenu = false;

globalInterface::globalInterface()
{
}

globalInterface::~globalInterface()
{
}

void globalInterface::CreateItemToAllInventory(std::string_view _Name, int _ItemType)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem(_Name, _ItemType);
    }
}

void globalInterface::CreateItemToAllInventory(int _SeedName)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem(_SeedName);
    }
}

void globalInterface::CreateItemToAllInventory_Mineral(int _MineralName)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem_Minaral(_MineralName);
    }
}


void globalInterface::AllInventoryItemOn()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->AllItemOn();
    }
}

void globalInterface::AllInventoryDelete()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->GetSelectedItem()->MinusQuntity();
    }
}

void globalInterface::AllInventoryDelete(int Index)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->GetItemList()[Index]->MinusQuntity();
    }
}

Item* globalInterface::GetSelectedItem()
{
    return InventoryList[0]->GetSelectedItem();
}

std::string globalInterface::GetSelectedItemName()
{
    if (InventoryList.size() >= 1)
    {
        if (InventoryList[0]->GetSelectedItem() != nullptr)
        {
            return InventoryList[0]->GetSelectedItemName();
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "";
    }
}

bool globalInterface::isUpdate_CurLevelInventory()
{
    return Inventory::GetInventory()->GetInventoryRender()->IsUpdate();
}

void globalInterface::MenuOnOff()
{
    if (Inventory::GetInventory()->GetInventoryRender()->IsUpdate() == false &&
        AffectionBox::GetGlobalAffectionBox()->GetAffectionBoxRender()->IsUpdate() == false)
    {
        isOpenMenu = true;
        Inventory::GetInventory()->InventoryOn();
        MenuButton::GetGlobalMenuButton()->MenuButtonOn();
        MenuButton::GetGlobalMenuButton()->SetInventoryButtonToSelectedPos();
    }

    else if (Inventory::GetInventory()->GetInventoryRender()->IsUpdate() == true ||
        AffectionBox::GetGlobalAffectionBox()->GetAffectionBoxRender()->IsUpdate() == true)
    {
        isOpenMenu = false;
        Inventory::GetInventory()->InventoryOff();
        AffectionBox::GetGlobalAffectionBox()->AffectionBoxOff();
        MenuButton::GetGlobalMenuButton()->MenuButtonOff();
    }
}

void globalInterface::UI_OnOff()
{
    UI::GetUI()->UI_ONOFF();
}

void globalInterface::ChangeAllQuickSlot()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->ChangeQuickSlot();
    }
}

void globalInterface::ChangeAllQuickSlotItem(int _Num)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->ChangeSelectedItem(_Num);
    }
}


void globalInterface::AllInventoryUpdate()
{
    size_t Size = InventoryList.size();

    for (int i = 0; i < Size; i++)
    {
        InventoryList[i]->ItemUpdate();
    }
}