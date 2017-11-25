#pragma once
#include "cocos2d.h"
#include "Controller.h"
using namespace cocos2d;
class SimpleMoveControll :public Controller
{
public:
	CREATE_FUNC(SimpleMoveControll);
	virtual bool init();
	virtual void update(float dt);
	/*设置移动速度*/
	void setiSpeed(int iSpeed);
private:
	int iSpeed;
};