#pragma once

class Tools;

/// <summary>
/// 유저가 조종하는 Player
/// 
/// 마우스를 이용하여 게임을 진행한다
/// 2021. 02. 14 Hacgeum
/// </summary>
class Player
{
public:
	Player();
	~Player();

private:
	Tools* m_pTools;

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};