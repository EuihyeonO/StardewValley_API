#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class Haley : public GameEngineActor
{

public:

	Haley();
	~Haley();

	Haley(const Haley& _Other) = delete;
	Haley(Haley&& _Other) noexcept = delete;
	Haley& operator=(const Haley& _Other) = delete;
	Haley& operator=(Haley&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* HaleyRender = nullptr;
};

