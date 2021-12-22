#pragma once
#include "IScene.h"

/// <summary>
/// ���ΰ��� ��
/// 
/// �繫��(��ü ���� Ȯ��), �ΰ˽�, ��� ���� ���� ����
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
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize(JJEngine* pJJEngine) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;
};