#pragma once
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
    void CreateCrops(std::string _CropName);

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
    static std::vector<Crops*> CropList;
};

