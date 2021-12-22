#include "pch.h"

#include "GameProcess.h"

#ifdef _DEBUG

#ifdef UNICODE
//유니코드
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#endif

// 윈도 프로시저
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 윈 메인
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow)
{
	// 애플리케이션 초기화를 수행합니다:

	GameProcess* pGameProcess = new GameProcess();

	if (!pGameProcess->Initialize(hInstance))
	{
		return FALSE;
	}

	pGameProcess->MessageLoop();
	pGameProcess->Release();

	return 0;
}