#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineString.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
    Image = GameEngineResources::GetInst().ImageFind(_ImageName);
    // SetScaleToImage();
}

void GameEngineRender::SetImageToScaleToImage(const std::string_view& _ImageName)
{
    Image = GameEngineResources::GetInst().ImageFind(_ImageName);
    SetScaleToImage();
}

void GameEngineRender::SetScaleToImage()
{
    if (nullptr == Image)
    {
        MsgAssert("이미지를 세팅하지 않았는데 이미지의 크기로 변경하려고 했습니다.");
    }

    SetScale(Image->GetImageScale());
}

void GameEngineRender::SetOrder(int _Order)
{
    GetActor()->GetLevel()->PushRender(this, _Order);
}

void GameEngineRender::SetFrame(int _Frame)
{
    if (nullptr == Image)
    {
        MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
    }

    if (false == Image->IsImageCutting())
    {
        MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
    }

    if (false == Image->IsCutIndexValid(_Frame))
    {
        MsgAssert("유요하지 않은 이미지인덱스 입니다.");
    }

    Frame = _Frame;
}

bool GameEngineRender::FrameAnimation::IsEnd()
{
    int Value = (static_cast<int>(FrameIndex.size()) - 1);
    return CurrentIndex == Value;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
    CurrentTime -= _DeltaTime;

    if (CurrentTime <= 0.0f)
    {
        ++CurrentIndex;

        if (FrameIndex.size() <= CurrentIndex)
        {
            if (true == Loop)
            {
                CurrentIndex = 0;
            }
            else {
                CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
            }
        }

        // 정밀하게 하려면 이게 맞죠?
        CurrentTime += FrameTime[CurrentIndex];
    }
}

void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor)
{
    RenderText = _Text;
    TextHeight = _TextHeight;
    TextType = _TextType;
    Align = _TextAlign;
    TextColor = _TextColor;
}

void GameEngineRender::Render(float _DeltaTime)
{
    if (RenderText != "")
    {
        TextRender(_DeltaTime);
    }
    else
    {
        ImageRender(_DeltaTime);
    }
}

void GameEngineRender::TextRender(float _DeltaTime)
{

    float4 CameraPos = float4::Zero;

    if (true == IsEffectCamera)
    {
        CameraPos = GetActor()->GetLevel()->GetCameraPos();
    }

    float4 RenderPos = GetActorPlusPos() - CameraPos;

    HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
    HFONT hFont, OldFont;
    LOGFONTA lf;
    lf.lfHeight = TextHeight;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 0;
    lf.lfItalic = 0;
    lf.lfUnderline = 0;
    lf.lfStrikeOut = 0;
    lf.lfCharSet = HANGEUL_CHARSET;
    lf.lfOutPrecision = 0;
    lf.lfClipPrecision = 0;
    lf.lfQuality = 0;
    lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
    lstrcpy(lf.lfFaceName, TEXT(TextType.c_str()));
    hFont = CreateFontIndirect(&lf);
    OldFont = static_cast<HFONT>(SelectObject(hdc, hFont));

    SetTextAlign(hdc, static_cast<UINT>(Align));
    SetTextColor(hdc, TextColor);
    SetBkMode(hdc, TRANSPARENT);

    TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

    SelectObject(hdc, OldFont);
    DeleteObject(hFont);

    return;
}

void GameEngineRender::ImageRender(float _DeltaTime)
{
    if (nullptr != CurrentAnimation)
    {
        CurrentAnimation->Render(_DeltaTime);
        Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
        Image = CurrentAnimation->Image;
    }

    if (nullptr == Image)
    {
        MsgAssert("이미지를 세팅해주지 않았습니다.");
    }

    float4 CameraPos = float4::Zero;

    if (true == IsEffectCamera)
    {
        CameraPos = GetActor()->GetLevel()->GetCameraPos();
    }

    float4 RenderPos = GetActorPlusPos() - CameraPos;

    if (true == Image->IsImageCutting())
    {
        if (255 == Alpha)
        {
            GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
        }
        else if (255 > Alpha)
        {
            GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), Alpha);
        }
    }
    else
    {
        if (255 == Alpha)
        {
            GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
        }
        else if (255 > Alpha)
        {
            GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), Alpha);
        }
    }
}

bool GameEngineRender::IsAnimationEnd()
{
    return CurrentAnimation->IsEnd();
}

void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
    // 애니메이션을 만들기 위해서 이미지를 검증한다.
    GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

    if (nullptr == Image)
    {
        MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
    }

    if (false == Image->IsImageCutting())
    {
        MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
    }

    std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

    if (Animation.end() != Animation.find(UpperName))
    {
        MsgAssert("이미 존재하는 이름의 애니메이션 입니다." + UpperName);
    }


    FrameAnimation& NewAnimation = Animation[UpperName];

    NewAnimation.Image = Image;

    if (0 != _Paramter.FrameIndex.size())
    {
        NewAnimation.FrameIndex = _Paramter.FrameIndex;
    }
    else
    {
        for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
        {
            NewAnimation.FrameIndex.push_back(i);
        }
    }

    // 각 프레임별 시간을 계산한다.
    if (0 != _Paramter.FrameTime.size())
    {
        NewAnimation.FrameTime = _Paramter.FrameTime;
    }
    else
    {
        for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
        {
            NewAnimation.FrameTime.push_back(_Paramter.InterTime);
        }
    }

    NewAnimation.Loop = _Paramter.Loop;
    NewAnimation.Parent = this;
}

void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange /*= false*/)
{
    // 이미 같은 애니메이션으로 바꾸라고 리턴할껍니다.

    std::string UpperName = GameEngineString::ToUpper(_AnimationName);

    if (Animation.end() == Animation.find(UpperName))
    {
        MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
    }

    // 강제로 바꾸지 않는 상황에서 애니메이션이 같으면
    if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
    {
        return;
    }

    CurrentAnimation = &Animation[UpperName];

    CurrentAnimation->CurrentIndex = 0;
    // 0.1
    CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}