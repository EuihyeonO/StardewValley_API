#pragma once
#include "NpcCommonData.h"

class GameEngineRender;
class GameEngineCollision;
class Haley : public NpcCommonData
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
    
};

