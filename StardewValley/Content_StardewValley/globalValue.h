#pragma once
#include "Item.h"
#include "Inventory.h"
#include <GameEngineBase/GameEngineMath.h>

#include <vector>
#include <string>
#include <string_view>

class UI;
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

    static void AddUIToList(UI* _UI)
    {
        UIList.push_back(_UI);
    }

    static std::vector<UI*> GetUIList()
    {
        return UIList;
    }
    static int GetKeyInput();
    static void ChangeAllQuickSlot();
    static void ChangeAllQuickSlotItem(int _Num);

    static void UI_OnOff(const std::string_view& _Name);
    static void OpenInventory(const std::string_view& _Name);

    static void CreateItemToAllInventory(std::string_view _Name, int _ItemType);
    static void CreateItemToAllInventory(int _SeedName);
    static void AllInventoryItemOn();
    static void AllInventoryDelete();
    static void AllInventoryDelete(int Index);
    static void AllInventoryUpdate();
    static void SetMoney(int Num)
    {
        money = Num;
    }

    static int GetMoney()
    {
        return money;
    }

    static void SetCurLevelName(std::string_view _name)
    {
        CurLevelName = _name;
    }

    static Item* GetSelectedItem();
    static std::string GetSelectedItemName();
    static bool isUpdate_CurLevelInventory(const std::string_view& _Name);

    globalValue();
	~globalValue();

    globalValue(const globalValue& _Other) = delete;
    globalValue(globalValue&& _Other) noexcept = delete;
    globalValue& operator=(const globalValue& _Other) = delete;
    globalValue& operator=(globalValue&& _Other) noexcept = delete;

protected:

private:
    static std::vector<Inventory*> InventoryList;
    static std::vector<UI*> UIList;

    static float4 cameraLimitPos;
    static std::string_view CurLevelName;

    static int money;
};
