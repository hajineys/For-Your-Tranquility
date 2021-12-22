#pragma once
#include "IScene.h"

/// <summary>
/// 메인게임 씬
/// 
/// 사무실(시체 정보 확인), 부검실, 결과 도출 씬에 존재
/// 2021. 02. 06. Hacgeum
/// </summary>
class MainGameScene : public IScene
{
public:
	MainGameScene();
	virtual ~MainGameScene();

	eSceneStateAll m_MainGameState;
	IScene* m_pNowScene;
	IScene* m_pMainOffice;
	IScene* m_pMainAutopsyRoom;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};