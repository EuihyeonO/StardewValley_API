#pragma once
#include <vector>
#include <string_view>

#include <GameEngineCore/GameEngineActor.h>

#include "Item.h"

//class Item;
class Player;
class NumberRenderObject;
class Inventory : public GameEngineActor
{

public:
   

	Inventory();
	~Inventory();
    
    void OpenInventory();
    void InitInventory();


    static Inventory* GetInventory()
    {
        return GlobalInventory;
    }

    GameEngineRender* GetInventoryRender()
    {
        return InventoryRender;
    }

    void InsertToMyInventory(Item* _item)
    {
        ItemList.push_back(_item);
    }
   

    size_t GetNumOfItem()
    {
        return ItemList.size();
    }

    void SetOwnerToPierre()
    {
        isPierreInventory = true;
    }

    int IsExistInInventory(std::string_view& _Name);
   

    void ItemUpdate();
    void CreateItem(std::string_view _Name, int ItemType);
    void CreateItem(int Seedtype);
    void SellItem();

    void ChangeQuickSlot();

    std::string GetSelectedItemName();

    void ChangeSelectedItem(int _InputKey);
    void ChangeSelectedItem();

    Item* GetSelectedItem();

    static void SetGlobalInventory(Inventory* _Inventory)
    {
        GlobalInventory = _Inventory;
    }

    static void ChangeGlobalInventory(Inventory* _Inventory);

    static void SetQuickSlotPos(float4 _pos);

    std::vector<Item*> GetItemList()
    {
        return ItemList;
    }
    
    bool IsPierreInventory()
    {
        return isPierreInventory;
    }

    void AllItemOn();
    void AllItemOff();

    void InventoryOn();
    void InventoryOff();

    void SetItemPos();
    void CameraPosUpdate();
    void QuickSlotUpdate();
    void SelectedItemUpdate();

	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    static Inventory* GlobalInventory;
    
    std::vector<Item*> ItemList;

    Item* SelectedItem = nullptr;
    int SelectedItemIndex = 0;

    GameEngineRender* InventoryRender = nullptr;
    GameEngineRender* QuickSlotRender = nullptr;
    GameEngineRender* SelectedLine = nullptr;

    NumberRenderObject CurGold;
    NumberRenderObject TotalGold;

    float4 CameraPos = { 0,0 };
    float4 Screensize = { 0,0 };

    bool isPierreInventory = false;
    int QuickSlotOrder = 0;
};


