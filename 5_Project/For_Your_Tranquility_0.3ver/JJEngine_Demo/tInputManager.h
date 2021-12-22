#pragma once
#include "JTransform.h"

#include <windowsx.h>

/// ���콺 �Է��� �޾ƺ���
// [�ҿ�]�̱������� ������
// 2021.2.8 JJun
class tInputManager
{
private:
	tInputManager();
	~tInputManager();

private:
	static tInputManager* m_pInstance;

	HWND m_hWnd;

	POINT m_MouseScreenPos;							// ��ũ���� ���콺 ��ǥ
	POINT m_MouseClientPos;							// ���α׷��� ���콺 ��ǥ

public:
	bool m_NowMouseLButtonState;
	bool m_PrevMouseLButtonState;

	static tInputManager* GetInstance();
	void DestroyInstance();

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
};