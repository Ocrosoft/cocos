#pragma once
#include "cocos2d.h"
#include "ControllerListener.h"
using namespace cocos2d;
class Controller :public Layer
{
public:
	/*���ü�������*/
	void setControllerListener(ControllerListener* m_controllerListener);
protected:
	ControllerListener* m_controllerListener;
};