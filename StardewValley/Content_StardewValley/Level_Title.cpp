#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineFile.h>

#include "globalValue.h"
#include "Level_Title.h"
#include "Title.h"
#include "Mouse.h"
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
    ImageRoad();

    CreateActor<Title>();
    CreateActor<Mouse>();
}

void Level_Title::Update(float _DeltaTime)
{

}


void Level_Title::ImageRoad()
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
        GameEngineImage* Button5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("newgamebuttonHover.BMP"));

        GameEngineImage* colButton1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("colnewgame.BMP"));

        GameEngineImage* Button2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("loadbutton.BMP"));
        GameEngineImage* Button3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("multibutton.BMP"));
        GameEngineImage* Button4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButton.BMP"));
        GameEngineImage* Button6 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ExitButtonHover.BMP"));

        GameEngineImage* Buttonnum = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Number.BMP"));
        Buttonnum->Cut(10, 1);

        GameEngineImage* number2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NumberBIG.BMP"));
        number2->Cut(10, 1);
        GameEngineImage* number3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Numbersmall.BMP"));
        number3->Cut(10, 1);

    }

    //인터페이스 미리 로딩
    {
        Dir.Move("UI");

        GameEngineImage* Quickslot = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Quickslot.BMP"));
        GameEngineImage* TimeBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TimeBar.BMP"));
        GameEngineImage* StatusBar = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StatusBar.BMP"));
        GameEngineImage* HP = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("HP.BMP"));
        GameEngineImage* Energy = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Energy.BMP"));
        GameEngineImage* Inventory = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Inventory.BMP"));
        GameEngineImage* SelectedLine = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectedLine.BMP"));
        GameEngineImage* Cursor = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cursor.BMP"));
        GameEngineImage* AffectionBox = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AffectionBox.BMP"));
        GameEngineImage* GiftCount = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GiftCount.BMP"));
        GiftCount->Cut(3, 1);
        GameEngineImage* Heart = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Heart.BMP"));
        Heart->Cut(1, 11);
        GameEngineImage* InventoryButton = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("InventoryButton.BMP"));
        GameEngineImage* AffectionButton = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("AffectionButton.BMP"));

        GameEngineImage* SelectedButton = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectedButton.BMP"));
        GameEngineImage* SelectedButtonRelease = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SelectedButtonRelease.BMP"));
       
        Dir.MoveParent();

    }
    //타이틀 산맥
    {
        GameEngineImage* Mountain1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMountain1.BMP"));
        GameEngineImage* Mountain2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleMountain2.BMP"));

        GameEngineImage* Cloud1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cloud1.BMP"));
        GameEngineImage* Cloud2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cloud2.BMP"));
        GameEngineImage* Cloud3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cloud3.BMP"));
        GameEngineImage* Cloud4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cloud4.BMP"));
        GameEngineImage* Cloud5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Cloud5.BMP"));

        GameEngineImage* Tree = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TitleTree.BMP"));

        GameEngineImage* Bird = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bird.BMP"));
        Bird->Cut(6, 1);
    }

    {
        Dir.Move("Map");
        GameEngineImage* BlackMap = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlackMap.BMP"));
        Dir.MoveParent();
    }

    {
        Dir.MoveParent();
        Dir.Move("Sound");
        Dir.Move("Effect");

        std::vector<GameEngineFile> Files = Dir.GetAllFile();

        for (size_t i = 0; i < Files.size(); i++)
        {
            GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
        }
    }

}