#include "pch.h"

#include "tInputManager.h"

tInputManager* tInputManager::m_pInstance = nullptr;

tInputManager::tInputManager()
	:m_NowMouseLButtonState(false), m_PrevMouseLButtonState(false)
{

}

tInputManager::~tInputManager()
{

}

tInputManager* tInputManager::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new tInputManager;
	}

	return m_pInstance;
}

void tInputManager::DestroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void tInputManager::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
}

void tInputManager::Update()
{
	GetCursorPos(&m_MouseScreenPos);
	m_MouseClientPos = m_MouseScreenPos;

	ScreenToClient(m_hWnd, &m_MouseClientPos);

	CheckLeftButtonState();
}

void tInputManager::Reset()
{
	m_PrevMouseLButtonState = false;
	m_NowMouseLButtonState = false;
}

void tInputManager::CheckLeftButtonState()
{
	// 이전 상태값 저장
	m_PrevMouseLButtonState = m_NowMouseLButtonState;

	// 현재 상태 갱신
	m_NowMouseLButtonState = HIWORD(GetAsyncKeyState(VK_LBUTTON));
}

bool tInputManager::CheckLeftButtonNone()
{
	return m_PrevMouseLButtonState == false && m_NowMouseLButtonState == false;
}

bool tInputManager::CheckLeftButtonDown()
{
	return m_PrevMouseLButtonState == false && m_NowMouseLButtonState == true;
}

bool tInputManager::CheckLeftButtonUp()
{
	return m_PrevMouseLButtonState == true && m_NowMouseLButtonState == false;
}

bool tInputManager::CheckLeftButtonHold()
{
	return m_PrevMouseLButtonState == true && m_NowMouseLButtonState == true;
}