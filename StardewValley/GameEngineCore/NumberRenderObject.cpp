#include "NumberRenderObject.h"
#include "GameEngineResources.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineString.h>

NumberRenderObject::NumberRenderObject()
{
}

NumberRenderObject::~NumberRenderObject()
{
}



void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
    GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

    // 선생님 저는 0.bmp 1.bmp
    if (FindNumberImage->GetImageCuttingCount() != 10)
    {
        MsgAssert("숫자 이미지는 무조건 10개로 짤려있어야 합니다.");
    }

    if (0 >= _Scale.x || 0 >= _Scale.y)
    {
        MsgAssert("크기가 0으로 숫자를 출력할 수 없습니다.");
    }

    ImageName = _ImageName;
    NumberScale = _Scale;
    Order = _Order;
    TransColor = _TransColor;
    NegativeName = _NegativeName;
}

void NumberRenderObject::SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame)
{
    GameEngineRender* Render = NumberRenders[_Index];
    if (nullptr == Render)
    {
        MsgAssert("숫자랜더러가 nullptr 입니다");
    }
    Render->SetTransColor(_TransColor);
    Render->SetPosition(_Pos);
    Render->SetImage(_ImageName);
    Render->SetScale(_Scale);
    Render->SetEffectCamera(_CameraEffect);
    if (-1 != _Frame)
    {
        Render->SetFrame(_Frame);
    }
}

void NumberRenderObject::On()
{
    GameEngineObject::On();
    for (size_t i = 0; i < NumberRenders.size(); i++)
    {
        NumberRenders[i]->On();
    }
}

void NumberRenderObject::Off()
{
    GameEngineObject::Off();
    for (size_t i = 0; i < NumberRenders.size(); i++)
    {
        NumberRenders[i]->Off();
    }
}

void NumberRenderObject::SetValue(int _Value)
{
    GameEngineActor* Actor = GetOwner<GameEngineActor>();
    Value = _Value;

    std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);

    if (nullptr == Actor)
    {
        MsgAssert("액터만이 NumberRenderObject의 부모가 될수 있습니다.");
    }

    if (-1 != NumOfDigits && Numbers.size() > NumOfDigits) // 숫자길이 설정함 && Value길이 > 설정 길이
    {
        MsgAssert("Digits 설정 값이 value값 보다 작습니다.");
    }

    // -선택 음수 + digits길이 설정한경우
    // 1. digits길이를 value길이로 바꾼다.(리셋)
    // 2. MsgAssert
    if (-1 != NumOfDigits && Value < 0) //
    {
        ResetDigits(); // 음수면서 digits길이를 설정한 경우 
        MsgAssert("Value가 음수인 동시에 Digits길이가 설정되었습니다.");
    }


    Negative = _Value >= 0 ? false : true;

    // 최종 랜더 길이 설정x - Numbers.size(), 설정o - NumOfDigits
    size_t Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits) + (Negative ? 1 : 0);

    // -- [수정 전] : NumOfDigits 추가 이전
    ////            자리수가 바뀌었고                  3자리 랜더하고 있었는데 5자리가 됐다면
    //if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
    //{
    //	size_t CurRenderSize = NumberRenders.size();
    //	//                       5                   3
    //	for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
    //	{
    //		NumberRenders.push_back(Actor->CreateRender(Order));
    //	}
    //}
    // --

    if (NumberRenders.size() < Digits) // NumberRenders를 추가해야 하는 경우
    {
        size_t CurRenderSize = NumberRenders.size();
        //                       5                   3
        for (size_t i = 0; i < (Digits - CurRenderSize); ++i)
        {
            NumberRenders.push_back(Actor->CreateRender(Order));
        }
    }
    else // NumberRenders를 삭제 해야하는 경우  +)유지되는 경우
    {
        size_t CurRenderSize = NumberRenders.size();
        //                       5                   3
        for (size_t i = 0; i < (CurRenderSize - Digits); ++i)
        {
            GameEngineRender* LastRender = NumberRenders.back();
            NumberRenders.pop_back(); // 삭제되는지 체크 필요
            LastRender->Death();
        }
    }


    // Pos

    float4 RenderPos = Pos;
    size_t NumRenderIndex = 0;

    switch (AlignState)
    {
    case Align::Left:
        break;
    case Align::Right:
        RenderPos.x -= (Digits - 1) * NumberScale.x;
        break;
    case Align::Center:
        RenderPos.x -= ((Digits - 1) * NumberScale.x) / 2;
        break;
    default:
        break;
    }

    //--[수정 전] : NumOfDigits 추가 이전
    //Negative = _Value >= 0 ? false : true;

    /*if (true == Negative && nullptr == NegativeRender)
    {
        NegativeRender = Actor->CreateRender(Order);
        NegativeRender->SetTransColor(TransColor);
        NegativeRender->SetPosition(Pos + RenderPos);
        NegativeRender->SetImage(NegativeName);
        NegativeRender->SetScale(NumberScale);
        RenderPos.x += NumberScale.x;
    }

    if (nullptr != NegativeRender)
    {
        NegativeRender->SetPosition(Pos + RenderPos);
        RenderPos.x += NumberScale.x;
    }*/
    //--
    if (true == Negative && nullptr == NegativeRender)
    {
        SetNumberRenders(NumRenderIndex++, TransColor, RenderPos, NegativeName, NumberScale, CameraEffect);
        RenderPos.x += NumberScale.x;
    }
    for (; NumRenderIndex < Digits - Numbers.size(); ++NumRenderIndex)
    {
        SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, 0);
        RenderPos.x += NumberScale.x;
    }
    for (int i = 0; NumRenderIndex < NumberRenders.size(); ++NumRenderIndex)
    {
        SetNumberRenders(NumRenderIndex, TransColor, RenderPos, ImageName, NumberScale, CameraEffect, Numbers[i++]);
        RenderPos.x += NumberScale.x;
    }

    // -- [수정 전] : NumOfDigits 추가 이전
    //for (size_t i = 0; i < NumberRenders.size(); i++)
    //{
    //	GameEngineRender* Render = NumberRenders[i];

    //	if (nullptr == Render)
    //	{
    //		MsgAssert("숫자랜더러가 nullptr 입니다");
    //	}

    //	Render->SetTransColor(TransColor);
    //	Render->SetPosition(Pos + RenderPos);
    //	Render->SetImage(ImageName);
    //	Render->SetScale(NumberScale);
    //	Render->SetFrame(Numbers[i]);

    //	RenderPos.x += NumberScale.x;
    //}
    // --

    //switch (AlignState)
    //{
    //case Align::Left:
    //	break;
    //case Align::Right:
    //	SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
    //	if (nullptr != NegativeRender)
    //	{
    //		NegativeRender->SetPosition(Pos + float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
    //	}
    //	break;
    //case Align::Center:
    //	SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
    //	if (nullptr != NegativeRender)
    //	{
    //		NegativeRender->SetPosition(Pos + (float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
    //	}
    //	break;
    //default:
    //	break;
    //}

    //for (size_t i = 0; i < NumberRenders.size(); i++)
    //{
    //	//CameraEffect
    //	NumberRenders[i]->SetEffectCamera(CameraEffect);
    //}
    // --

}

