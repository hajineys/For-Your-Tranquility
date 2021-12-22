#pragma once

class Object;

/// <summary>
/// �̱��� ������ �̿��� ���ӿ�����Ʈ ���� �Ŵ���
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

	/// 1. �̰� Scene�������� �޶�� �Ѵ�.
	/// 2. �̰��� Sort�� ����� �ȴ�. ���İ���(depth)�� ���� ó������ �������� ���� �ְ�,
	/// ���� �߰��� �ٲ� ���� �ִ�.

public:
	void Initialize();
	void Release();

	// �� ������ ������ ������Ʈ�� ������Ʈ ����Ʈ�� �ִ´�.
	void AddObject(Object* object);

	void CheckCollision();
	void InputKey();

	void UpdateAll_old(float dTime);
	void DrawAll_old();
};