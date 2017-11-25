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
	/* 实现SimpleMoveListener接口的方法 */
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

