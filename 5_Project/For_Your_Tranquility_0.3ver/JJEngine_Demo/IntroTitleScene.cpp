#include "pch.h"
#include "IntroTitleScene.h"

#include "ObjectManager.h"
#include "GameObject.h"
#include "InteractionObject.h"

#include "TextBox.h"

IntroTitleScene::IntroTitleScene()
{

}

IntroTitleScene::~IntroTitleScene()
{

}

void IntroTitleScene::Initialize()
{
	InputManager::GetInstance()->Reset();
	//ObjectManager::GetInstance();

	Character = new GameObject();
	Character->Initialize(JVector(200, 200), L"GameObject");
	Character->SetSpriteSheet(L"../../../4_Resources/sheet_example.png");

	testObject = new InteractionObject();
	testObject->Initialize(JVector(400, 0), L"testObject");
	testObject->SetSprite(L"../../../4_Resources/Ingame_Resources/cursors/cursor_pincette.png", 2);

	textBox = new TextBox();
	textBox->Initialize(JVector(50, 600), L"IntroTitleScene");
	
	//testGameObject = new GameObject();
	//testGameObject->Initialize(JVector(0, 0), L"testGameObject");
	//testGameObject->SetSpriteSheet(L"../../../4_Resources/Ingame_Resources/cursors/cursor_pincette.png");

	/*
	/// ObjectManager�� AddObject() �ϴ� ����
	/// ...
	*/
}

void IntroTitleScene::Update(float dTime)
{
	/// ������Ʈ�Ŵ����� Update�� ���ߵ�
	Character->Update(dTime);
	testObject->Update(dTime);
	textBox->Update(dTime);

	Character->Transform()->TranslateAnimation(dTime, 500, 600, 2);

	//testGameObject->Transform()->SetPos(InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y);

	Character->PlayAnimation(dTime, 2.0f);

	/// �� �ѱ�� ��ư�� üũ
	if (InputManager::GetInstance()->CheckLeftButtonUp())
	{
		//SceneManager::ChangeScene(eSceneStateAll::INTRO_ANIMATION);

		// �׽�Ʈ������ ĳ���� ����� �ٲ��ش�.
		Character->SetMotion();

		// ���� �ؽ�Ʈ�� �� ��µǾ����� ���� �ؽ�Ʈ�� ���
		if (textBox->IsNowTextEnd())
			textBox->DrawNextText();
		else
			textBox->DrawAllNowText();

		//testGameObject->NextMotionFrame();
	}

	/// ���콺�� �浹üũ -> ������Ʈ �Ŵ����� Update�� ���ߵ�
	dynamic_cast<InteractionObject*>(testObject)->CheckClicked();
}

void IntroTitleScene::Render()
{
	Character->Draw(0.5f);
	//testObject->Draw();
	textBox->Draw();

	//testGameObject->Draw();

	ShowDebug();
}

void IntroTitleScene::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Title ��");
}

void IntroTitleScene::Finalize()
{
	// ������Ʈ �Ŵ����� �ҷ��� ������Ʈ ����Ʈ�� ����ش�.
}