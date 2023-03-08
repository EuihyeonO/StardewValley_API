#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string_view>

class GameEngineRender;
class GameEngineCollision;

class NpcCommonData : public GameEngineActor
{

public:
    void SetBodyRender(const std::string_view& _ImageName, float4 _pos);
    void SetTextRender(float4 _pos = { 640, 568 });
    
    void SetName(const std::string& _NpcName)
    {
        NpcName = _NpcName;
    }

    void SetCollision();

    void TextBoxOn(float _DeltaTime, const std::string& CommonText, const std::string& HappyText, const std::string& AngryText);
    void TextBoxOff();
    void TextOn(const std::string& _Text);
    void TextOff();
    void TextBoxOnOff(float _DeltaTime, const std::string& CommonText, const std::string& HappyText, const std::string& AngryText);

    void InteractUpdate();
    void RenderOrderUpdate();

    bool IsTextUpdate();

	NpcCommonData();
	~NpcCommonData();

	NpcCommonData(const NpcCommonData& _Other) = delete;
	NpcCommonData(NpcCommonData&& _Other) noexcept = delete;
	NpcCommonData& operator=(const NpcCommonData& _Other) = delete;
	NpcCommonData& operator=(NpcCommonData&& _Other) noexcept = delete;

    GameEngineRender* TextBox_Common = nullptr;
    GameEngineRender* TextBox_Happy = nullptr;
    GameEngineRender* TextBox_Angry = nullptr;

    GameEngineRender* TextBoxShadow = nullptr;

    GameEngineRender* BodyRender = nullptr;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* OrderCollision = nullptr;

    GameEngineRender* Text = nullptr;

protected:

private:
    float4 Scale = { 0,0 };

    std::string Talk = "";
    std::string CopyText = "";

    float Prevtime = 0;
    float Curtime = 0;
    float Counttime = 0;
    float CountSoundtime = 0;

    int StringIndex = 0;

    bool isKeyInteract = false;
    bool isSetText = false;

    std::string CopyOutPutText;
    GameEngineRender* CopyOutPutTextBox = nullptr;

    bool isInputText = false;

    std::string NpcName;
};

