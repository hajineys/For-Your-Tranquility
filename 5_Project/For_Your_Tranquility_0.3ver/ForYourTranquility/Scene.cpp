#include "pch.h"
#include "Scene.h"
#include "Button.h"
#include "ObjectManager.h"

Scene::Scene()
	:m_pObjectManager(nullptr), m_NowSceneState(eNowSceneState::NONE), m_IsGameEnd(false)
{
	
}

Scene::~Scene()
{

}

void Scene::Initialize()
{
	// 씬마다 오브젝트 매니저 생성
	m_pObjectManager = new ObjectManager();

}

void Scene::ShowDebug()
{
	static bool _IsDebugShow = false;

	if (InputManager::GetInstance()->CheckF5ButtonUp())
	{
		if (!_IsDebugShow)
			_IsDebugShow = true;
		else
			_IsDebugShow = false;

		InputManager::GetInstance()->Reset();
	}

	if (!_IsDebugShow)
	{
		return;
	}
}

void Scene::Release()
{	
	m_pObjectManager->Release();

	// 오브젝트 매니저 제거
	if (m_pObjectManager != nullptr)
	{
		delete(m_pObjectManager);
		m_pObjectManager = nullptr;
	}
}