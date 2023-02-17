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

    // ������ ���� 0.bmp 1.bmp
    if (FindNumberImage->GetImageCuttingCount() != 10)
    {
        MsgAssert("���� �̹����� ������ 10���� ©���־�� �մϴ�.");
    }

    if (0 >= _Scale.x || 0 >= _Scale.y)
    {
        MsgAssert("ũ�Ⱑ 0���� ���ڸ� ����� �� �����ϴ�.");
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
        MsgAssert("���ڷ������� nullptr �Դϴ�");
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
        MsgAssert("���͸��� NumberRenderObject�� �θ� �ɼ� �ֽ��ϴ�.");
    }

    if (-1 != NumOfDigits && Numbers.size() > NumOfDigits) // ���ڱ��� ������ && Value���� > ���� ����
    {
        MsgAssert("Digits ���� ���� value�� ���� �۽��ϴ�.");
    }

    // -���� ���� + digits���� �����Ѱ��
    // 1. digits���̸� value���̷� �ٲ۴�.(����)
    // 2. MsgAssert
    if (-1 != NumOfDigits && Value < 0) //
    {
        ResetDigits(); // �����鼭 digits���̸� ������ ��� 
        MsgAssert("Value�� ������ ���ÿ� Digits���̰� �����Ǿ����ϴ�.");
    }


    Negative = _Value >= 0 ? false : true;

    // ���� ���� ���� ����x - Numbers.size(), ����o - NumOfDigits
    size_t Digits = (NumOfDigits == -1 ? Numbers.size() : NumOfDigits) + (Negative ? 1 : 0);

    // -- [���� ��] : NumOfDigits �߰� ����
    ////            �ڸ����� �ٲ����                  3�ڸ� �����ϰ� �־��µ� 5�ڸ��� �ƴٸ�
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

    if (NumberRenders.size() < Digits) // NumberRenders�� �߰��ؾ� �ϴ� ���
    {
        size_t CurRenderSize = NumberRenders.size();
        //                       5                   3
        for (size_t i = 0; i < (Digits - CurRenderSize); ++i)
        {
            NumberRenders.push_back(Actor->CreateRender(Order));
        }
    }
    else // NumberRenders�� ���� �ؾ��ϴ� ���  +)�����Ǵ� ���
    {
        size_t CurRenderSize = NumberRenders.size();
        //                       5                   3
        for (size_t i = 0; i < (CurRenderSize - Digits); ++i)
        {
            GameEngineRender* LastRender = NumberRenders.back();
            NumberRenders.pop_back(); // �����Ǵ��� üũ �ʿ�
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

    //--[���� ��] : NumOfDigits �߰� ����
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

    // -- [���� ��] : NumOfDigits �߰� ����
    //for (size_t i = 0; i < NumberRenders.size(); i++)
    //{
    //	GameEngineRender* Render = NumberRenders[i];

    //	if (nullptr == Render)
    //	{
    //		MsgAssert("���ڷ������� nullptr �Դϴ�");
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


