#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Road : public GameEngineActor
{

public:

	Road();
	~Road();
    std::string isCollision_PortalToPlayer();

	Road(const Road& _Other) = delete;
	Road(Road&& _Other) noexcept = delete;
	Road& operator=(const Road& _Other) = delete;
	Road& operator=(Road&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    GameEngineCollision* PortalToFarm = nullptr;
    bool isDebug = false;
};

