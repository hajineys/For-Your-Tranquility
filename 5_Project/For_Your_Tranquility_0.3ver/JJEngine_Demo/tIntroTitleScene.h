#pragma once
#include "IScene.h"

class tObjectManager;
class tGameObject;
class tObject;
class tTextBox;

/// <summary>
/// 타이틀 씬
/// 
/// 타이틀, 게임시작, 게임종료 등 선택지 존재
/// 2021. 02. 08. Hacgeum
/// </summary>
class tIntroTitleScene : public IScene
{
public:
	tIntroTitleScene();
	~tIntroTitleScene();

private:
	tObjectManager* m_pObjectManager;

	// 테스트용 게임오브젝트
	tGameObject* Character;
	tObject* testObject;
	tTextBox* textBox;

	tGameObject* testGameObject;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Render() override;
	virtual void ShowDebug() override;
	virtual void Finalize() override;
};