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

    static GameEngineRender* GetInventoryRender()
    {
        return GlobalInventory->InventoryRender;
    }

    void InsertToMyInventory(Item* _item)
    {
        ItemList.push_back(_item);
    }
   

    static size_t GetNumOfItem()
    {
        return GlobalInventory->ItemList.size();
    }

    int IsExistInInventory(std::string_view& _Name);

    void CreateItem(std::string_view _Name, int ItemType);

    static Item* GetLastItem();

    static std::string GetSelectedItemName();
    static Item* GetSelectedItem();
    void ChangeSelectedItem();


    static void SetGlobalInventory(Inventory* _Inventory)
    {
        GlobalInventory = _Inventory;
    }

    static void CopyItemList(Inventory* _Inventory);

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
    int SelecetedItemIndex = 0;

    GameEngineRender* InventoryRender = nullptr;
    GameEngineRender* QuickSlotRender = nullptr;
    GameEngineRender* SelectedLine = nullptr;

    float4 CameraPos = { 0,0 };
};


