#include "Player.h"
#include "objectTag.h"

Player::Player()
{

}
Player::~Player(){}
bool Player::init()
{
	auto playerSprite = Sprite::createWithSpriteFrameName("StartRoomMountains_Sprite");
	this->addChild(playerSprite);
	auto body = PhysicsBody::createBox(playerSprite->getContentSize());
	body->setDynamic(true);//动态刚体
	body->setGravityEnable(false);//不受重力影响
	body->getShape(0)->setFriction(0);//设置摩擦力
	//body->getShape(0)->setRestitution(0);//设置弹力
	body->setCategoryBitmask(1);//碰撞检测
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->applyImpulse(Vect(0, -40000));
	this->setTag(Tag_Player);//设置标签
	return true;
}