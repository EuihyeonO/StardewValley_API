#pragma once
#include <string>
#include <string_view>

// ���� == Ư������ 1���� ��Ī�ϴ� ���

// ��Ƽ����Ʈ : ���ڸ� 1����Ʈ�� 2����Ʈ�� ǥ���ϴ� ���ڵ� ���
// ��Ƽ����Ʈ ansiǥ������̶�� �Ҹ��⵵ �մϴ�.
// �����ڵ� : ���ڸ� 2����Ʈ�� ǥ���ϴ� ���ڵ� ���
// => 2����Ʈ ���� ����ǥ�� ������ ��� ���ڸ� 2����Ʈ �ȿ� ������ ������.

// �׷��� UTF ��ĵ���� ���Դ�.
// �׷��� UTF 1~3 4����Ʈ�θ� 3����Ʈ�θ�
// ���־�Ʃ����� �˼����� ǥ�����Դϴ�.

// ���� :
class GameEngineString
{
public:
    static std::string ToUpper(const std::string_view& _Str);
    static std::string ToString(int Value);

    static std::wstring AnsiToUniCode(const std::string_view& _Text);
    static std::string UniCodeToAnsi(const std::wstring_view& _Text);

    static std::string UniCodeToUTF8(const std::wstring_view& _Text);
    static std::string AnsiToUTF8(const std::string_view& _Text);

protected:

private:
    // constrcuter destructer
    GameEngineString();
    ~GameEngineString();
    GameEngineString(const GameEngineString& _Other) = delete;
    GameEngineString(GameEngineString&& _Other) noexcept = delete;
    GameEngineString& operator=(const GameEngineString& _Other) = delete;
    GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

