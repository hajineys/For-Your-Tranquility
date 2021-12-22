#pragma once
#include "Scene.h"

class ObjectManager;
class Object;
class TextBox;

/// <summary>
/// 아웃트로 씬
/// 
/// 부검을 통해 찾은 증거로 재판 결과를 보여줌
/// 2021. 02. 08. Hacgeum
/// </summary>
class OutroResultScene : public Scene
{
public:
	OutroResultScene();
	virtual ~OutroResultScene();

private:
	// 배경화면
	Object* m_pBackgroundIMG;
	TextBox* m_pTextBox;

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;
};