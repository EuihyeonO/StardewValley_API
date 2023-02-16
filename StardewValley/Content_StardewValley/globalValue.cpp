#include "globalValue.h"
#include "Level_Farm.h"
#include "Level_House.h"
#include "Level_Road.h"

float4 globalValue::cameraLimitPos = {0,0};
std::vector<Inventory*> globalValue::InventoryList;
std::string_view globalValue::CurLevelName;

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

void globalValue::ChangeAllSelectedItem()
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->ChangeSelectedItem();
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
}