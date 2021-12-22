#include "pch.h"

#include "JPhysics.h"

JVector JPhysics::CalculatePower(JVector myPos, JVector targetPos, float sumRadius)
{
	CollisionPower = myPos - targetPos;
	//JVector _power = { sumRadius - CollisionPower.x, sumRadius - CollisionPower.y };

	// ���� ���ͷ� ����
	float length = sqrt(CollisionPower.x * CollisionPower.x + CollisionPower.y * CollisionPower.y);
	CollisionPower.x = CollisionPower.x / length * 4;
	CollisionPower.y = CollisionPower.y / length * 4;

	//CollisionPower.x = CollisionPower.x * _power.x;
	//CollisionPower.y = CollisionPower.y * _power.y;

	// ������ ����
	Friction = 1.0f;

	return CollisionPower;
}
