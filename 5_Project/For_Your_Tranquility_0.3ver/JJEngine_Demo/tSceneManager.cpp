#include "pch.h"

#include "tSceneManager.h"
#include "tIntroTitleScene.h"

// static 멤버 변수 초기화
eSceneStateAll tSceneManager::SceneState = eSceneStateAll::INTRO_TITLE;				// 게임 첫 시작 State는 Intro로 설정
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
	// 씬 전환
	if (SceneState != nextScene)
	{
		// 기존 씬 삭제(Safe Delete)
		if (pNowScene)
		{
			pNowScene->Finalize();
			delete pNowScene;

			// 삭제 후 nullptr로 초기화
			pNowScene = nullptr;
		}
	}

	switch (nextScene)
	{
		case eSceneStateAll::INTRO_TITLE:
		{
			// 인트로 타이틀 실행
			pNowScene = new tIntroTitleScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::INTRO_ANIMATION:
		{
			// 인트로 애니메이션 실행
			//pNowScene = new IntroAnimationScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_OFFICE:
		{
			// 메인 사무실 실행
			//pNowScene = new MainOfficeScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_AUTOPSY:
		{
			// 메인 부검실 실행
			//pNowScene = new MainAutopsyRoomScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::MAIN_DISSECTING:
		{
			// 메인 해부실 실행
			//pNowScene = new MainDissectingRoomScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}

		case eSceneStateAll::OUTRO_RESULT:
		{
			// 아웃트로 결과 실행
			//pNowScene = new OutroResultScene;
			pNowScene->Initialize();
			SceneState = nextScene;
		}
		break;

		case eSceneStateAll::OUTRO_ENDING:
		{
			// 아웃트로 엔딩 실행
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