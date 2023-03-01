#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;
class Lewis : public GameEngineActor
{

public:

	Lewis();
	~Lewis();

	Lewis(const Lewis& _Other) = delete;
	Lewis(Lewis&& _Other) noexcept = delete;
	Lewis& operator=(const Lewis& _Other) = delete;
	Lewis& operator=(Lewis&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* LewisRender = nullptr;
};

