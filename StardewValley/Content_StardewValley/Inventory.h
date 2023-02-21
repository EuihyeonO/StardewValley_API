#pragma once
#include <vector>
#include <string_view>

#include <GameEngineCore/GameEngineActor.h>

#include "Item.h"

//class Item;
class Player;

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

    int IsExistInInventory(std::string_view& _Name);

    int QuickSlotOrder = 1;

    void ItemUpdate();
    void CreateItem(std::string_view _Name, int ItemType);
    void CreateItem(int Seedtype);

    void ChangeQuickSlot();

    std::string GetSelectedItemName();
    void ChangeSelectedItem(int _InputKey);
    Item* GetSelectedItem();

    static void SetGlobalInventory(Inventory* _Inventory)
    {
        GlobalInventory = _Inventory;
    }

    static void ChangeGlobalInventory(Inventory* _Inventory);

    void AllItemOn();
    void AllItemOff();

    void SetItemPos();
    void CameraPosUpdate();
    void QuickSlotUpdate();

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

    float4 CameraPos = { 0,0 };
    float4 Screensize = { 0,0 };
};


