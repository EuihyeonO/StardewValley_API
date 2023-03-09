#pragma once
#include <GameEngineCore/GameEngineActor.h>

class House : public GameEngineActor
{

public:
    std::string isCollision_PortalToPlayer();

    void PortalFarmOn();
    void SetIsFading(int num);

    void FadeInAndOut(float _DeltaTime);
    void Sleep(float _DeltaTime);
    void DoSleep(float _DeltaTime);

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
    GameEngineRender* house = nullptr;
    GameEngineRender* houseLayer = nullptr;
    GameEngineRender* BlackMap = nullptr;

    GameEngineCollision* PortalToFarm = nullptr;
    GameEngineCollision* BedCollision = nullptr;

    bool isDebug = false;
    bool SoundOn = false;
    bool isSleep = false;

    float alpha = 0;
    int alphacount = 0;
    int isFading = 0;
};

