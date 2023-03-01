#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class Penny : public GameEngineActor
{

public:

	Penny();
	~Penny();

	Penny(const Penny& _Other) = delete;
	Penny(Penny&& _Other) noexcept = delete;
	Penny& operator=(const Penny& _Other) = delete;
	Penny& operator=(Penny&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* PennyRender = nullptr;
};

