#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class ControllerListener
{
public:
	/*��ԭ�治ͬ����������ƶ��ľ���*/
	virtual void setSimplePosition(int x, int xi, int y, int yi) = 0;
	virtual Point getCurPosition() = 0;
};