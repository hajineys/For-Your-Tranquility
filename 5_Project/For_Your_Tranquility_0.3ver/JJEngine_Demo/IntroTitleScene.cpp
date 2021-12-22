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
	/// ObjectManager에 AddObject() 하는 내용
	/// ...
	*/
}

void IntroTitleScene::Update(float dTime)
{
	/// 오브젝트매니저의 Update에 들어가야됨
	Character->Update(dTime);
	testObject->Update(dTime);
	textBox->Update(dTime);

	Character->Transform()->TranslateAnimation(dTime, 500, 600, 2);

	//testGameObject->Transform()->SetPos(InputManager::GetInstance()->GetMousePos().x, InputManager::GetInstance()->GetMousePos().y);

	Character->PlayAnimation(dTime, 2.0f);

	/// 씬 넘기는 버튼을 체크
	if (InputManager::GetInstance()->CheckLeftButtonUp())
	{
		//SceneManager::ChangeScene(eSceneStateAll::INTRO_ANIMATION);

		// 테스트용으로 캐릭터 모션을 바꿔준다.
		Character->SetMotion();

		// 현재 텍스트가 다 출력되었으면 다음 텍스트를 재생
		if (textBox->IsNowTextEnd())
			textBox->DrawNextText();
		else
			textBox->DrawAllNowText();

		//testGameObject->NextMotionFrame();
	}

	/// 마우스와 충돌체크 -> 오브젝트 매니저의 Update에 들어가야됨
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
	JJEngine::GetInstance()->DrawText(0, 40, L"Intro_Title 씬");
}

void IntroTitleScene::Finalize()
{
	// 오브젝트 매니저를 불러와 오브젝트 리스트를 비워준다.
}