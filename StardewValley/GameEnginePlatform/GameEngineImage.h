#pragma once
#include <Windows.h>
#include <string_view>
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>

// �̹�����
// => ��ǻ�Ϳ��� ���� �����̳� ũ�⸦ ������ �ִٸ�
// Ư�� ������� ������ �����ϰ� �ִ� bit�� �����ϼ� �ۿ� ����.
// �׷��� byte�� �����̶�� �Ҽ� �ִ�.
// ����.
// �̹����� �����ϼ��ۿ� ����

// ��� �̹����� 2������ ����ϸ� �˴ϴ�.
// 1. ���� �����ϳ��� �����Ʈ�� ��� ǥ���ߴ°�? ��� ������ RGBA�� ���ؼ� ǥ���մϴ�.
//    �� RGBA�� 1���� �����Ʈ�� �Ἥ ǥ���Ұųİ� �����Դϴ�.
//    Bitmap ������ RGBA�� ���� R�� 1����Ʈ�� ���ؼ� ǥ���մϴ�.
// 2. ������.
//    bitmap�� �������� �ʾ�.

// Bitmap�� ����ϸ� ���� 1062x1380 ¥�� int 2���� 
// int ArrBitMap[1380][1062]
// char Color[4]
// Color[0] == 255

// �̰� �����찡 �����ϱ� �����մϴ�.
// int ArrBitMap[1380][1062] <= �츮�� �̰� ���� ���ؿ�.
// �迭�� ���� ������ �Ҽ� �ִ� ������ �ִµ� �װ� HDC�̴�.
// HDC�� �׷��� ������ �迭�� ����Ǿ� �ְ�. �װ� �����Ҽ� �ְ� �����ִ� ����̴�.

struct ImageCutData
{
    float StartX = 0.0f;
    float StartY = 0.0f;
    float SizeX = 0.0f;
    float SizeY = 0.0f;

    float4 GetStartPos()
    {
        return { StartX, StartY };
    }

    float4 GetScale()
    {
        return { SizeX, SizeY };
    }
};

// ���� :
class GameEnginePath;
class GameEngineImage
{
public:
    // constrcuter destructer
    GameEngineImage();
    ~GameEngineImage();

    // delete Function
    GameEngineImage(const GameEngineImage& _Other) = delete;
    GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
    GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
    GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

    bool ImageCreate(HDC _Hdc);

    bool ImageCreate(const float4& _Scale);

    bool ImageLoad(const GameEnginePath& _Path);

    bool ImageLoad(const std::string_view& _Path);

    void ImageClear();

    HDC GetImageDC() const
    {
        return ImageDC;
    }

    float4 GetImageScale() const
    {
        return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
    }

    bool IsImageCutting()
    {
        return IsCut;
    }

    size_t GetImageCuttingCount()
    {
        return ImageCutDatas.size();
    }

    bool IsCutIndexValid(int _Index) const
    {
        if (0 > _Index)
        {
            return false;
        }

        if (ImageCutDatas.size() <= _Index)
        {
            return false;
        }

        return true;
    }

    ImageCutData GetCutData(int _Index) const
    {
        if (false == IsCutIndexValid(_Index))
        {
            MsgAssert("��ȿ���� ���� �� �ε��� �Դϴ�.");
        }

        return ImageCutDatas[_Index];
    }



    void Cut(float4 _Start, float4 _End, int _X, int _Y);

    void Cut(int _X, int _Y);

    // Copy

    void BitCopy(const GameEngineImage* _OtherImage, float4 _Pos, float4 _Scale);

    // �������� ������ �÷�.
    // �翬�� �����ϴ�.
    // ũ�������� ������ ������
    void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));

    // ����Ʈ ���ڴ� ���𿡼��� �����մϴ�.
    void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));

    void AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha);
    // ����Ʈ ���ڴ� ���𿡼��� �����մϴ�.
    void AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color);


    DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);

    DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

protected:

private:
    HDC ImageDC = nullptr;
    HBITMAP BitMap = nullptr;
    HBITMAP OldBitMap = nullptr;
    BITMAP Info = BITMAP();
    bool IsCut = false;

    std::vector<ImageCutData> ImageCutDatas;

    void ImageScaleCheck();

};

