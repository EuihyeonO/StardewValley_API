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
    // 내 윈도우가 선택되었다.
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
        // Message함수가 0을 리턴하게 만들어라.
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
    // 윈도우를 찍어낼수 있는 class를 만들어내는 것이다.
    // 나는 이러이러한 윈도우를 만들어줘...
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // 넣어주지 않으면 윈도우 기본Icon이 됩니다.
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 윈도우에게 이런 내용을 window클래스를 GameEngineWindowDefault라는 이름으로 등록해줘.
    // 나중에 윈도우 만들때 쓸꺼냐.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 1000번 프로그램이 윈도우를 띄워달라고 요청했다.
    // 윈도우는 다시 특정 숫자이라는 윈도우가 만들어졌다고 우리에게 알려주는데.
    // 특정 숫자로 인식되는 우리의 윈도우에게 크기변경 떠라

    // (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (nullptr == HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우가 만들어지면서부터 만들어진 색깔의 2차원배열의 수정권한을 얻어오는 것이다.
    WindowBackBufferHdc = GetDC(HWnd);


    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // 크기 바꾸고 얻어온다.
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
    // 단축키인데. 안써도 문제가 되지는 않는다.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    if (nullptr != _Start)
    {
        _Start();
    }


    MSG msg;

    // 동기 함수가 종료될때까지 프로그램이 멈춘다.

    // 기본 메시지 루프입니다:
    // GetMessage는 내 윈도우에 무슨일이 생기는지 체크해줘.
    // GetMessage는 윈도우의 특별한 일이 생길대까지 멈추는 함수인겁니다.
    while (IsWindowUpdate)
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        //}

        // 윈도우 메세지를 처리한다.
        // GetMessage는 동기함수이기 때문에 애초에 게임을 만들수 있는 메세지 방식이 아니다
        // => 게임은 쉴새없이 돌아야 하는데
        // GetMessage라는 함수는 => 윈도우에 무슨일이 생기면 리턴되는 함수
        // 윈도우에 무슨일이 생기게 만들어야 한다.

        // if (GetMessage(&msg, nullptr, 0, 0))
        // 동기 메세지 있어? 없어? 있을때까지 기다릴께.

        // 메세지가 있든 없든 리턴됩니다.
        // 쌓여있는 메세지를 삭제하라는 명령입니다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            // 동기 메세지 있어? 없어 난 갈께.
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // 메세지가 있을때도 게임을 실행합니다.
            if (nullptr != _Loop)
            {
                _Loop();
            }

            GameEngineInput::IsAnyKeyOff();
            continue;
        }

        // 데드타임
        // 데드타임에 게임을 실행하는것. 
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

    // 그 타이틀바와 프레임까지 고려해서 크기를 설정해줘야 한다.

    //          위치      크기
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // 내가 원하는 크기를 넣으면 타이틀바까지 고려한 크기를 리턴주는 함수.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };
    // 0을 넣어주면 기존의 크기를 유지한다.
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // 완전히 똑같은 크기의 이미지입니다.

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