#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ControllerListener
{
public:
	/*与原版不同的是添加了移动的距离*/
	virtual void setSimplePosition(int x, int xi, int y, int yi) = 0;
	virtual Point getCurPosition() = 0;
};