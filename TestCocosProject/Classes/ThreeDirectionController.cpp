#include "ThreeDirectionController.h"
bool ThreeDirectionController::init()
{
	this->iXSpeed = 0;
	this->iYSpeed = 0;
	/*��������*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ThreeDirectionController::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ThreeDirectionController::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ThreeDirectionController::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/* ���������� */
	//this->setTouchEnabled(true);
	this->scheduleUpdate();
	return true;
}
void ThreeDirectionController::update(float dt)
{
	if (m_controllerListener == NULL) return;
	Point curPos = m_controllerListener->getCurPosition();
	//curPos.x += iXSpeed;
	//curPos.y += iYSpeed;
	m_controllerListener->setSimplePosition(curPos.x, iXSpeed, curPos.y, iYSpeed);
}
void ThreeDirectionController::setiXSpeed(int iSpeed)
{
	this->iXSpeed = iSpeed;
}
void ThreeDirectionController::setiYSpeed(int iSpeed)
{
	this->iYSpeed = iSpeed;
}
bool ThreeDirectionController::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}
void ThreeDirectionController::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	/* ��ȡ��������� */
	auto touchLocation = pTouch->getLocationInView();
	touchLocation = Director::getInstance()->convertToGL(touchLocation);
	/* �����ƶ�������� */
	auto pos = m_controllerListener->getCurPosition();
	/* �ж��������ƶ����������ƶ� */
	int iSpeed = 0;
	/*�����ƶ��ķ�����ٶ�*/
	if (touchLocation.y > pos.y)
	{
		iSpeed = 2;
	}
	else
	{
		iSpeed = -2;
	}
	setiYSpeed(iSpeed);
}
void ThreeDirectionController::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	/* ֹͣY�����ϵ��ƶ� */
	setiYSpeed(0);
}