#pragma once
#include "Scene.h"

/// <summary>
/// 게임씬 관리 매니저
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
	// 초기화
	void Initialize();
	void Update(float dTime);
	void Render();
	void Release();

	// 씬을 전환하는 스태틱 함수
	// 비정적 클래스를 사용하되, 특정 함수만 전역성을 보장받기 위함.
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
