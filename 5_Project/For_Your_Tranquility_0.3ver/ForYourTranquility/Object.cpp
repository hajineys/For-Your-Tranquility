#include "pch.h"

#include "Object.h"
#include "ColliderBox.h"

Object::Object(UISortLayer layer)
	: m_Transform(nullptr), m_ObjectName(""), m_SpriteIndex(0)
	, m_Layer(layer), m_ColliderBox(nullptr)
{

}

Object::~Object()
{

}

void Object::Initialize(JVector pos, PCWSTR objectName)
{
	m_Transform = new JTransform();

	// Trnasform �ʱ�ȭ
	m_Transform->Pos = pos;

	// ������Ʈ �̸� �ʱ�ȭ
	m_ObjectName = objectName;

	m_ColliderBox = new ColliderBox(pos, objectName);
}

void Object::Release()
{
	if (m_Transform != nullptr)
	{
		delete m_Transform;
		m_Transform = nullptr;
	}

	if (m_ColliderBox != nullptr)
	{
		delete m_ColliderBox;
		m_ColliderBox = nullptr;
	}
}

void Object::Update(float dTime)
{
	// �ڽ��� ������ ��� ������Ʈ
	m_Transform->CenterPos = { (2 * m_Transform->Pos.x + m_Transform->Size.x) / 2, (2 * m_Transform->Pos.y + m_Transform->Size.y) / 2 };

	m_ColliderBox->Update(dTime, m_Transform);
}

void Object::Draw(float opacity/*=1.0f*/)
{
	if (m_SpriteVec.size() > 0)
		JJEngine::GetInstance()->DrawSprite(m_SpriteVec[m_SpriteIndex], m_Transform->Pos.x, m_Transform->Pos.y, opacity);

	ShowDebug();
}

void Object::ShowDebug()
{
	static bool _IsDebugShow = false;

	if (InputManager::GetInstance()->CheckF5ButtonUp())
	{
		if (!_IsDebugShow)
			_IsDebugShow = true;
		else
			_IsDebugShow = false;

		InputManager::GetInstance()->Reset();
	}
		
	if (_IsDebugShow == true)
	{
		// �浹�ڽ� �׸���
		m_ColliderBox->Draw();
	}
	else
		return;
}

void Object::AddSprite(CString additionalName, int frame)
{
	JImage* _newSprite = new JImage(frame);
	
	_newSprite->Bitmap = ResourceManager::GetInstance()->GetMyImage(additionalName);

	if (_newSprite->Bitmap != nullptr)
	{
		m_SpriteVec.push_back(_newSprite);

		// �̹��� ũ�⿡ �°� �浹�ڽ��� �ʱ�ȭ
		m_Transform->Size = { _newSprite->Bitmap->GetSize().width / frame, _newSprite->Bitmap->GetSize().height };
		m_Transform->CenterPos = { (2 * m_Transform->Pos.x + m_Transform->Size.x) / 2, (2 * m_Transform->Pos.y + m_Transform->Size.y) / 2 };
		m_ColliderBox->SetTransform.Pos = { m_Transform->CenterPos.x - m_Transform->Size.x / 2, m_Transform->CenterPos.y - m_Transform->Size.y / 2 };
		m_ColliderBox->SetSize(m_Transform->Size);
	}
}

void Object::NextSprite()
{
	m_SpriteIndex++;

	if (m_SpriteIndex >= m_SpriteVec.size())
		m_SpriteIndex = 0;
}

void Object::ChangeSprite(int frame)
{
	// �� �ִϸ��̼��� �������� �Ѿ�� ���� ��츸 ������ ��ü
	if (frame < m_SpriteVec.size())
		m_SpriteIndex = frame;
}

void Object::NextFrame()
{
	if (m_SpriteVec.size() > 0)
	{
		m_SpriteVec[m_SpriteIndex]->NextFrame();
	}
}

void Object::ChangeFrame(int frame)
{
	if (m_SpriteVec.size() > 0)
	{
		m_SpriteVec[m_SpriteIndex]->ChangeFrame(frame);
	}
}

bool Object::PlayAnimation(float dTime, float speed /*= 1.0f*/)
{
	return m_SpriteVec[m_SpriteIndex]->Play(dTime, speed);
}

bool Object::PlayAndResetAnimation(float dTime, float speed /*= 1.0f*/)
{
	return m_SpriteVec[m_SpriteIndex]->PlayAndReset(dTime, speed);
}

void Object::UpdateAnimation(float dTime, float speed /*= 1.0f*/)
{
	m_SpriteVec[m_SpriteIndex]->Update(dTime, speed);
}

void Object::ResetAnimation()
{
	m_SpriteVec[m_SpriteIndex]->Reset();
}