void NumberRenderObject::SetMove(float4 _RenderPos)
{
    for (size_t i = 0; i < NumberRenders.size(); i++)
    {
        NumberRenders[i]->SetMove(_RenderPos);
    }
}

void NumberRenderObject::SetAlign(Align _Align)
{
    AlignState = _Align;
}

void NumberRenderObject::SetRenderPos(float4 _Pos)
{
    Pos = _Pos;
    SetValue(Value);
    /*switch (AlignState)
    {
    case Align::Left:
        for (size_t i = 0; i < NumberRenders.size(); i++)
        {
            NumberRenders[i]->SetPosition(_Pos + float4::Right * NumberRenders[i]->GetScale() * static_cast<const float>(i));
        }

        if (nullptr != NegativeRender)
        {
            NegativeRender->SetPosition(_Pos + float4::Left * NumberScale.x);
        }
        break;
    case Align::Right:
        for (size_t i = 0; i < NumberRenders.size(); i++)
        {
            NumberRenders[i]->SetPosition(_Pos + float4::Left * NumberRenders[i]->GetScale() * (static_cast<const float>(NumberRenders.size()) - (static_cast<const float>(i) + 1)));
        }

        if (nullptr != NegativeRender)
        {
            NegativeRender->SetPosition(_Pos + float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
        }
        break;
    case Align::Center:
        for (size_t i = 0; i < NumberRenders.size(); i++)
        {
            NumberRenders[i]->SetPosition(_Pos + (float4::Left * NumberRenders[i]->GetScale().half() * (static_cast<const float>(NumberRenders.size()) - 1)) + (float4::Right * NumberRenders[i]->GetScale() * static_cast<const float>(i)));
        }

        if (nullptr != NegativeRender)
        {
            NegativeRender->SetPosition(_Pos + (float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
        }
        break;
    default:
        break;
    }*/
}


