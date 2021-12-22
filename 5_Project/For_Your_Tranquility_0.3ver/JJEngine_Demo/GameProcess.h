#pragma once

class JTimer;
class tInputManager;
class tSceneManager;

class GameProcess
{
private:
	HWND m_hwnd;

	JTimer* m_pTimer;
	tSceneManager* m_pSceneManager;

public:
	GameProcess();
	~GameProcess();

public:
	bool Initialize(HINSTANCE hInstance);
	void Release();

	void MessageLoop();
	void GameLoop();

	void CreateManager();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};