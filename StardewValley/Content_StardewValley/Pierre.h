#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>

class Button;
class GameEngineCollision;

struct shopItem
{
    std::string ShopItemName;
    GameEngineRender* ShopItemRender;
};

class Pierre : public GameEngineActor
{
public:
    
    void OpenPierreShop();
    void AddItemToShop(std::string _Name);
    void SortToShopItem();
    void AllShopItemOnOff();

    static std::string GetNameShopItem(Button* _button);

    static bool IsOpenShop()
    {
        return isOpenShop;
    }

    void ChangeSelectedItem();


	Pierre();
	~Pierre();

	Pierre(const Pierre& _Other) = delete;
	Pierre(Pierre&& _Other) noexcept = delete;
	Pierre& operator=(const Pierre& _Other) = delete;
	Pierre& operator=(Pierre&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;

private:
    static std::map<std::string, Button*> ShopItemList;
    static bool isOpenShop;

    GameEngineRender* PierreRender = nullptr;
    GameEngineCollision* PierreCollision = nullptr;

    GameEngineRender* ShopRender = nullptr;


    Button* SelectedItem = nullptr;

    GameEngineRender* SelectedLine = nullptr;

    float4 ShopTopPos = { 119, -271 };
};

