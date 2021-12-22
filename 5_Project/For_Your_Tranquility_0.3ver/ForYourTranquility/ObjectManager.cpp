#include "pch.h"

#include "ObjectManager.h"
#include "GameObject.h"
#include "Button.h"
#include "ColliderBox.h"
#include "TextBox.h"

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
	// 리스트를 비워준다.
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end(); it++)
	{
		Object* _deleteObject = *it;

		_deleteObject->Release();

		delete _deleteObject;
		_deleteObject = nullptr;
	}

	// 리스트2를 비워준다.
	for (auto it = m_NotDrawUpdateObjectList.begin(); it != m_NotDrawUpdateObjectList.end(); it++)
	{
		Object* _deleteObject = *it;

		_deleteObject->Release();

		delete _deleteObject;
		_deleteObject = nullptr;
	}

	m_ObjectList.clear();
	m_NotDrawUpdateObjectList.clear();
}

Object* ObjectManager::OnlyCreateObject_Image(JVector pos, std::wstring name, int frame, UISortLayer layer)
{
	Object* _newObject = new Object(layer);
	_newObject->Initialize(pos, name.c_str());
	_newObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newObject);

	return _newObject;
}

GameObject* ObjectManager::OnlyCreateObject_Animation(JVector pos, std::wstring name, UISortLayer layer)
{
	GameObject* _newGameObject = new GameObject(layer);
	_newGameObject->Initialize(pos, name.c_str());
	_newGameObject->SetSpriteSheet(name.c_str());

	m_NotDrawUpdateObjectList.push_back(_newGameObject);

	return _newGameObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eNowSceneState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->Transform()->Size = colliderSize;
	_newButtonObject->GetColliderBox()->SetSize(colliderSize);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer)
{
	Button* _newButtonObject = new Button(layer);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eNowSceneState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eFirstChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eSecondChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eThirdChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eFirstChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->Transform()->Size = colliderSize;
	_newButtonObject->GetColliderBox()->SetSize(colliderSize);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eSecondChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->Transform()->Size = colliderSize;
	_newButtonObject->GetColliderBox()->SetSize(colliderSize);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

Button* ObjectManager::OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eThirdChoiceState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->Transform()->Size = colliderSize;
	_newButtonObject->GetColliderBox()->SetSize(colliderSize);

	m_NotDrawUpdateObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

TextBox* ObjectManager::OnlyCreateObject_TextBox(JVector pos, std::wstring name, UISortLayer layer)
{
	TextBox* _newTextBox = new TextBox(layer);
	_newTextBox->Initialize(pos, name.c_str());

	m_NotDrawUpdateObjectList.push_back(_newTextBox);

	return _newTextBox;
}

// 오브젝트 하나를 생성해서, 돌려준다. 내부적으로 리스트로 가지고 있다.
Object* ObjectManager::CreateObject_Image(JVector pos, std::wstring name, int frame, UISortLayer layer)
{
	Object* _newObject = new Object(layer);
	_newObject->Initialize(pos, name.c_str());
	_newObject->AddSprite(name.c_str(), frame);
	m_ObjectList.push_back(_newObject);

	return _newObject;
}

GameObject* ObjectManager::CreateObject_Animation(JVector pos, std::wstring name, UISortLayer layer)
{
	GameObject* _newGameObject = new GameObject(layer);
	_newGameObject->Initialize(pos, name.c_str());
	_newGameObject->SetSpriteSheet(name.c_str());

	m_ObjectList.push_back(_newGameObject);

	return _newGameObject;
}

Button* ObjectManager::CreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eNowSceneState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->Transform()->Size = colliderSize;
	_newButtonObject->GetColliderBox()->SetSize(colliderSize);
	m_ObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

// 부모를 상속받은 자식 오브젝트 계층도를 다 받되, 부모 포인터로 돌려준다.
Button* ObjectManager::CreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer)
{
	Button* _newButtonObject = new Button(layer);
	_newButtonObject->Initialize(pos, name.c_str());

	m_ObjectList.push_back(_newButtonObject);

	return _newButtonObject;
}

// 부모를 상속받은 자식 오브젝트 계층도를 다 받되, 부모 포인터로 돌려준다.
Button* ObjectManager::CreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eNowSceneState state)
{
	Button* _newButtonObject = new Button(layer, state);
	_newButtonObject->Initialize(pos, name.c_str());
	_newButtonObject->AddSprite(name.c_str(), frame);

	m_ObjectList.push_back(_newButtonObject);

	// 다형성 사용을 염두에 두었음..
	return _newButtonObject;
}

TextBox* ObjectManager::CreateObject_TextBox(JVector pos, std::wstring name, UISortLayer layer)
{
	TextBox* _newTextBox = new TextBox(layer);
	_newTextBox->Initialize(pos, name.c_str());
	_newTextBox->AddSprite(name.c_str(), 1);

	m_ObjectList.push_back(_newTextBox);

	return _newTextBox;
}

void ObjectManager::UpdateAll(float dTime)
{
	// C++ 11
	for (Object* _object : m_ObjectList)
	{
		_object->Update(dTime);
	}
}

bool IsLessThan(const Object* a, const Object* b)
{
	return a->GetLayer() < b->GetLayer();
}

void ObjectManager::DrawAll()
{
	// Layer별로 정렬한다. (오름차순)
	m_ObjectList.sort(IsLessThan);

	for (Object* _object : m_ObjectList)
	{
		_object->Draw();
	}
}

void ObjectManager::CheckButtonClicked(Scene* nowScene)
{
	for (Object* _object : m_ObjectList)
	{
		// 버튼일 경우만 클릭을 체크
		Button* _nowButtonObject = dynamic_cast<Button*>(_object);

		if (_nowButtonObject != nullptr)
		{
			if (_nowButtonObject->GetColliderBox()->CheckClicked())
				nowScene->SetNowSceneState(_nowButtonObject->GetStateForClicked());
		}
	}
}