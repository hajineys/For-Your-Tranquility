#include "pch.h"

#include "GameProcess.h"
#include "IScene.h"

GameProcess::GameProcess()
	:m_pTimer(nullptr), m_pSceneManager(nullptr)
{

}

GameProcess::~GameProcess()
{

}

bool GameProcess::Initialize(HINSTANCE hInstance)
{
	/// 윈도를 등록한다.
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameProcess::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("ForYourTranquility");
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	// 애플리케이션 초기화를 수행합니다:
	m_hwnd = CreateWindowW(_T("ForYourTranquility"), _T("당신의 안녕을 위하여"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!m_hwnd)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	CreateManager();

	return true;
}

void GameProcess::Release()
{
	JJEngine::GetInstance()->Release();
	//delete pJJEngine;
}

void GameProcess::MessageLoop()
{
	MSG msg;

	tSoundManager::Init();
	tSoundManager* sound = new tSoundManager("../../Data/Sound/ParkGumSa.mp3", true);
	sound->play();

	tResourceManager::GetInstance()->LoadImageFile(_T("../../../4_Resources"));

	// 씬 매니저의 상태를 INTRO로 초기화
	m_pSceneManager->ChangeScene(eSceneStateAll::INTRO_TITLE);

	// 기본 메시지 루프입니다
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			GameLoop();
		}
	}
}

void GameProcess::GameLoop()
{
	float FPS = m_pTimer->GetFPS();
	float _dTime = m_pTimer->GetDeltaTime();
	m_pTimer->Update();
	tInputManager::GetInstance()->Update();

	m_pSceneManager->Update(_dTime);
	//------------------------------------------------------------
	JJEngine::GetInstance()->BeginRender();
	m_pSceneManager->Render();

	JJEngine::GetInstance()->DrawText(0, 0, L"FPS : %.0f", FPS);
	JJEngine::GetInstance()->DrawText(0, 20, L"DeltaTime : %f", _dTime);

	JJEngine::GetInstance()->EndRender();
	//------------------------------------------------------------
}

void GameProcess::CreateManager()
{
	// 엔진 생성
	JJEngine::GetInstance()->Initialize(m_hwnd);

	// 타이머 생성
	m_pTimer = new JTimer();
	m_pTimer->Initialize();

	// SceneManager 생성
	m_pSceneManager = new tSceneManager;
	m_pSceneManager->Initialize();

	// InputManager 초기화
	tInputManager::GetInstance()->Initialize(m_hwnd);
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}