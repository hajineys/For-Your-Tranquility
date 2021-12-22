#pragma once

class Object;

/// <summary>
/// 싱글톤 패턴을 이용한 게임오브젝트 관리 매니저
/// 
/// 2021. 02. 09. Hacgeum
/// </summary>
class ObjectManager
{
private:
	ObjectManager();
	~ObjectManager();

private:
	std::list<Object*> m_ObjectList;

	/// 1. 이게 Scene갯수별로 달라야 한다.
	/// 2. 이것이 Sort의 대상이 된다. 선후관계(depth)는 게임 처음부터 고정적일 수도 있고,
	/// 게임 중간에 바뀔 수도 있다.

public:
	void Initialize();
	void Release();

	// 각 씬에서 생성한 오브젝트를 오브젝트 리스트에 넣는다.
	void AddObject(Object* object);

	void CheckCollision();
	void InputKey();

	void UpdateAll_old(float dTime);
	void DrawAll_old();
};