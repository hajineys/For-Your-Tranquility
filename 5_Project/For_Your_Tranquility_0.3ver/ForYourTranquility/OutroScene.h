#pragma once
#include "IScene.h"

/// <summary>
/// �ƿ�Ʈ�� ��
/// 
/// ���, ���� �� ����
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
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};