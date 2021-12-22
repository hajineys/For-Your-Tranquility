#include "pch.h"

#include "tSceneManager.h"
#include "tIntroTitleScene.h"

// static ��� ���� �ʱ�ȭ
eSceneStateAll tSceneManager::SceneState = eSceneStateAll::INTRO_TITLE;				// ���� ù ���� State�� Intro�� ����
IScene* tSceneManager::pNowScene = nullptr;

tSceneManager::tSceneManager()
{

}

tSceneManager::~tSceneManager()
{

}

void tSceneManager::Initialize()
{

}

void tSceneManager::Update(float dTime)
{
	if (pNowScene)
	{
		pNowScene->Update(dTime);
	}
}

void tSceneManager::Render()
{
	if (pNowScene)
	{
		pNowScene->Render();
	}
}

void tSceneManager::ChangeScene(eSceneStateAll nextScene)
{
	// �� ��ȯ
	if (SceneState != nextScene)
	{
		// ���� �� ����(Safe Delete)
		if (pNowScene)
		{
			pNowScene->Finalize();
			delete pNowScene;

			// ���� �� nullptr�� �ʱ�ȭ
			pNowScene = nullptr;
		}
	}

	switch (nextScene)
	{
		case eSceneStateAll::INTRO_TITLE:
		{
			// ��Ʈ�� Ÿ��Ʋ ����
			pNowScene = new tIntroTitleScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::INTRO_ANIMATION:
		{
			// ��Ʈ�� �ִϸ��̼� ����
			//pNowScene = new IntroAnimationScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_OFFICE:
		{
			// ���� �繫�� ����
			//pNowScene = new MainOfficeScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_AUTOPSY:
		{
			// ���� �ΰ˽� ����
			//pNowScene = new MainAutopsyRoomScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_DISSECTING:
		{
			// ���� �غν� ����
			//pNowScene = new MainDissectingRoomScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}

		case eSceneStateAll::OUTRO_RESULT:
		{
			// �ƿ�Ʈ�� ��� ����
			//pNowScene = new OutroResultScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::OUTRO_ENDING:
		{
			// �ƿ�Ʈ�� ���� ����
			//pNowScene = new OutroEndingScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;
	}
}

void tSceneManager::Finalize()
{
	if (pNowScene)
	{
		pNowScene->Finalize();
	}
}