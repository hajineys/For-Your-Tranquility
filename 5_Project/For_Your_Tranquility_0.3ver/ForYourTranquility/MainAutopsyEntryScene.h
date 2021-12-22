#pragma once
#include "Scene.h"

class Button;

/// <summary>
/// 메인 부검실 들어가기 전 씬
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
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};