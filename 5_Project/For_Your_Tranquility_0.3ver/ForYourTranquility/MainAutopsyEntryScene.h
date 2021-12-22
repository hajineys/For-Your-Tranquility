#pragma once
#include "Scene.h"

class Button;

/// <summary>
/// ���� �ΰ˽� ���� �� ��
/// 
/// 2021. 02. 18. Hacgeum
/// </summary>
class MainAutopsyEntryScene : public Scene
{
public:
	MainAutopsyEntryScene();
	virtual ~MainAutopsyEntryScene();

private:
	Button* m_pFrog;

public:
	static bool IsFirstPlay;

public:
	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};