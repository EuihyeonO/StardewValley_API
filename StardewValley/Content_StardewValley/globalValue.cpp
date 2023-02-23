#include "globalValue.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "Level_Road.h"
#include "UI.h"
#include "ContentsEnum.h"
#include "Pierre.h"

#include <GameEnginePlatform/GameEngineInput.h>

float4 globalValue::cameraLimitPos = {0,0};
std::vector<Inventory*> globalValue::InventoryList;
std::string_view globalValue::CurLevelName;
std::vector<UI*> globalValue::UIList;
int globalValue::money = 200;
int globalValue::Day = 1;

globalValue::globalValue()
{
}

globalValue::~globalValue()
{

}

void globalValue::CreateItemToAllInventory(std::string_view _Name, int _ItemType)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem(_Name, _ItemType);
    }
}

void globalValue::CreateItemToAllInventory(int _SeedName)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem(_SeedName);
    }
}

void globalValue::AllInventoryItemOn()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->AllItemOn();
    }
}

void globalValue::AllInventoryDelete()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->GetSelectedItem()->MinusQuntity();
    }
}

void globalValue::AllInventoryDelete(int Index)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->GetItemList()[Index]->MinusQuntity();
    }
}

Item* globalValue::GetSelectedItem()
{
   return InventoryList[0]->GetSelectedItem();
}

std::string globalValue::GetSelectedItemName()
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

bool globalValue::isUpdate_CurLevelInventory(const std::string_view& _Name)
{
    if (_Name == "Farm")
    {
        return Level_Farm::FarmInventory->GetInventoryRender()->IsUpdate();
    }
    else if(_Name == "House")
    {
        return Level_House::HouseInventory->GetInventoryRender()->IsUpdate();
    }
    else if (_Name == "Road")
    {
        return Level_Road::RoadInventory->GetInventoryRender()->IsUpdate();
    }
    else
    {
        return false;
    }
}

void globalValue::OpenInventory(const std::string_view& _Name)
{
    if (_Name == "Farm")
    {
        Level_Farm::FarmInventory->OpenInventory();
    }
    else if (_Name == "House")
    {
        Level_House::HouseInventory->OpenInventory();
    }
    else if (_Name == "Road")
    {
        Level_Road::RoadInventory->OpenInventory();
    }
    else
    {
        false;
    }
}

void globalValue::UI_OnOff(const std::string_view& _Name)
{
    if (_Name == "Farm")
    {
        Level_Farm::FarmUI->UI_ONOFF();
    }
    else if (_Name == "House")
    {
        Level_House::HouseUI->UI_ONOFF();
    }
    else if (_Name == "Road")
    {
        Level_Road::RoadUI->UI_ONOFF();
    }
}

void globalValue::ChangeAllQuickSlot()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->ChangeQuickSlot();
    }
}

void globalValue::ChangeAllQuickSlotItem(int _Num)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->ChangeSelectedItem(_Num);
    }
}

int globalValue::GetKeyInput()
{
    {
        if (Pierre::IsOpenShop() == true)
        {
            return Act::Idle;
        }

        else
        {
            if (true == GameEngineInput::IsDown("MouseInteract"))
            {
                return Act::MouseInteract;
            }

            if (true == GameEngineInput::IsDown("KeyInteract"))
            {
                return Act::KeyInteract;
            }

            else if (true == GameEngineInput::IsPress("LMove") ||
                true == GameEngineInput::IsPress("RMove") ||
                true == GameEngineInput::IsPress("UMove") ||
                true == GameEngineInput::IsPress("DMove"))
            {
                return Act::Move;
            }

            else
            {
                return Act::Idle;
            }
        }
    }
}


void globalValue::AllInventoryUpdate()
{
    size_t Size = InventoryList.size();

    for (int i = 0; i < Size; i++)
    {
        InventoryList[i]->ItemUpdate();
    }
}