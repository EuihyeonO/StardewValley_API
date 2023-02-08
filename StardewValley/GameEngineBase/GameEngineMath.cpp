#include "GameEngineMath.h"
#include "GameEngineString.h"

// 변수명은 숫자가 앞에올수가 없습니다.

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;

const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Down = { 0.0f, 1.0f, 0.0f, 1.0f };

// 2d때는 쓸일이 없을것이다.
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };

// 뭘하는 함수냐?
// 123121 [1][2][3][1][2][1]
std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
    // std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

    //if (0 == _Value)
    //{
    //	ResultValue.push_back(0);
    //	return ResultValue;
    //}

    //int Lenth = GetLenth(_Value);
    //ResultValue.resize(Lenth);

    //int Value = _Value;
    //int HighestDigitValue = 0;
    //for (size_t i = 0; i < Lenth; i++)
    //{
    //	HighestDigitValue = Value / pow(10, Lenth - (1 + i));
    //	ResultValue[i] = HighestDigitValue;
    //	Value -= HighestDigitValue * pow(10, Lenth - (1 + i));
    //}

    std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

    std::string StringValue = GameEngineString::ToString(_Value);

    int StartIndex = 0;

    if (0 != StringValue.size() && StringValue[0] == '-')
    {
        StartIndex = 1;
    }

    ResultValue.reserve(StringValue.size());

    for (size_t i = StartIndex; i < StringValue.size(); i++)
    {
        ResultValue.push_back(StringValue[i] - '0');
    }

    return ResultValue;
}

unsigned int GameEngineMath::GetLenth(int _Value)
{
    std::vector<unsigned int> ResultValue = std::vector<unsigned int>();

    std::string StringValue = GameEngineString::ToString(_Value);

    int StartIndex = 0;

    if (0 != StringValue.size() && StringValue[0] == '-')
    {
        StartIndex = 1;
    }

    return static_cast<unsigned int>(StringValue.size()) - StartIndex;
}