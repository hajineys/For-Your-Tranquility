#pragma once

class tObject;

/// <summary>
/// �̱��� ������ �̿��� ���ӿ�����Ʈ ���� �Ŵ���
/// 
/// 2021. 02. 09. Hacgeum
/// </summary>
class tObjectManager
{
private:
	tObjectManager();
	~tObjectManager();

private:
	std::list<tObject*> m_ObjectList;

	/// 1. �̰� Scene�������� �޶�� �Ѵ�.
	/// 2. �̰��� Sort�� ����� �ȴ�. ���İ���(depth)�� ���� ó������ �������� ���� �ְ�,
	/// ���� �߰��� �ٲ� ���� �ִ�.

public:
	void Initialize();
	void Release();

	// �� ������ ������ ������Ʈ�� ������Ʈ ����Ʈ�� �ִ´�.
	void AddObject(tObject* object);

	void CheckCollision();
	void InputKey();

	void UpdateAll_old(float dTime);
	void DrawAll_old();
};