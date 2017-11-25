#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Player:public Node
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	void moveToRight();
	void moveToLeft();
	void quickMove();
	void logic(float dt);
	void beAtked(int iValue);
	void hurt(int iValue);
	void cure(int iValue);
protected:
private:
	CC_SYNTHESIZE(int, m_iHP, IHP);
};