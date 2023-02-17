#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

#include "globalValue.h"
#include "Level_Title.h"
#include "Title.h"
#include "Player.h"

Level_Title::Level_Title()
{
}

Level_Title::~Level_Title()
{
}

void Level_Title::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Level_Title::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void Level_Title::Loading()
{
    GameEngineDirectory Dir;

    Dir.MoveParentToDirectory("ContentsResources");
    Dir.Move("ContentsResources");
    Dir.Move("Image");

    //타이틀 배경
    {
        GameEngineImage* IntroBackground = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Intro1.BMP"));
    }

    {
        //타이틀 로고(게임이름)
        GameEngineImage* IntroTitle = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleName.BMP"));


        //타이틀 버튼 ( 시작, 종료 등등)
        GameEngineImage* Button1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("newgamebutton.BMP"));

        GameEngineImage* colButton1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("colnewgame.BMP"));

        GameEngineImage* Button2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("loadbutton.BMP"));
        GameEngineImage* Button3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("multibutton.BMP"));
        GameEngineImage* Button4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));

        GameEngineImage* Buttonnum = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
        Buttonnum->Cut(10, 1);

    }

    //인터페이스 미리 로딩
    {
        Dir.Move("UI");

        GameEngineImage* Quickslot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Quickslot.BMP"));
        GameEngineImage* TimeBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimeBar.BMP"));
        GameEngineImage* StatusBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StatusBar.BMP"));
        GameEngineImage* Inventory = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Inventory.BMP"));
        GameEngineImage* SelectedLine = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectedLine.BMP"));
        GameEngineImage* Cursor = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cursor.BMP"));
        Dir.MoveParent();
    }
        //타이틀 산맥
    {
        GameEngineImage* Mountain1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMountain1.BMP"));
        GameEngineImage* Mountain2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMountain2.BMP"));

        GameEngineImage* Tree = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleTree.BMP"));
    }

    CreateActor<Title>();
}
void Level_Title::Update(float _DeltaTime)
{

}