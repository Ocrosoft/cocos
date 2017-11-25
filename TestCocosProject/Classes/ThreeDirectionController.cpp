#include "ThreeDirectionController.h"
bool ThreeDirectionController::init()
{
	this->iXSpeed = 0;
	this->iYSpeed = 0;
	/*触摸监听*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ThreeDirectionController::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ThreeDirectionController::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ThreeDirectionController::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/* 设置允许触屏 */
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
	/* 获取点击的坐标 */
	auto touchLocation = pTouch->getLocationInView();
	touchLocation = Director::getInstance()->convertToGL(touchLocation);
	/* 被控制对象的坐标 */
	auto pos = m_controllerListener->getCurPosition();
	/* 判断是向上移动还是向下移动 */
	int iSpeed = 0;
	/*设置移动的方向和速度*/
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
	/* 停止Y坐标上的移动 */
	setiYSpeed(0);
}