#include "pch.h"
#include "tIntroTitleScene.h"

#include "tObjectManager.h"
#include "tGameObject.h"
#include "tInteractionObject.h"

#include "tTextBox.h"

tIntroTitleScene::tIntroTitleScene()
{

}

tIntroTitleScene::~tIntroTitleScene()
{

}

void tIntroTitleScene::Initialize()
{
	tInputManager::GetInstance()->Reset();
	//ObjectManager::GetInstance();

	Character = new tGameObject();
	Character->Initialize(JVector(200, 200), L"sheet_example");


	//Character->SetSpriteSheet(L"../../../4_Resources/sheet_example.png");

// 	testObject = new tInteractionObject();
// 	testObject->Initialize(JVector(400, 0), L"Testcharacter1");
// 	testObject->SetSprite(L"../../../4_Resources/Ingame_Resources/cursors/cursor_pincette.png", 2);

	//textBox = new tTextBox();
	//textBox->Initialize(JVector(50, 600), L"IntroTitleScene");
	
	//testGameObject = new GameObject();
	//testGameObject->Initialize(JVector(0, 0), L"testGameObject");
	//testGameObject->SetSpriteSheet(L"../../../4_Resources/Ingame_Resources/cursors/cursor_pincette.png");

	/*
	/// ObjectManager�� AddObject() �ϴ� ����
	/// ...
	*/
}

void tIntroTitleScene::Update(float dTime)
{
	Character->Update(dTime);

	/// �ε巯�� �̵�
	Character->Transform()->TranslateSmoothAnimation(dTime, 1300, 800, 1.0f);
	/// �׳� �̵�
	//Character->Transform()->TranslateAnimation(dTime, 1300, 800, 1.0f);

	Character->PlayAnimation(dTime, 2.0f);
	//Character->UpdateAnimation(dTime);

	/// �� �ѱ�� ��ư�� üũ
	if (tInputManager::GetInstance()->CheckLeftButtonUp())
	{
		// �׽�Ʈ������ ĳ���� ����� �ٲ��ش�.
		Character->SetPlayCount(3);
		Character->SetMotion();
	}
}

void tIntroTitleScene::Render()
{
	Character->Draw(0.5f);

	ShowDebug();
}

void tIntroTitleScene::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Title ��");
}

void tIntroTitleScene::Finalize()
{
	// ������Ʈ �Ŵ����� �ҷ��� ������Ʈ ����Ʈ�� ����ش�.
}