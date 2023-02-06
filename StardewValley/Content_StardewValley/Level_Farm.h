#pragma once
#include <vector>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineActor.h>

#include "Crops.h"



class Level_Farm : public GameEngineLevel
{

public:


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
    std::vector<Crops*> CropList;
};

