#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Button;
class MenuButton : public GameEngineActor
{

public:

    static void SetGlobalMenuButton(MenuButton* _Button)
    {
        GlobalMenuButton = _Button;
    }

    static MenuButton* GetGlobalMenuButton()
    {
        return GlobalMenuButton;
    }

    void MenuButtonOn();
    void MenuButtonOff();
    void MenuButtonOnOff();

    void SetInventoryButtonToSelectedPos();
    void SetAffectionButtonToSelectedPos();

	MenuButton();
	~MenuButton();

	MenuButton(const MenuButton& _Other) = delete;
	MenuButton(MenuButton&& _Other) noexcept = delete;
	MenuButton& operator=(const MenuButton& _Other) = delete;
	MenuButton& operator=(MenuButton&& _Other) noexcept = delete;

protected:
    void Start() override;
    void Update(float _DeltaTime) override;
    void Render(float _Time) override;
private:
    Button* InventoryButton = nullptr;
    Button* AffectionButton = nullptr;

    static MenuButton* GlobalMenuButton;
};

