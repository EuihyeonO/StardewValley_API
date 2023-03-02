#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button;
class GameEngineRender;
class GameEngineCollision;
class Marlon : public GameEngineActor
{

public:

    void isCollision();
    void TextBoxOn(float _DeltaTime);
    void TextBoxOff();
    void isInteract();

    bool static GetisCollided();

	Marlon();
	~Marlon();

	Marlon(const Marlon& _Other) = delete;
	Marlon(Marlon&& _Other) noexcept = delete;
	Marlon& operator=(const Marlon& _Other) = delete;
	Marlon& operator=(Marlon&& _Other) noexcept = delete;

    static Marlon* GlobalMarlon;
    static Marlon* GetGlobalMarlon()
    {
        return GlobalMarlon;
    }

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    GameEngineRender* MarlonRender = nullptr;
    GameEngineRender* MarlonText = nullptr;
    GameEngineRender* MarlonTextShadow = nullptr;

    GameEngineCollision* MarlonCollision = nullptr;

    float4 Scale = { 0,0 };

    int isInput = 0;

    bool isCollided = false;
    bool isKeyInteract = false;

    Button* OkayButton = nullptr;
    Button* NoButton = nullptr;

    bool isButtonOn = false;

};

