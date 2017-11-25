#pragma  once
#include "cocos2d.h"
USING_NS_CC;

class Player :public Node
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
};