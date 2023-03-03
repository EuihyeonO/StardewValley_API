#pragma once
#include "NpcCommonData.h"

class GameEngineRender;
class GameEngineCollision;
class Lewis : public NpcCommonData
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

};

