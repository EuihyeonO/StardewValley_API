#include "GameEngineString.h"
#include <Windows.h>
#include "GameEngineDebug.h"

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}


std::string GameEngineString::ToUpper(const std::string_view& _Str)
{
    std::string Text = _Str.data();

    for (size_t i = 0; i < Text.size(); i++)
    {
        Text[i] = toupper(Text[i]);
    }

    return Text;
}

std::string GameEngineString::ToString(int Value)
{
    return std::to_string(Value);
}


std::wstring GameEngineString::AnsiToUniCode(const std::string_view& _Text)
{
    // 2���� ������ �ֽ��ϴ�.
    // ���� ��ȯ
    // ��ȯ�ϸ� ���� ����Ʈ�� �ʿ��Ѱ�.
    // CP_ACP��ȯ�Ϸ��� ���ڵ��ε�
    // CP_ACP
    int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return L"";
    }

    std::wstring Result;
    Result.resize(Size);

    Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return L"";
    }

    return Result;
}


std::string GameEngineString::UniCodeToAnsi(const std::wstring_view& _Text)
{
    int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return "";
    }

    std::string Result;
    Result.resize(Size);

    Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return "";
    }

    return Result;
}

std::string GameEngineString::UniCodeToUTF8(const std::wstring_view& _Text)
{
    int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, nullptr);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return "";
    }

    std::string Result;
    Result.resize(Size);

    Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

    if (0 == Size)
    {
        MsgAssert("���ڿ� ��ȯ�� �����߽��ϴ�");
        return "";
    }

    return Result;

}

std::string GameEngineString::AnsiToUTF8(const std::string_view& _Text)
{
    std::wstring Unicode = AnsiToUniCode(_Text);
    return UniCodeToUTF8(Unicode.c_str());
}