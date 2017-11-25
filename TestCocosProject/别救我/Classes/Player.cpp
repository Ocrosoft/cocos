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
	//��Բ�θ���������ײ
	auto body = PhysicsBody::createCircle(playerSp->getContentSize().width*0.4f);
	body->getShape(0)->setFriction(0);//��ȡƤ��,����Ħ����
	body->getShape(0)->setRestitution(1.0f);//��ȡƤ�������õ���
	body->setCategoryBitmask(1);//��ײ���
	body->setCollisionBitmask(1); 
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
	//ʩ�����µ�����
	this->getPhysicsBody()->applyImpulse(Vect(0, -40000));
	//����Tag
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