#pragma once
#include "Player.h"
#include "Inventory.h"

#include <vector>
#include <map>
#include <list>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>

class Tree;
class AffectionBox;
class MenuButton;
class Farm;
class UI;
class GameEngineTileMap;
class Level_Farm : public GameEngineLevel
{

public:

    void ImageRoad();
    void CropImageRoad();
    void ToolImageRoad();
    void UIImageRoad();

    static void SetSeedPos(float4 _pos, int _SeedType);

    static GameEngineTileMap* GetTileMap()
    {
        return TileMap;
    }

    static UI* getFarmUI()
    {
        return FarmUI;
    }

    Inventory* GetFarmInventory()
    {
        return FarmInventory;
    }


    void ValidCollisionTileOn();
    void isCollisionToPlayer();
    void CreateCrops(std::string _CropName);    
    void InitTile();

    static int CheckUpdateTile(float4 _pos);
    static int GetLastIndexCrops(int _SeedType);
    static bool IsMaxGrow(float4 _pos, int _SeedType);

    static void Grow_Up();
    static void DeleteTileToList(int _SeedName, float4 _pos);

    static void PlusOnTileToList(GameEngineRender* _Render)
    {
        OnTileList.push_back(_Render);
    }

    static Inventory* FarmInventory;
    static UI* FarmUI;

	Level_Farm();
	~Level_Farm();

	Level_Farm(const Level_Farm& _Other) = delete;
	Level_Farm(Level_Farm&& _Other) noexcept = delete;
	Level_Farm& operator=(const Level_Farm& _Other) = delete;
	Level_Farm& operator=(Level_Farm&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

    static GameEngineTileMap* TileMap;
    static std::vector<GameEngineRender*> OnTileList;

    MenuButton* FarmMenuButton = nullptr;
    AffectionBox* FarmAffectionBox = nullptr;
    
    std::vector<Tree*> TreeList;

    float myDeltaTime = 0;

    Player* FarmPlayer = nullptr;
    Farm* FarmController = nullptr;

    std::vector<GameEngineCollision*> CollidedTile;
   
};

