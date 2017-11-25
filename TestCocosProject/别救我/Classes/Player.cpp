#include "Player.h"
#include "objectTag.h"
Player::Player()
{
	m_iHP = 100;
}
Player::~Player() {}
bool Player::init()
{
	auto playerSp = Sprite::create("player.png");
	this->addChild(playerSp);
	//用圆形刚体设置碰撞
	auto body = PhysicsBody::createCircle(playerSp->getContentSize().width*0.4f);
	body->getShape(0)->setFriction(0);//获取皮肤,设置摩擦力
	body->getShape(0)->setRestitution(1.0f);//获取皮肤并设置弹力
	body->setCategoryBitmask(1);//碰撞检测
	body->setCollisionBitmask(1); 
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
	//施加向下的推力
	this->getPhysicsBody()->applyImpulse(Vect(0, -40000));
	//设置Tag
	this->setTag(ObjectTag_Player);
	return true;
}
void Player::logic(float dt)
{

}
void Player::moveToRight()
{
	this->getPhysicsBody()->applyImpulse(Vect(50000, 0));
}
void Player::moveToLeft()
{
	this->getPhysicsBody()->applyImpulse(Vect(-50000, 0));
}
void Player::quickMove()
{
	this->getPhysicsBody()->applyImpulse(Vect(0, -200000));
}
void Player::beAtked(int iValue)
{
	if (iValue < 0) cure(-iValue);
	else hurt(std::abs(iValue));
}
void Player::hurt(int iValue)
{
	setIHP(getIHP() - iValue);
}
void Player::cure(int iValue)
{
	setIHP(getIHP() + iValue);
}