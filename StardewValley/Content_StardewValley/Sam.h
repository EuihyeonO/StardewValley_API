#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class Sam : public GameEngineActor
{

public:

	Sam();
	~Sam();

	Sam(const Sam& _Other) = delete;
	Sam(Sam&& _Other) noexcept = delete;
	Sam& operator=(const Sam& _Other) = delete;
	Sam& operator=(Sam&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* SamRender = nullptr;
};

