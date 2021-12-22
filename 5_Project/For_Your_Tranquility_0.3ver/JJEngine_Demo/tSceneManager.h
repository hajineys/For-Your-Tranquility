#pragma once
#include "IScene.h"

/// <summary>
/// ���Ӿ� ���� �Ŵ���
/// 
/// 2021. 02. 06. Hacgeum
/// </summary>
class tSceneManager
{
public:
	tSceneManager();
	~tSceneManager();

public:
	static eSceneStateAll SceneState;
	static IScene* pNowScene;

public:
	// �ʱ�ȭ
	void Initialize();
	void Update(float dTime);
	void Render();
	void Finalize();

	// ���� ��ȯ�ϴ� ����ƽ �Լ�
	// ������ Ŭ������ ����ϵ�, Ư�� �Լ��� �������� ����ޱ� ����.
	static void ChangeScene(eSceneStateAll nextScene);
};