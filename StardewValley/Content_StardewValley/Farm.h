#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <String>

class Farm : public GameEngineActor
{

public:

    void FadeInAndOut(float _DeltaTime);
    void PortalMineOn();
    void SetIsFading(int _num);
	Farm();
	~Farm();

    std::string isCollision_PortalToPlayer();

	Farm(const Farm& _Other) = delete;
	Farm(Farm&& _Other) noexcept = delete;
	Farm& operator=(const Farm& _Other) = delete;
	Farm& operator=(Farm&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:

    GameEngineCollision* PortalToVillage = nullptr;
    GameEngineCollision* PortalToHouse = nullptr;  
    GameEngineCollision* PortalToMine = nullptr;  

    GameEngineRender* BlackMap = nullptr;

    bool isDebug = false;
    float alpha = 0;
    int isFading = 0;

    bool isMapChanging = false;

    std::string NextMap;
};

