#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class ColliderBox;

/// <summary>
/// ���ΰ��� ��
/// 
/// ��� ���� : ��ü ���� �� ��ǿ� ���� ���� Ȯ�ΰ���
/// 2021. 02. 19. �ձ���
/// </summary>
class	MainIncidentScene : public Scene
{
public:
	MainIncidentScene();
	virtual ~MainIncidentScene();

private:
	// ��� ����
	// �׾��ִ� ������̵� ���� ���̶�����
	Button* m_pPolaroidDeadBtnOn;
	// ���� ������̵� ���� ���̶�����
	Button* m_pPolaroidShelterBtnOn;
	// �Ź� ������̵� ���� ���̶�����
	Button* m_pPolaroidShoesBtnOn;
	// ���� ������̵� ���� ���̶�����
	Button* m_pPolaroidSojuBtnOn;
	// �� �̹��� ���̶�����
	Button* m_pMapBtnOn;

	// �˾�
	Button* m_pPolaroidDeadBtn;
	Button* m_pPolaroidShelterBtn;
	Button* m_pPolaroidShoesBtn;
	Button* m_pPolaroidSojuBtn;
	Button* m_pMapBtn;
	
public:
	// ����
	static bool IsPlaying[5];

public:
	// Scene ��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};