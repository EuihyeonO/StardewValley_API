#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <string>

class GameEngineRender;
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

    GameEngineRender* PierreRender = nullptr;
    GameEngineCollision* PierreCollision = nullptr;

    GameEngineRender* ShopRender = nullptr;

    std::map<std::string, GameEngineRender*> ShopItemList;

    GameEngineRender* SelectedItem = nullptr;
    GameEngineRender* SelectedLine = nullptr;
};
