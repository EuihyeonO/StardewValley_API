#pragma once
#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

enum class Align
{
    Left,
    Right,
    Center
};

// 설명 : Image로 숫자출력을 해주는 클래스
//        세팅되는 이미지는 무조건 10개로 컷팅되어있어야 한다.
// 넣어줘야할건 무조건 Actor계열이여야 합니다.
class GameEngineActor;
class NumberRenderObject : public GameEngineObject
{
public:
    // constrcuter destructer
    NumberRenderObject();
    ~NumberRenderObject();

    // delete Function
    NumberRenderObject(const NumberRenderObject& _Other) = delete;
    NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
    NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
    NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

    // 
    void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");
    void SetValue(int _Value);

    void SetMove(float4 _RenderPos);
    void SetAlign(Align _Align);

    void SetCameraEffect(bool _EffectSetting)
    {
        CameraEffect = _EffectSetting;
    }

    void On() override;
    void Off() override;

    void SetRenderPos(float4 _Pos);


    inline int GetValue()
    {
        return Value;
    }

    inline void SetNumOfDigits(int _Num) { // 랜더 할 숫자 길이 설정
        NumOfDigits = _Num;
    }

    inline void ResetDigits() { // 숫자길이 리셋 (Value만큼 랜더)
        SetNumOfDigits(-1);
    }

protected:

private:
    int Order = 0;
    float4 NumberScale = {};
    float4 Pos = {};
    int Value = 0;
    int TransColor = RGB(255, 0, 255);
    Align AlignState = Align::Left;
    bool Negative = false;

    int NumOfDigits = -1; // 렌더할 숫자 길이
    // GameEngineImage* NumberImage;

    bool CameraEffect = false;

    std::string_view ImageName = std::string_view();

    std::string_view NegativeName = std::string_view();

    std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();
    GameEngineRender* NegativeRender = nullptr;

    void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);
};

