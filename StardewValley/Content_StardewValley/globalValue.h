#pragma once
#include <GameEngineBase/GameEngineMath.h>


class globalValue
{

public:

    static float4 GetcameraLimitPos()
    {
        return cameraLimitPos;
    }

    static void SetcameraLimitPos(float4 _pos)
    {
        cameraLimitPos = _pos;
    }

    globalValue();
	~globalValue();

    globalValue(const globalValue& _Other) = delete;
    globalValue(globalValue&& _Other) noexcept = delete;
    globalValue& operator=(const globalValue& _Other) = delete;
    globalValue& operator=(globalValue&& _Other) noexcept = delete;

protected:

private:
  static float4 cameraLimitPos;
};
