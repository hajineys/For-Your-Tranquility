#include "pch.h"

#include "InputManager.h"

InputManager* InputManager::m_pInstance = nullptr;

InputManager::InputManager()
	:m_NowMouseLButtonState(false), m_PrevMouseLButtonState(false)
{

}

InputManager::~InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new InputManager;
	}

	return m_pInstance;
}

void InputManager::DestroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void InputManager::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
}

void InputManager::Update()
{
	GetCursorPos(&m_MouseScreenPos);
	m_MouseClientPos = m_MouseScreenPos;

	ScreenToClient(m_hWnd, &m_MouseClientPos);

	CheckLeftButtonState();
}

void InputManager::Reset()
{
	m_PrevMouseLButtonState = false;
	m_NowMouseLButtonState = false;
}

void InputManager::CheckLeftButtonState()
{
	// 이전 상태값 저장
	m_PrevMouseLButtonState = m_NowMouseLButtonState;

	// 현재 상태 갱신
	m_NowMouseLButtonState = HIWORD(GetAsyncKeyState(VK_LBUTTON));
}

bool InputManager::CheckLeftButtonNone()
{
	return m_PrevMouseLButtonState == false && m_NowMouseLButtonState == false;
}

bool InputManager::CheckLeftButtonDown()
{
	return m_PrevMouseLButtonState == false && m_NowMouseLButtonState == true;
}

bool InputManager::CheckLeftButtonUp()
{
	return m_PrevMouseLButtonState == true && m_NowMouseLButtonState == false;
}

bool InputManager::CheckLeftButtonHold()
{
	return m_PrevMouseLButtonState == true && m_NowMouseLButtonState == true;
}