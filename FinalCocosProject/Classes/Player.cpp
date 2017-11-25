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
	body->setDynamic(true);//��̬����
	body->setGravityEnable(false);//��������Ӱ��
	body->getShape(0)->setFriction(0);//����Ħ����
	//body->getShape(0)->setRestitution(0);//���õ���
	body->setCategoryBitmask(1);//��ײ���
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	this->setPhysicsBody(body);
	this->getPhysicsBody()->applyImpulse(Vect(0, -40000));
	this->setTag(Tag_Player);//���ñ�ǩ
	return true;
}