#pragma once
#include "NpcCommonData.h"

class GameEngineRender;
class GameEngineCollision;
class Penny : public NpcCommonData
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
};

