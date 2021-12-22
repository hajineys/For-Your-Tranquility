#pragma once
#include "IScene.h"

class ObjectManager;
class GameObject;
class Object;
class TextBox;

/// <summary>
/// 타이틀 씬
/// 
/// 타이틀, 게임시작, 게임종료 등 선택지 존재
/// 2021. 02. 08. Hacgeum
/// </summary>
class IntroTitleScene : public IScene
{
public:
	IntroTitleScene();
	~IntroTitleScene();

private:
	ObjectManager* m_pObjectManager;

	// 테스트용 게임오브젝트
	GameObject* Character;
	Object* testObject;
	TextBox* textBox;

	GameObject* testGameObject;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Render() override;
	virtual void ShowDebug() override;
	virtual void Finalize() override;
};