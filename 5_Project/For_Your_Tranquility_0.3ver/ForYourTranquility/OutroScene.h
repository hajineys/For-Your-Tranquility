#pragma once
#include "IScene.h"

/// <summary>
/// 아웃트로 씬
/// 
/// 결과, 엔딩 씬 존재
/// 2021. 02. 06. Hacgeum
/// </summary>
class OutroScene : public IScene
{
public:
	OutroScene();
	virtual ~OutroScene();

	eSceneStateAll m_OutroState;
	IScene* m_pNowScene;
	IScene* m_pOutroResult;
	IScene* m_pOutroEnding;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};