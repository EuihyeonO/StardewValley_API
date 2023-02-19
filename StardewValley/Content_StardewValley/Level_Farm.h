#pragma once
#include "Player.h"
#include "Inventory.h"

#include <vector>
#include <map>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>

class UI;
class Crops;
class GameEngineTileMap;
class Level_Farm : public GameEngineLevel
{

public:


	Level_Farm();
	~Level_Farm();

	Level_Farm(const Level_Farm& _Other) = delete;
	Level_Farm(Level_Farm&& _Other) noexcept = delete;
	Level_Farm& operator=(const Level_Farm& _Other) = delete;
	Level_Farm& operator=(Level_Farm&& _Other) noexcept = delete;

    static std::vector<Crops*> GetCropList()
    {
        return CropList;
    }

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

    static void DeathCrops(Crops* _Crop); 

    void CreateCrops(std::string _CropName);    
    void InitTile();
    static int CheckUpdateTile(float4 _pos);
    static int GetLastIndexCrops(int _SeedType);
    static bool IsMaxGrow(float4 _pos, int _SeedType);
    static bool isCollisionMouseToTile();
    static Inventory* FarmInventory;
    static UI* FarmUI;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

    static std::vector<Crops*> CropList;   

    static GameEngineTileMap* TileMap;
    Player* FarmPlayer = nullptr;
    
};

