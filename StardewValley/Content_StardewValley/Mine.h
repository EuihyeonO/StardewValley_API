#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
class Mine : public GameEngineActor
{

public:

    std::string isCollision_PortalToPlayer();
    void FadeInAndOut(float _DeltaTime);
    void PortalFarmOn();
    void SetIsFading(int num);

	Mine();
	~Mine();

	Mine(const Mine& _Other) = delete;
	Mine(Mine&& _Other) noexcept = delete;
	Mine& operator=(const Mine& _Other) = delete;
	Mine& operator=(Mine&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    bool isDebug = false;
    GameEngineCollision* PortalToFarm = nullptr;
    GameEngineRender* BlackMap = nullptr;
    int isFading = 0;

    float alpha = 0;
};

