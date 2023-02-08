#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <map>
#include "GameEngineComponent.h"
// 랜더링에 관련된 기능을 모두 집약한다.

class FrameAnimationParameter
{
public:
    std::string_view AnimationName = "";
    std::string_view ImageName = "";
    int Start = 0;
    int End = 0;
    int CurrentIndex = 0;
    float InterTime = 0.1f;
    bool Loop = true;
    std::vector<int> FrameIndex = std::vector<int>();
    std::vector<float> FrameTime = std::vector<float>();
};


// 설명 :
class GameEngineActor;
class GameEngineLevel;
class GameEngineRender : public GameEngineComponent
{
    friend GameEngineActor;
    friend GameEngineLevel;

public:
    // constrcuter destructer
    GameEngineRender();
    ~GameEngineRender();

    // delete Function
    GameEngineRender(const GameEngineRender& _Other) = delete;
    GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
    GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
    GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

    void SetImage(const std::string_view& _ImageName);

    void SetScaleToImage();

    void SetFrame(int _Frame);

    inline GameEngineImage* GetImage()
    {
        return Image;
    }

    inline int GetFrame()
    {
        return Frame;
    }

    void SetTransColor(int _Color)
    {
        TransColor = _Color;
    }

    inline void EffectCameraOff()
    {
        IsEffectCamera = false;
    }

    bool IsAnimationEnd();
    void CreateAnimation(const FrameAnimationParameter& _Paramter);
    void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);

    void SetOrder(int _Order) override;

    void SetText(const std::string_view& _Text);

protected:

private:
    GameEngineImage* Image = nullptr;
    bool IsEffectCamera = true;

    int TransColor = RGB(255, 0, 255);

    int Frame = 0;

    void Render(float _DeltaTime);

    void TextRender(float _DeltaTime);
    void ImageRender(float _DeltaTime);

    class FrameAnimation
    {
    public:
        GameEngineRender* Parent = nullptr;
        // 짤려있는 이미지여야 한다.
        GameEngineImage* Image = nullptr;
        std::vector<int> FrameIndex;
        std::vector<float> FrameTime;
        int CurrentIndex = 0;
        float CurrentTime = 0.0f;
        bool Loop = true;


        bool IsEnd();

        void Render(float _DeltaTime);

        void Reset()
        {
            CurrentIndex = 0;
            CurrentTime = 0.0f;
        }
    };

    std::map<std::string, FrameAnimation> Animation;
    FrameAnimation* CurrentAnimation = nullptr;

    /// <summary>
    /// TextRender
    /// </summary>
    std::string RenderText;
    // 그런걸 하면 HBRUSH 만드는데 사용하고 나면 Release
    // GameEngineImage를 참조해라.
};

