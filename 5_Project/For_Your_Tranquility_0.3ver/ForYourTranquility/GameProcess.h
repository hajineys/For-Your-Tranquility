#pragma once

class JTimer;
class InputManager;
class SceneManager;

class GameProcess
{
private:
	HWND m_hwnd;

	JTimer* m_pTimer;
	SceneManager* m_pSceneManager;

public:
	GameProcess();
	~GameProcess();

public:
	bool Initialize(HINSTANCE hInstance);
	void Release();

	void MessageLoop();
	void GameLoop();

	void CreateManager();
	void LoadResources();
	void CreateFileFolder();
	void CreateScene();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};