#pragma once
#include "Object.h"

class Object;
class GameObject;
class Button;
class TextBox;

/// <summary>
/// 싱글톤 패턴을 이용한 게임오브젝트 관리 매니저
/// 
/// 2021. 02. 09. Hacgeum
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

private:
	list<Object*> m_ObjectList;
	list<Object*> m_NotDrawUpdateObjectList;
	/// 1. 이게 Scene갯수별로 달라야 한다.
	/// 2. 이것이 Sort의 대상이 된다. 선후관계(depth)는 게임 처음부터 고정적일 수도 있고,
	/// 게임 중간에 바뀔 수도 있다.

public:
	void Initialize();
	void Release();

	Object* OnlyCreateObject_Image(JVector pos, std::wstring name, int frame, UISortLayer layer);
	GameObject* OnlyCreateObject_Animation(JVector pos, std::wstring name, UISortLayer layer);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eNowSceneState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eFirstChoiceState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eSecondChoiceState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eThirdChoiceState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eNowSceneState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eFirstChoiceState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eSecondChoiceState state);
	Button* OnlyCreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eThirdChoiceState state);
	TextBox* OnlyCreateObject_TextBox(JVector pos, std::wstring name, UISortLayer layer);

	// 오브젝트를 생성하고 리스트에 넣는다.
	Object* CreateObject_Image(JVector pos, std::wstring name, int frame, UISortLayer layer);
	GameObject* CreateObject_Animation(JVector pos, std::wstring name, UISortLayer layer);
	Button* CreateObject_Button(JVector pos, std::wstring name, JVector colliderSize, UISortLayer layer, eNowSceneState state);
	Button* CreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer);
	Button* CreateObject_Button(JVector pos, std::wstring name, int frame, UISortLayer layer, eNowSceneState state);
	TextBox* CreateObject_TextBox(JVector pos, std::wstring name, UISortLayer layer);

	void UpdateAll(float dTime);
	void DrawAll();

public:
	void CheckButtonClicked(Scene* nowScene);
};