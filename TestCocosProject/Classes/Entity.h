#pragma once
#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"
using namespace cocos2d;
class Entity : public Node, public ControllerListener
{
public:
	void setSprite(Sprite* sprite);
	void setController(Controller* controller);
	/* ʵ��SimpleMoveListener�ӿڵķ��� */
	virtual void setSimplePosition(int x, int xi, int y, int yi);
	virtual Point getCurPosition();
protected:
	Sprite*  m_sprite;
	Controller* m_Controller;
	TMXTiledMap* map;
	TMXLayer* meta;
	TMXLayer* barrier;
	TMXLayer* win;
	Point tileCoordForPosition(Point pos);
};

