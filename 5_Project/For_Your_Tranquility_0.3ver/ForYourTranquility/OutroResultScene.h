#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class TextBox;

/// <summary>
/// �ƿ�Ʈ�� ��
/// 
/// �ΰ��� ���� ã�� ���ŷ� ���� ����� ������
/// 2021. 02. 08. Hacgeum
/// </summary>
class OutroResultScene : public Scene
{
public:
	OutroResultScene();
	virtual ~OutroResultScene();

private:
	// ���ȭ��
	Object* m_pBackgroundIMG;
	TextBox* m_pTextBox;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};