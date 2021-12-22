#pragma once
#include "JTransform.h"

#include <windowsx.h>

/// 마우스 입력을 받아보자
// [소연]싱글톤으로 변경함
// 2021.2.8 JJun
class InputManager
{
private:
	InputManager();
	~InputManager();

private:
	static InputManager* m_pInstance;

	HWND m_hWnd;

	POINT m_MouseScreenPos;							// 스크린상 마우스 좌표
	POINT m_MouseClientPos;							// 프로그램상 마우스 좌표

public:
	bool m_NowMouseLButtonState;
	bool m_PrevMouseLButtonState;

	bool m_NowF5ButtonState;
	bool m_PrevF5ButtonState;

	static InputManager* GetInstance();
	void DeleteInstance();

	// Getter / Setter
public:
	POINT GetMousePos() const { return m_MouseClientPos; }

public:
	void Initialize(HWND hWnd);						// 핸들을 받아야한다.
	void Update();
	void Reset();

	void CheckLeftButtonState();
	bool CheckLeftButtonNone();
	bool CheckLeftButtonDown();
	bool CheckLeftButtonUp();
	bool CheckLeftButtonHold();

	bool CheckF5ButtonUp();
};