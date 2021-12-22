#include "pch.h"

#include "GameProcess.h"
#include "Scene.h"

GameProcess::GameProcess()
	:m_pTimer(nullptr), m_pSceneManager(nullptr), m_hwnd(nullptr)
{

}

GameProcess::~GameProcess()
{

}

bool GameProcess::Initialize(HINSTANCE hInstance)
{
	/// 윈도우창을 등록한다
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
	m_hwnd = CreateWindowExW(WS_EX_APPWINDOW, _T("ForYourTranquility"), _T("당신의 안녕을 위하여"), WS_POPUP,
		0, 0, CW_XSIZE, CW_YSIZE, nullptr, nullptr, hInstance, nullptr);

	if (!m_hwnd)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hwnd);

	// 매니저 클래스 생성
	CreateManager();

	// 리소스를 로드
	LoadResources();
	// 파일 철(게임매니저) 생성
	CreateFileFolder();

	// 씬을 생성
	CreateScene();

	return true;
}

void GameProcess::Release()
{
	JJEngine::GetInstance()->Release();

	if (m_pTimer != nullptr)
	{
		m_pTimer->Release();
		delete m_pTimer;
		m_pTimer = nullptr;
	}

	InputManager::GetInstance()->DeleteInstance();
	SoundManager::GetInstance()->Release();
	//FileFolder::GetInstance()->Release();
	//ResourceManager::GetInstance()->Release();

	if (m_pSceneManager != nullptr)
	{
		m_pSceneManager->Release();
		delete m_pSceneManager;
		m_pSceneManager = nullptr;
	}
}

void GameProcess::MessageLoop()
{
	MSG msg;

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
	InputManager::GetInstance()->Update();
	SoundManager::GetInstance()->Update();

	m_pSceneManager->Update(_dTime);
	//------------------------------------------------------------
	JJEngine::GetInstance()->BeginRender();
	m_pSceneManager->Render();

// 	JJEngine::GetInstance()->DrawText(0, 0, L"FPS : %.0f", FPS);
// 	JJEngine::GetInstance()->DrawText(0, 20, L"DeltaTime : %f", _dTime);
// 	JJEngine::GetInstance()->DrawText(300, 0, L"MousePosX : %d", InputManager::GetInstance()->GetMousePos().x);
// 	JJEngine::GetInstance()->DrawText(300, 20, L"MousePosY : %d", InputManager::GetInstance()->GetMousePos().y);

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

	// InputManager 초기화
	InputManager::GetInstance()->Initialize(m_hwnd);

	// SoundManager 초기화
	SoundManager::GetInstance()->Initialize(5);
}

void GameProcess::LoadResources()
{
	// 리소스 이미지들을 로드한다.
	ResourceManager::GetInstance()->LoadImageFile(_T("../../../4_Resources/Ingame_Resources"));

	// 사운드 리소스들을 로드한다.
	SoundManager::GetInstance()->LoadSoundFile(_T("../../../4_Resources/Sound_Resources"));
}

void GameProcess::CreateFileFolder()
{
	
}

void GameProcess::CreateScene()
{
	// SceneManager 생성
	m_pSceneManager = new SceneManager;
	m_pSceneManager->Initialize();

	// 씬 매니저의 상태를 INTRO로 초기화
	m_pSceneManager->ChangeScene(eSceneStateAll::INTRO_TITLE);
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