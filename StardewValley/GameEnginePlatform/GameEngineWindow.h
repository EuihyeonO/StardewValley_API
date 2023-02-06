#pragma once
#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

// ������� �ڵ� ����̶�°��� �̿��Ѵ�.
// �ڵ����̶� �츮���� os�� �����Ѵٴ� �������� ���� 1�� �ݴϴ�.
// �� ���ڸ� �ڵ��̶�� �մϴ�.

// ���� :
class GameEngineImage;
class GameEngineWindow
{
    static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
    // �����츦 ����� �ִ� ����Դϴ�.
    static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

    static void SettingWindowSize(float4 _Size);
    static void SettingWindowPos(float4 _Pos);

    static float4 GetScreenSize()
    {
        return ScreenSize;
    }

    static HWND GetHWnd()
    {
        return HWnd;
    }

    static HDC GetWindowBackBufferHdc()
    {
        return WindowBackBufferHdc;
    }

    static GameEngineImage* GetDoubleBufferImage()
    {
        return DoubleBufferImage;
    }

    static void AppOff()
    {
        IsWindowUpdate = false;
    }

    static void DoubleBufferClear();
    static void DoubleBufferRender();

    // ���� ���� �ܺο��� ���°� ��������ֱ⸸ �ϸ� �ǰ� ����°�.
    // �׷��� �ٸ� Ŭ������ ���������� ������ ���� �ʰ� ������ ��Ű�� ���� �ϴ� Ŭ������ �Ǵ°�
    // ���� �Լ��� ��� ��������ִ� �� �Լ������͸� �̿��� ����� callback ����̶�� �մϴ�.
    // void(*Start)(), void(*Loop)(), void(*End)() �ܺο��� �Լ������͸� �ñ�� ���.
    // => �������� ����� �и��ϱ� ���ؼ�
    static int WindowLoop(void(*Start)(), void(*Loop)(), void(*End)());

    static float4 GetMousePosition();

    GameEngineWindow();
    ~GameEngineWindow();

    // delete Function
    GameEngineWindow(const GameEngineWindow& _Other) = delete;
    GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
    GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
    GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;



protected:

private:
    static float4 WindowSize;
    static float4 ScreenSize;
    static float4 WindowPos;
    static HWND HWnd;
    static HDC WindowBackBufferHdc; // �����쿡 �׸��� �׸��� �ִ� ����.
    static GameEngineImage* BackBufferImage;
    static GameEngineImage* DoubleBufferImage;
    static bool IsWindowUpdate;
};

