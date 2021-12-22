#include "pch.h"

#include "GameObject.h"
#include "ResourceManager.h"

GameObject::GameObject()
	: m_SpriteSheet(nullptr)
	,m_MotionCount(0), m_MotionIndex(0)
{
	
}

GameObject::~GameObject()
{

}

void GameObject::Initialize(JVector pos, PCWSTR objectName)
{
	Object::Initialize(pos, objectName);

	// �ִϸ��̼� ���� �ʱ�ȭ
	ResourceManager::GetInstance()->LoadMotionDataFile(m_ObjectName, m_MotionVec);

	// �ʱ� �ִϸ��̼� ����
	m_MotionCount = m_MotionVec.size();

	// MotionVec �����Ͱ� ���� ��� �ִϸ��̼� O, ���� ��� �ִϸ��̼� X
	if (m_MotionCount > 0)
	{
		m_NowMotion = m_MotionVec[m_MotionIndex];
	}
}

void GameObject::Release()
{
	Object::Release();
}

void GameObject::Update(float dTime)
{
	// ���� ����� �����ΰ�?
	m_NowMotion = m_MotionVec[m_MotionIndex];
}

void GameObject::Draw(float opacity/*=1.0f*/)
{
	JJEngine::GetInstance()->DrawSprite(m_SpriteSheet, m_NowMotion, m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void GameObject::ShowDebug()
{
	JJEngine::GetInstance()->DrawText(0, 800, L"x : %f", m_Transform->Pos.x);
	JJEngine::GetInstance()->DrawText(0, 840, L"y : %f", m_Transform->Pos.y);

	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 10, L"DrawIndex : %d", m_NowMotion->DrawIndex);
	JJEngine::GetInstance()->DrawText(m_Transform->Pos.x, m_Transform->Pos.y - 30, L"NowMotionFrame : %d", m_NowMotion->Frame);
}

void GameObject::UpdateAnimation(float dTime, float speed)
{
	// ��� ������Ʈ
	m_NowMotion->Update(dTime, speed);
}

void GameObject::PlayAnimation(float dTime, float speed)
{
	m_NowMotion->Play(dTime, speed);
}

void GameObject::SetSpriteSheet(PCWSTR uri)
{
	JJEngine::GetInstance()->LoadBitmapFromFile(uri, 0, 0, &m_SpriteSheet);
}

void GameObject::SetMotion()
{
	m_MotionIndex++;

	if (m_MotionIndex >= m_MotionCount)
	{
		m_MotionIndex = 0;
	}

	m_NowMotion = m_MotionVec[m_MotionIndex];
	m_NowMotion->Reset();
}

void GameObject::NextMotionFrame()
{
	m_NowMotion->NextMotionFrame();
}

void GameObject::ChangeMotionFrame(int frame)
{
	m_NowMotion->ChangeMotionFrame(frame);
}
