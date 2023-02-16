#pragma once
#include <GameEngineCore/GameEngineActor.h>

class House : public GameEngineActor
{

public:
    std::string isCollision_PortalToPlayer();
	House();
	~House();

	House(const House& _Other) = delete;
	House(House&& _Other) noexcept = delete;
	House& operator=(const House& _Other) = delete;
	House& operator=(House&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    GameEngineCollision* PortalToFarm = nullptr;
    bool isDebug = false;
};

