#pragma once

class Tools;

/// <summary>
/// ������ �����ϴ� Player
/// 
/// ���콺�� �̿��Ͽ� ������ �����Ѵ�
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