#pragma once
#include <GameEngineCore/GameEngineActor.h>


class Farm : public GameEngineActor
{

public:

	Farm();
	~Farm();

	Farm(const Farm& _Other) = delete;
	Farm(Farm&& _Other) noexcept = delete;
	Farm& operator=(const Farm& _Other) = delete;
	Farm& operator=(Farm&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineCollision* PortalToVillage;

    bool isDebug = false;
};

