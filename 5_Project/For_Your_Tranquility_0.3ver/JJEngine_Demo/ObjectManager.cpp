#include "pch.h"

#include "ObjectManager.h"
#include "GameObject.h"

using namespace std;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Initialize()
{

}

void ObjectManager::Release()
{

}

void ObjectManager::AddObject(Object* object)
{
	/*object->m_la*/
	// ���̾� ���� ��𰬾�..
	m_ObjectList.push_back(object);
}

void ObjectManager::UpdateAll_old(float dTime)
{
// 	// ������Ʈ ����Ʈ�� ��ȸ�ϸ鼭 Update ��Ų��.
// 	list<GameObject*>::iterator iter;
// 
// 	// m_ListObject�� �迭�� ���� �� Layer�� Object���� Update�Ѵ�
// 	for (int i = 0; i < static_cast<int>(UISortLayer::ENDLAYER); i++)
// 	{
// 		for (iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end(); iter++)
// 		{
// 			(*iter)->Update(dTime);
// 		}
// 	}
}

void ObjectManager::DrawAll_old()
{
// 	// ������Ʈ ����Ʈ�� ��ȸ�ϸ鼭 Draw ��Ų��.
// 	list<GameObject*>::iterator iter;
// 
// 	// m_ListObject�� �迭�� ���� �� Layer�� Object���� Render�Ѵ�
// 	for (int i = 0; i < static_cast<int>(UISortLayer::ENDLAYER); i++)
// 	{
// 		for (iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end(); iter++)
// 		{
// 			//(*iter)->Draw(JJEngine::GetInstance());
// 		}
// 	}
}

void ObjectManager::CheckCollision()
{

}

void ObjectManager::InputKey()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{

	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{

	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{

	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{

	}
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{

	}
}