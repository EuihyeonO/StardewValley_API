#pragma once

class AdefaultClass
{

public:

	AdefaultClass();
	~AdefaultClass();

	AdefaultClass(const AdefaultClass& _Other) = delete;
	AdefaultClass(AdefaultClass&& _Other) noexcept = delete;
	AdefaultClass& operator=(const AdefaultClass& _Other) = delete;
	AdefaultClass& operator=(AdefaultClass&& _Other) noexcept = delete;

protected:

private:

};

