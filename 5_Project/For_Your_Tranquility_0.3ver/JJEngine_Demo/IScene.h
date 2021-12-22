#pragma once

enum class eSceneStateAll
{
	INTRO_TITLE,
	INTRO_ANIMATION,
	MAIN_OFFICE,
	MAIN_AUTOPSY,
	MAIN_DISSECTING,
	OUTRO_RESULT,
	OUTRO_ENDING
};

/// <summary>
/// �� �������̽�
/// 
/// �� ���� ���� �θ� �߻� Ŭ����
/// 2021. 02. 06. Hacgeum
/// </summary>
class IScene /*abstract*/
{
public:
	// �ʱ�ȭ
	virtual void Initialize() abstract;
	virtual void Update(float dTime) abstract;
	virtual void Render() abstract;
	virtual void ShowDebug() abstract;
	virtual void Finalize() abstract;
};