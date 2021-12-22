#pragma once
#include "IScene.h"

/// <summary>
/// 게임씬 관리 매니저
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
	// 초기화
	void Initialize();
	void Update(float dTime);
	void Render();
	void Finalize();

	// 씬을 전환하는 스태틱 함수
	// 비정적 클래스를 사용하되, 특정 함수만 전역성을 보장받기 위함.
	static void ChangeScene(eSceneStateAll nextScene);
};