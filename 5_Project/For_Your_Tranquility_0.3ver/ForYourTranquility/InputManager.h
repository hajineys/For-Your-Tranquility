#pragma once
#include "JTransform.h"

#include <windowsx.h>

/// ���콺 �Է��� �޾ƺ���
// [�ҿ�]�̱������� ������
// 2021.2.8 JJun
class InputManager
{
private:
	InputManager();
	~InputManager();

private:
	static InputManager* m_pInstance;

	HWND m_hWnd;

	POINT m_MouseScreenPos;							// ��ũ���� ���콺 ��ǥ
	POINT m_MouseClientPos;							// ���α׷��� ���콺 ��ǥ

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
	void Initialize(HWND hWnd);						// �ڵ��� �޾ƾ��Ѵ�.
	void Update();
	void Reset();

	void CheckLeftButtonState();
	bool CheckLeftButtonNone();
	bool CheckLeftButtonDown();
	bool CheckLeftButtonUp();
	bool CheckLeftButtonHold();

	bool CheckF5ButtonUp();
};