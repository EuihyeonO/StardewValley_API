#pragma once
#include "Item.h"
#include "Inventory.h"
#include <GameEngineBase/GameEngineMath.h>

#include <vector>
#include <string>
#include <string_view>

class AffectionBox;
class UI;
class globalInterface
{

public:
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


    static void AddAffectionToList(AffectionBox* _AffectionBox)
    {
        AffectionBoxList.push_back(_AffectionBox);
    }

    static std::vector<AffectionBox*> GetAffectionList()
    {
        return AffectionBoxList;
    }

    static void AllAffectionUp(std::string& _NpcName);
    static void AllAffectionDown(std::string& _NpcName);
    static void AllGiftCountUp(std::string& _NpcName);
    static void AllGiftCountClear();

    static bool isMenuOpen()
    {
        return isOpenMenu;
    }

    static Item* GetSelectedItem();
    static std::string GetSelectedItemName();

    static bool isUpdate_CurLevelInventory();

    static void ChangeAllQuickSlot();
    static void ChangeAllQuickSlotItem(int _Num);

    static bool IsInInventory(const std::string_view& _ItemName);

    static void UI_OnOff();
    static void OpenInventory();

    static void AllInventorySaveItem(Item* _item);
    static void AllInventoryLastSellItemDeath();

    static void CreateItemToAllInventory(std::string_view _Name, int _ItemType, bool isHarvested = false );
    static void CreateItemToAllInventory(int _SeedName);
    static void CreateItemToAllInventory_Mineral(int _MineralName);
    static void AllInventoryItemOn();
    static void AllInventoryItemOff();
    static void AllInventoryDelete();
    static void AllInventoryDelete(int Index);
    static void AllInventoryUpdate();
    static void MenuOnOff();

	globalInterface();
	~globalInterface();

	globalInterface(const globalInterface& _Other) = delete;
	globalInterface(globalInterface&& _Other) noexcept = delete;
	globalInterface& operator=(const globalInterface& _Other) = delete;
	globalInterface& operator=(globalInterface&& _Other) noexcept = delete;

protected:

private:
    static std::vector<Inventory*> InventoryList;
    static std::vector<UI*> UIList;
    static std::vector<AffectionBox*> AffectionBoxList;

    static bool isOpenMenu;
};

