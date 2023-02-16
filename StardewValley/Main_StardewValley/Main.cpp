#include <Windows.h>
#include <Content_StardewValley/ContentsCore.h>

#include <vector>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
    ContentsCore::GetCore().CoreStart(hInstance);
	return 1;
}