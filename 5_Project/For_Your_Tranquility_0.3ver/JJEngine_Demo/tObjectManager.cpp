#include "pch.h"

#include "tObjectManager.h"
#include "tGameObject.h"

using namespace std;

tObjectManager::tObjectManager()
{

}

tObjectManager::~tObjectManager()
{

}

void tObjectManager::Initialize()
{

}

void tObjectManager::Release()
{

}

void tObjectManager::AddObject(tObject* object)
{
	/*object->m_la*/
	// 레이어 정보 어디갔어..
	m_ObjectList.push_back(object);
}

void tObjectManager::UpdateAll_old(float dTime)
{
// 	// 오브젝트 리스트를 순회하면서 Update 시킨다.
// 	list<GameObject*>::iterator iter;
// 
// 	// m_ListObject의 배열을 돌며 각 Layer의 Object들을 Update한다
// 	for (int i = 0; i < static_cast<int>(UISortLayer::ENDLAYER); i++)
// 	{
// 		for (iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end(); iter++)
// 		{
// 			(*iter)->Update(dTime);
// 		}
// 	}
}

void tObjectManager::DrawAll_old()
{
// 	// 오브젝트 리스트를 순회하면서 Draw 시킨다.
// 	list<GameObject*>::iterator iter;
// 
// 	// m_ListObject의 배열을 돌며 각 Layer의 Object들을 Render한다
// 	for (int i = 0; i < static_cast<int>(UISortLayer::ENDLAYER); i++)
// 	{
// 		for (iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end(); iter++)
// 		{
// 			//(*iter)->Draw(JJEngine::GetInstance());
// 		}
// 	}
}

void tObjectManager::CheckCollision()
{

}

void tObjectManager::InputKey()
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