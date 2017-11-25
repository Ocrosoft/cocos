#include "SimpleMoveControll.h"

bool SimpleMoveControll::init()
{
	this->iSpeed = 0;
	/* ÿһ֡��Ҫ����update����������Ҫ�������� */
	this->scheduleUpdate();
	return true;
}
void SimpleMoveControll::update(float dt)
{
	if (m_controllerListener == NULL) return;
	Point pos = m_controllerListener->getCurPosition();
	//pos.x += iSpeed;
	m_controllerListener->setSimplePosition(pos.x, iSpeed, pos.y, 0);
}
void SimpleMoveControll::setiSpeed(int iSpeed)
{
	this->iSpeed = iSpeed;
}