#pragma once
#include "Scene.h"

class Object;
class ObjectManager;
class ColliderBox;

/// <summary>
/// 아웃트로 씬
/// 
/// 엔딩 애니메이션 씬
/// 2021. 02. 08. Hacgeum
/// </summary>
class OutroEndingScene : public Scene
{
public:
	OutroEndingScene();
	virtual ~OutroEndingScene();

	Object* m_pBackgroundIMG;
	Object* m_pFileIMG;
	Object* m_pThankyou;
	
	Button* m_pGoTitle;
	Button* m_pExitGame;

	wstring m_FirstChoiceStr;
	wstring m_SecondChoiceStr;
	wstring m_ThirdChoiceStr;

	static bool m_IsFirst;
	static bool m_IsFirstPlay[2];

public:
	// Scene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update(float dTime) override;
	virtual void Draw() override;
	virtual void ShowDebug() override;
	virtual void Release() override;

	// static 변수 초기화
	void AllStaticFinalize();
};