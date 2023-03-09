#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

class GameEngineRender;
class GameEngineCollision;
class Mummy : public GameEngineActor
{

public:
    static int GetMummyAttackPower()
    {
        return AttackPower;
    }

    GameEngineCollision* GetHalfCollision()
    {
        return HalfBodyCollision;
    }

    void RenderOrderUpdate();
    void hitByPlayer(float _DeltaTime);
    void MoveToPlayer(float _DeltaTime);
    void Dead();
    void SetDir(bool isCol = false);

	Mummy();
	~Mummy();

	Mummy(const Mummy& _Other) = delete;
	Mummy(Mummy&& _Other) noexcept = delete;
	Mummy& operator=(const Mummy& _Other) = delete;
	Mummy& operator=(Mummy&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    static int AttackPower;

    GameEngineRender* BodyRender = nullptr;
    GameEngineCollision* HalfBodyCollision = nullptr;
    GameEngineCollision* FullBodyCollision = nullptr;

    int HP = 4;
    int Accel = 15;

    bool isCol = false;
    bool isCol2 = false;
    bool isHit = false;
    bool DeadAnimationStart = false;
    bool isBirth = true;

    std::string Dir = "D";

    float4 DestiPos = { 0,0 };
    float4 DirVector = { 0,0 };
};

