#pragma once
#include "Item.h"
#include "Inventory.h"
#include <GameEngineBase/GameEngineMath.h>
#include <vector>

class globalValue
{

public:

    static float4 GetcameraLimitPos()
    {
        return cameraLimitPos;
    }

    static void SetcameraLimitPos(float4 _pos)
    {
        cameraLimitPos = _pos;
    }

    static void AddItemListToList(Inventory* _inventory)
    {
        InventoryList.push_back(_inventory);
    }

    static std::vector<Inventory*> GetInventoryList()
    {
        return InventoryList;
    }

    static void CreateItemToAllInventory(std::string_view _Name, int _ItemType);
    static void ChangeAllSelectedItem();
    static void AllInventoryItemOn();

    globalValue();
	~globalValue();

    globalValue(const globalValue& _Other) = delete;
    globalValue(globalValue&& _Other) noexcept = delete;
    globalValue& operator=(const globalValue& _Other) = delete;
    globalValue& operator=(globalValue&& _Other) noexcept = delete;

protected:

private:
    static std::vector<Inventory*> InventoryList;
    static float4 cameraLimitPos;
};
