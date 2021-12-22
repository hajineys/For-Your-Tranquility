#pragma once
#include "Scene.h"

/// <summary>
/// ���Ӿ� ���� �Ŵ���
/// 
/// 2021. 02. 06. Hacgeum
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	static eSceneStateAll SceneState;
	static Scene* pNowScene;

public:
	// �ʱ�ȭ
	void Initialize();
	void Update(float dTime);
	void Render();
	void Release();

	// ���� ��ȯ�ϴ� ����ƽ �Լ�
	// ������ Ŭ������ ����ϵ�, Ư�� �Լ��� �������� ����ޱ� ����.
	static void ChangeScene(eSceneStateAll nextScene);

public:
	// FadeInFadeOut
	static float Opacity;
	static float FadeInFadeOutTime;
	static bool IsFadeInEnd;
	static bool IsFadeOutEnd;
	static bool IsSceneEnd;

	static ID2D1Bitmap* BlackScreen;

	static void FadeIn(float dTime);
	static void FadeOut(float dTime);

	static void DrawBlackScreen();
};
