#pragma once
#include "Player.h"
#include "Inventory.h"

#include <vector>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>

class Crops;
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
   
    static void DeathCrops(Crops* _Crop); 

    static Level_Farm* GetFarmManager()
    {
        return FarmManager;
    }

    void CreateCrops(std::string _CropName);
    
    void CreateItemToFarmInventory();

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:

    static Level_Farm* FarmManager;
    static std::vector<Crops*> CropList;    

    Inventory* FarmInventory = nullptr;
    Player* FarmPlayer = nullptr;
    
};

