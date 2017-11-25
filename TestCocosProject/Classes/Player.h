#pragma once
#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;
class Player : public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	bool initWithTiledMap(TMXTiledMap* map);
	static Player* createWithTiledMap(TMXTiledMap* map);
	void run();
	void setViewPointByPlayer();
	/* 重写父类的函数 */
	virtual void setSimplePosition(int x, int xi, int y, int yi);
private:
	bool checkCollidable(int x, int y);
};

