#include "Player.h"
#include "TollgateScene.h"
#include "SimpleAudioEngine.h"
#include "objectTag.h"

#define  tag_armature 1
#define  tag_shape 2

using namespace CocosDenshion;

Player::Player() {}
Player::~Player() {}
bool Player::init()
{
	m_armature = Armature::create("FinalAnimation");
	m_armature->getAnimation()->playByIndex(Idle, -1, 1);
	m_armature->setAnchorPoint(Vec2(0, 0));
	m_armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Player::attackEnd));
	m_armature->setTag(tag_armature);
	auto contentSize = m_armature->getContentSize();
	m_armature->setPosition(Vec2(0 - contentSize.width / 4, -contentSize.height / 2));
	this->addChild(m_armature);

	//auto body = PhysicsBody::createBox(Size(contentSize.width / 2, contentSize.height));
	auto body = PhysicsBody::createBox(Size(contentSize.width / 2, contentSize.height), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	m_height = contentSize.height;
	//body->setGravityEnable(false);//��������Ӱ��
	body->setRotationEnable(false);//��ֹ��ת
	body->setCategoryBitmask(Mask_Player);//��ײ���
	body->setCollisionBitmask(Mask_Player);
	body->setContactTestBitmask(Mask_Player);
	body->getShape(0)->setTag(tag_shape);
	this->setPhysicsBody(body);
	this->setTag(Tag_Player);//���ñ�ǩ
	//this->getPhysicsBody()->applyImpulse(Vec2(0, -40000));
	physicsBody = this->getPhysicsBody();
	return true;
}
void Player::jump()
{
	if (m_action == Idle || m_action == Walking)
	{
		changeArmature(Jumping);
		m_action = Jumping;
		auto seq = Sequence::create(MoveBy::create(0.5f, Vec2(0, 200)) , CallFunc::create(CC_CALLBACK_0(Player::fall, this)), NULL);
		this->runAction(seq);
	}
}
void Player::moveToLeft()
{
	if (m_face == face_right)turnTo(face_left);
	if (m_action == Falling || m_action == Jumping || m_action == Walking || m_action == Attacking) {}
	else
	{
		changeArmature(Walking);
		m_action = Walking;//����ʱֻ�����ƶ������ı�״̬
	}
	auto moveBy = MoveBy::create(0.1, Vec2(-10, 0));
	this->runAction(moveBy);
}
void Player::moveToRight()
{
	if (m_face == face_left)turnTo(face_right);
	if (m_action == Falling || m_action == Jumping || m_action == Walking || m_action == Attacking) {}
	else
	{
		changeArmature(Walking);
		m_action = Walking;
	}
	auto moveBy = MoveBy::create(0.1, Vec2(10, 0));
	this->runAction(moveBy);
}
int Player::getStatu()
{
	return m_action;
}
int Player::getFace()
{
	return m_face;
}
bool Player::turnTo(int newFace)
{
	if (newFace != 0 && newFace != 1)return false;
	m_face = newFace;
	this->setScaleX(m_face == face_right ? 1 : -1);
	return true;
}
void Player::setIdle()
{
	changeArmature(Idle);
	m_action = Idle;
}
void Player::changeArmature(int type)
{
	//CCLOG("%d", m_action);
	//this->removeChildByTag(1);
	switch (type)
	{
	case Idle:
		m_armature->getAnimation()->playByIndex(Idle, -1, 1);
		break;
	case Walking:
		m_armature->getAnimation()->playByIndex(Walking, -1, 1);
		break;
	case Jumping:
		m_armature->getAnimation()->playByIndex(Jumping, -1, 1);
		break;
	case Falling:
		m_armature->getAnimation()->playByIndex(Falling, -1, 1);
		break;
	case Attacking:
		m_armature->getAnimation()->playByIndex(Attacking, -1, 0);
		break;
	}
	m_armature->setAnchorPoint(Vec2(0, 0));
	auto contentSize = m_armature->getContentSize();
	m_armature->setPosition(Vec2(0 - contentSize.width / 4, -contentSize.height / 2));
	m_armature->setTag(tag_armature);
	this->addChild(m_armature);
	m_armature = (Armature*)this->getChildByTag(tag_armature);

	physicsBody->removeShape(tag_shape);
	//auto body = PhysicsBody::createBox(Size(contentSize.width / 2, contentSize.height));
	auto body = PhysicsBody::createBox(Size(contentSize.width / 2, contentSize.height), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	m_height = contentSize.height;
	//body->getShape(0)->setFriction(0);//����Ħ����
	body->getShape(0)->setDensity(0);//�ܶ�
	body->getShape(0)->setRestitution(0);
	//body->setGravityEnable(false);//��������Ӱ��
	body->setRotationEnable(false);//��ֹ��ת
	body->setCategoryBitmask(Mask_Player);//��ײ���
	body->setCollisionBitmask(Mask_Player);
	body->setContactTestBitmask(Mask_Player);
	body->getShape(0)->setTag(2);
	this->getPhysicsBody()->addShape(body->getShape(2));
}
void Player::attack()
{
	if (m_action == Attacking)return;
	//���¹�������һС�ξٽ�ʱ��
	auto seq = Sequence::create(DelayTime::create(0.3f),CallFunc::create(CC_CALLBACK_0(Player::addAttackNode,this)), NULL);
	this->runAction(seq);
	SimpleAudioEngine::getInstance()->playEffect("Audio\\00000107.mp3");//����
	changeArmature(Attacking);
	this->m_action = Attacking;
}
void Player::fall()
{
	if (m_action != Attacking)
	{
		changeArmature(Falling);
		m_action = Falling;
	}
	//this->runAction(JumpBy::create(15, Vec2(0, -768), -768, 1));
}
void Player::attackEnd(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	//return;
	if (m_action == Dead)
	{
		if (movementType == COMPLETE)
		{
			//
		}
		return;
	}
	if (m_action != Attacking)return;
	if (movementType == COMPLETE)
	{
		this->stopAllActions();
		//m_armature->getAnimation()->playByIndex(Idle);
		auto seq = Sequence::create(DelayTime::create(0.1f), CallFunc::create(CC_CALLBACK_0(Player::setIdle, this)), CallFunc::create(CC_CALLBACK_0(Player::removeAttackShape, this)), nullptr);
		this->runAction(seq);
	}
}
double Player::getHeight()
{
	return m_height;
}
void Player::removeAttackShape()
{
	auto tollgateScene = (TollgateScene*)this->getParent();
	auto world = tollgateScene->getScene()->getPhysicsWorld();
	while(tollgateScene->getChildByTag(Tag_PlayerSword))
		tollgateScene->removeChildByTag(Tag_PlayerSword);
	while (tollgateScene->getChildByTag(Tag_PlayerSwordPart2))
		tollgateScene->removeChildByTag(Tag_PlayerSwordPart2);
}
void Player::addAttackNode()
{
	/*�½�һ��Node,���й�����ײ���*/
	auto node = new Node();
	auto body = PhysicsBody::createBox(Size(40, 20), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	body->setGravityEnable(false);//��������Ӱ��
	body->setCategoryBitmask(Mask_Sword);//��ײ���
	body->setCollisionBitmask(Mask_Sword);
	body->setContactTestBitmask(Mask_Sword);
	node->setPhysicsBody(body);
	node->setTag(Tag_PlayerSword);
	auto tollgateScene = (TollgateScene*)this->getParent();
	auto world = tollgateScene->getScene()->getPhysicsWorld();
	auto position = this->getPosition();
	//node->setPosition(Vec2(position.x, position.y + 30));
	node->setPosition(Vec2(position.x, position.y + 30));
	tollgateScene->addChild(node);
	auto seq = Sequence::create(DelayTime::create(0.1f), CCCallFunc::create(CC_CALLBACK_0(Player::addAttackNode2, this)), NULL);//�ӳ�0.2s�Ƴ������ڵ�1����ӹ����ڵ�2
	runAction(seq);
}
void Player::magicAttack()
{
	//��ʱû��ħ������
}
void Player::addAttackNode2()
{
	auto nodeAttackPart2 = new Node();
	auto bodyAttackPart2 = PhysicsBody::createBox(Size(50, 65), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	bodyAttackPart2->setGravityEnable(false);
	bodyAttackPart2->setCategoryBitmask(Mask_Sword);
	bodyAttackPart2->setCollisionBitmask(Mask_Sword); 
	bodyAttackPart2->setContactTestBitmask(Mask_Sword);
	nodeAttackPart2->setPhysicsBody(bodyAttackPart2);
	nodeAttackPart2->setTag(Tag_PlayerSwordPart2);
	//nodeAttackPart2->setPosition(Vec2(position.x + 40,position.y));
	auto tollgateScene = (TollgateScene*)this->getParent();
	auto world = tollgateScene->getScene()->getPhysicsWorld();
	auto position = this->getPosition();
	nodeAttackPart2->setPosition(Vec2(position.x + (this->m_face == face_right ? 40 : -40), position.y+15));
	tollgateScene->removeChild(tollgateScene->getChildByTag(Tag_PlayerSword));
	tollgateScene->addChild(nodeAttackPart2);
}
void Player::hurt(int value)
{
	m_health -= value;
	if (m_health < 0)
	{
		m_action = Dead;
		((TollgateScene*)(this->getParent()))->gameOver();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto moveTo = MoveTo::create(1.0f, Vec3(visibleSize.width / 2, visibleSize.height / 2, 0));
		auto seq = Sequence::create(moveTo, DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Player::die, this)), NULL);
		runAction(seq);
	}
	else
	{
		stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("Audio\\00000103.mp3");//������
		/*����*/
		auto jumpBy = JumpBy::create(0.5f, Vec2(m_face == face_right ? 50 : -50, 0), 30, 1);
		this->runAction(jumpBy);
	}
}
void Player::die()
{
	/*��������*/
	SimpleAudioEngine::getInstance()->playEffect("Audio\\00000100.mp3");
	m_armature->getAnimation()->play("PlayerDie", -1, 0);
}