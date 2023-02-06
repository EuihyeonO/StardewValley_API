#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineInput.h"

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

HWND GameEngineWindow::HWnd = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize = { 800, 600 };
float4 GameEngineWindow::WindowPos = { 100, 100 };
float4 GameEngineWindow::ScreenSize = { 800, 600 };
GameEngineImage* GameEngineWindow::BackBufferImage = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;
bool GameEngineWindow::IsWindowUpdate = true;



LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_MOUSEMOVE:
    {
        int a = 0;
        break;
    }
    // �� �����찡 ���õǾ���.
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_KEYDOWN:
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        // Message�Լ��� 0�� �����ϰ� ������.
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{

}

void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
    // �����츦 ���� �ִ� class�� ������ ���̴�.
    // ���� �̷��̷��� �����츦 �������...
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // �־����� ������ ������ �⺻Icon�� �˴ϴ�.
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // �����쿡�� �̷� ������ windowŬ������ GameEngineWindowDefault��� �̸����� �������.
    // ���߿� ������ ���鶧 ������.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

    // hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // 1000�� ���α׷��� �����츦 ����޶�� ��û�ߴ�.
    // ������� �ٽ� Ư�� �����̶�� �����찡 ��������ٰ� �츮���� �˷��ִµ�.
    // Ư�� ���ڷ� �νĵǴ� �츮�� �����쿡�� ũ�⺯�� ����

    // (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (nullptr == HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // �����찡 ��������鼭���� ������� ������ 2�����迭�� ���������� ������ ���̴�.
    WindowBackBufferHdc = GetDC(HWnd);


    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // ũ�� �ٲٰ� ���´�.
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);


    return;
}

void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

void GameEngineWindow::DoubleBufferRender()
{
    //static GameEngineImage* BackBufferImage;
    //static GameEngineImage* DoubleBufferImage;
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
}

int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    // ����Ű�ε�. �Ƚᵵ ������ ������ �ʴ´�.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg;

    // ���� �Լ��� ����ɶ����� ���α׷��� �����.

    // �⺻ �޽��� �����Դϴ�:
    // GetMessage�� �� �����쿡 �������� ������� üũ����.
    // GetMessage�� �������� Ư���� ���� �������� ���ߴ� �Լ��ΰ̴ϴ�.
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // ������ �޼����� ó���Ѵ�.
        // GetMessage�� �����Լ��̱� ������ ���ʿ� ������ ����� �ִ� �޼��� ����� �ƴϴ�
        // => ������ �������� ���ƾ� �ϴµ�
        // GetMessage��� �Լ��� => �����쿡 �������� ����� ���ϵǴ� �Լ�
        // �����쿡 �������� ����� ������ �Ѵ�.

        // if (GetMessage(&msg, nullptr, 0, 0))
        // ���� �޼��� �־�? ����? ���������� ��ٸ���.

        // �޼����� �ֵ� ���� ���ϵ˴ϴ�.
        // �׿��ִ� �޼����� �����϶�� ����Դϴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            // ���� �޼��� �־�? ���� �� ����.
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // �޼����� �������� ������ �����մϴ�.
            if (nullptr != _Loop)
            {
                _Loop();
            }

            GameEngineInput::IsAnyKeyOff();
            continue;
        }

        // ����Ÿ��
        // ����Ÿ�ӿ� ������ �����ϴ°�. 
        if (nullptr != _Loop)
        {
            _Loop();
        }

        GameEngineInput::IsAnyKeyOff();
    }

    if (nullptr != _End)
    {
        _End();
    }

    if (nullptr != BackBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

void GameEngineWindow::SettingWindowSize(float4 _Size)
{

    // �� Ÿ��Ʋ�ٿ� �����ӱ��� ����ؼ� ũ�⸦ ��������� �Ѵ�.

    //          ��ġ      ũ��
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // ���� ���ϴ� ũ�⸦ ������ Ÿ��Ʋ�ٱ��� ����� ũ�⸦ �����ִ� �Լ�.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    // 0�� �־��ָ� ������ ũ�⸦ �����Ѵ�.
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // ������ �Ȱ��� ũ���� �̹����Դϴ�.

    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);


}
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;
    LPPOINT PointPtr = &MoniterPoint;
    GetCursorPos(PointPtr);
    ScreenToClient(HWnd, PointPtr);

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}