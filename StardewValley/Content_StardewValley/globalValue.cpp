#include "globalValue.h"

float4 globalValue::cameraLimitPos = {0,0};
std::vector<Inventory*> globalValue::InventoryList;

globalValue::globalValue()
{
}

globalValue::~globalValue()
{

}

void globalValue::CreateItemToAllInventory(std::string_view _Name)
{
    size_t size = InventoryList.size();

    for (int i = 0; i < size; i++)
    {
        InventoryList[i]->CreateItem(_Name);
    }
}