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
	/* �����¼� */
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	/* ����X������ƶ��ٶ� */
	void setiXSpeed(int iSpeed);
	/* ����Y������ƶ��ٶ�*/
	void setiYSpeed(int iSpeed);
private:
	int iXSpeed;
	int iYSpeed;
};