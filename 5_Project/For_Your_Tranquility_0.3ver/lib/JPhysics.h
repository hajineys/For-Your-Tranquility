#pragma once

#include "JTransform.h"

class JPhysics
{
public:
	JVector CollisionPower;
	float Friction;

public:
	JPhysics() : CollisionPower({ 0,0 }), Friction(0) { }
	~JPhysics() { }

public:
	JVector CalculatePower(JVector myPos, JVector targetPos, float sumRadius);
};