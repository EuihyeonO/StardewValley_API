#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_Village : public GameEngineLevel
{

public:

	Level_Village();
	~Level_Village();

	Level_Village(const Level_Village& _Other) = delete;
	Level_Village(Level_Village&& _Other) noexcept = delete;
	Level_Village& operator=(const Level_Village& _Other) = delete;
	Level_Village& operator=(Level_Village&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update(float _DeltaTime) override;
    void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
    void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:

};

