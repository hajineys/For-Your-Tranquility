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
	/// ������â�� ����Ѵ�
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

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	m_hwnd = CreateWindowExW(WS_EX_APPWINDOW, _T("ForYourTranquility"), _T("����� �ȳ��� ���Ͽ�"), WS_POPUP,
		0, 0, CW_XSIZE, CW_YSIZE, nullptr, nullptr, hInstance, nullptr);

	if (!m_hwnd)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hwnd);

	// �Ŵ��� Ŭ���� ����
	CreateManager();

	// ���ҽ��� �ε�
	LoadResources();
	// ���� ö(���ӸŴ���) ����
	CreateFileFolder();

	// ���� ����
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

	// �⺻ �޽��� �����Դϴ�
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
	// ���� ����
	JJEngine::GetInstance()->Initialize(m_hwnd);

	// Ÿ�̸� ����
	m_pTimer = new JTimer();
	m_pTimer->Initialize();

	// InputManager �ʱ�ȭ
	InputManager::GetInstance()->Initialize(m_hwnd);

	// SoundManager �ʱ�ȭ
	SoundManager::GetInstance()->Initialize(5);
}

void GameProcess::LoadResources()
{
	// ���ҽ� �̹������� �ε��Ѵ�.
	ResourceManager::GetInstance()->LoadImageFile(_T("../../../4_Resources/Ingame_Resources"));

	// ���� ���ҽ����� �ε��Ѵ�.
	SoundManager::GetInstance()->LoadSoundFile(_T("../../../4_Resources/Sound_Resources"));
}

void GameProcess::CreateFileFolder()
{
	
}

void GameProcess::CreateScene()
{
	// SceneManager ����
	m_pSceneManager = new SceneManager;
	m_pSceneManager->Initialize();

	// �� �Ŵ����� ���¸� INTRO�� �ʱ�ȭ
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