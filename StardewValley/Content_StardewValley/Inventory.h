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

     static void InsertItem(Item* _item)
    {
        GlobalInventory->ItemList.push_back(_item);
    }

    static size_t GetNumOfItem()
    {
        return GlobalInventory->ItemList.size();
    }

    static Item* GetLastItem();

    void AllItemOn();
    void AllItemOff();

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
    GameEngineRender* InventoryRender = nullptr;
    std::vector<Item*> ItemList;
};

