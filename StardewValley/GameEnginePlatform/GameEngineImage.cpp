#include "GameEngineImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

// �ٸ� lib�� ����ϰڴ�.
#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
{
}

GameEngineImage::~GameEngineImage()
{
    if (nullptr != BitMap)
    {
        DeleteObject(BitMap);
        BitMap = nullptr;
    }

    if (nullptr != OldBitMap)
    {
        DeleteObject(OldBitMap);
        OldBitMap = nullptr;
    }

    if (nullptr != ImageDC)
    {
        DeleteDC(ImageDC);
        ImageDC = nullptr;
    }
}

bool GameEngineImage::ImageCreate(HDC _Hdc)
{
    if (nullptr == _Hdc)
    {
        MsgAssert("�̹��� ������ �����߽��ϴ� nullptr �� HDC�� �־�����ϴ�.");
        return false;
    }

    ImageDC = _Hdc;
    ImageScaleCheck();
    return true;
}

void GameEngineImage::ImageClear()
{
    Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

bool GameEngineImage::ImageCreate(const float4& _Scale)
{
    if (true == _Scale.IsZero())
    {
        MsgAssert("ũ�Ⱑ 0�� �̹����� ���� ���� �����ϴ�");
        return false;
    }

    BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

    if (nullptr == BitMap)
    {
        MsgAssert("�̹��� ������ �����߽��ϴ�.");
        return false;
    }

    ImageDC = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC)
    {
        MsgAssert("�̹��� HDC ������ �����߽��ϴ�.");
        return false;
    }

    // ImageDC 1,1 �迭�̶� ����Ǿ� �ִ�. 

    // 1, 1
    OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

    ImageScaleCheck();

    ImageClear();

    return true;
}

bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
    return ImageLoad(_Path.GetPathToString().c_str());
}

#define TEST(Value) Value

bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
    //HDC ImageDC;
    //HBITMAP BitMap;
    //HBITMAP OldBitMap;
    //BITMAP Info;

    // �̹����߿� �Ϻθ� �ε��Ҽ� �ִµ� 0�� �־��ָ� �� �ε��ϰڴٴ� �̾߱Ⱑ �����ϴ�.
    // LR_LOADFROMFILE ���Ͽ������� �ε��ϰڴٴ� �ǹ̰� �˴ϴ�.

    // �̹����� �ε��� 2���� �迭�� ������
    // �����쿡�� new�� �����ѰͰ� �ٸ��� ����.
    BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

    if (nullptr == BitMap)
    {
        std::string Path = _Path.data();
        MsgAssert(Path + " �̹��� �ε忡 �����߽��ϴ�.");
        return false;
    }

    ImageDC = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC)
    {
        std::string Path = _Path.data();
        MsgAssert(Path + " �̹��� HDC ������ �����߽��ϴ�.");
        return false;
    }

    // ImageDC 1,1 �迭�̶� ����Ǿ� �ִ�. 

    // 1, 1
    OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

    ImageScaleCheck();

    return true;
}

void GameEngineImage::ImageScaleCheck()
{
    HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
    GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}


// Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
    BitBlt(
        ImageDC, // ���� ���� �̹���
        _CenterPos.ix() - _Scale.hix(), // ��ġ 
        _CenterPos.iy() - _Scale.hiy(),
        _Scale.ix(),
        _Scale.iy(),
        _OtherImage->GetImageDC(), // ������ �̹���
        0,
        0,
        SRCCOPY
    );
}

// �����ʿ����� ����Ʈ ���ڸ� ǥ���� �ʿ䰡 �����ϴ�.
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color/* = RGB(255, 0, 255)*/)
{
    if (false == _OtherImage->IsCut)
    {
        MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
        return;
    }

    ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

    TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{

    TransparentBlt(ImageDC, // ���⿡ �׷���.
        _CopyCenterPos.ix() - _CopySize.hix(), // ���⸦ ��������
        _CopyCenterPos.iy() - _CopySize.hiy(),
        _CopySize.ix(), // �� ũ���
        _CopySize.iy(),
        _OtherImage->GetImageDC(),
        _OtherImagePos.ix(),// �̹����� x y��������
        _OtherImagePos.iy(),
        _OtherImageSize.ix(), // �̹����� x y������ ��ġ��
        _OtherImageSize.iy(),
        _Color);
}

void GameEngineImage::Cut(int _X, int _Y)
{
    ImageCutData Data;

    Data.SizeX = static_cast<float>(GetImageScale().ix() / _X);
    Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y);

    for (size_t i = 0; i < _Y; i++)
    {
        for (size_t i = 0; i < _X; i++)
        {
            ImageCutDatas.push_back(Data);
            Data.StartX += Data.SizeX;
        }

        Data.StartX = 0.0f;
        Data.StartY += Data.SizeY;
    }

    IsCut = true;
}

void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
    ImageCutData Data;

    Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X);
    Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y);

    Data.StartX = _Start.x;
    Data.StartY = _Start.y;

    for (size_t i = 0; i < _Y; i++)
    {
        for (size_t i = 0; i < _X; i++)
        {
            ImageCutDatas.push_back(Data);
            Data.StartX += Data.SizeX;
        }

        Data.StartX = _Start.x;
        Data.StartY += Data.SizeY;
    }

    IsCut = true;
}

DWORD GameEngineImage::GetPixelColor(float4 _Pos, DWORD _OutColor)
{
    return GetPixelColor(_Pos.ix(), _Pos.iy(), _OutColor);
}

DWORD GameEngineImage::GetPixelColor(int _X, int _Y, DWORD _OutColor)
{
    if (_X < 0)
    {
        return _OutColor;
    }
    if (_X >= GetImageScale().ix())
    {
        return _OutColor;
    }
    if (_Y < 0)
    {
        return _OutColor;
    }
    if (_Y >= GetImageScale().iy())
    {
        return _OutColor;
    }

    return GetPixel(ImageDC, _X, _Y);
}