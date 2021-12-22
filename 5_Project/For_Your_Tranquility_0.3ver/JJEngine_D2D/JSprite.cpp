#include "pch.h"

#include "JSprite.h"

JSprite::JSprite()
	:DrawPoint(0), Width(0), Height(0), Pivot(0), CancelRect({ 0,0,0,0 }), RectPos({ 0,0,0,0 })
	, Pivot2(0)
{

}

JSprite::~JSprite()
{

}