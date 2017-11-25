#pragma once
#include "cocos2d.h"
#include "Controller.h"
using namespace cocos2d;
class ThreeDirectionController : public Controller
{
public:
	CREATE_FUNC(ThreeDirectionController);
	virtual bool init();
	virtual void update(float dt);
	/* 触屏事件 */
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	/* 设置X方向的移动速度 */
	void setiXSpeed(int iSpeed);
	/* 设置Y方向的移动速度*/
	void setiYSpeed(int iSpeed);
private:
	int iXSpeed;
	int iYSpeed;
};