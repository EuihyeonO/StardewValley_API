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

void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor)
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
}

void NumberRenderObject::SetValue(int _Value)
{
    Value = _Value;

    std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);
    GameEngineActor* Actor = GetOwner<GameEngineActor>();

    if (nullptr == Actor)
    {
        MsgAssert("액터만이 NumberRenderObject의 부모가 될수 있습니다.");
    }

    //            자리수가 바뀌었고                  3자리 랜더하고 있었는데 5자리가 됐다면
    if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
    {
        size_t CurRenderSize = NumberRenders.size();
        //                       5                   3
        for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
        {
            NumberRenders.push_back(Actor->CreateRender(Order));
        }
    }
    // Pos

    float4 RenderPos;

    for (size_t i = 0; i < NumberRenders.size(); i++)
    {
        GameEngineRender* Render = NumberRenders[i];

        if (nullptr == Render)
        {
            MsgAssert("숫자랜더러가 nullptr 입니다");
        }

        Render->SetTransColor(TransColor);
        Render->SetPosition(Pos + RenderPos);
        Render->SetImage(ImageName);
        Render->SetScale(NumberScale);
        Render->SetFrame(Numbers[i]);

        RenderPos.x += NumberScale.x;
    }

    switch (AlignState)
    {
    case Align::Left:
        break;
    case Align::Right:
        SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
        break;
    case Align::Center:
        SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
        break;
    default:
        break;
    }
}

void NumberRenderObject::SetMove(float4 _RenderPos)
{
    for (size_t i = 0; i < NumberRenders.size(); i++)
    {
        NumberRenders[i]->SetMove(_RenderPos);
    }
}

void NumberRenderObject::SetAlign(int _Align)
{
    AlignState = static_cast<Align>(_Align);
}

void NumberRenderObject::SetAlign(Align _Align)
{
    AlignState = _Align;
}


