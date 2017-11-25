#include "Monster.h"
#include "objectTag.h"
#include "Bullet.h"

#define  tag_shape 2

Monster::Monster() {}
Monster::~Monster() {}
bool Monster::init(MonsterConfig* mc)
{
	this->m_monsterConfig = mc;
	if (m_monsterConfig->type >= 900)
	{
		m_armature = Armature::create(m_monsterConfig->model);
		m_armature->getAnimation()->play(m_monsterConfig->idleArmature, -1, 1);
		auto contentSize = m_armature->getContentSize();
		m_armature->setAnchorPoint(Vec2(0,0));
		m_armature->setPosition(Vec2(0, 0));
		m_armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Monster::animationEnd));
		this->addChild(m_armature);
		auto body = PhysicsBody::createBox(m_monsterConfig->itemSize, PhysicsMaterial(1.0f, 0.0f, 0.5f));
		body->setPositionOffset(Vec2(m_monsterConfig->itemSize.width / 2, m_monsterConfig->itemSize.height / 2));
		body->setRotationEnable(false);
		body->setGravityEnable(false);//地图物品不受重力影响
		body->setDynamic(false);//静态
		body->setCategoryBitmask(Mask_Items);//碰撞检测
		body->setCollisionBitmask(Mask_Items);
		body->setContactTestBitmask(Mask_Items);
		body->getShape(0)->setTag(tag_shape);
		this->setPhysicsBody(body);
		this->setTag(Tag_Items);
		physicsBody = this->getPhysicsBody();
		return true;
	}
	m_armature = Armature::create(m_monsterConfig->model);
	m_armature->getAnimation()->play(m_monsterConfig->idleArmature, -1, 1);
	m_armature->setAnchorPoint(Vec2(0, 0));
	m_armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Monster::animationEnd));
	auto contentSize = m_armature->getContentSize();
	m_armature->setPosition(Vec2(0 - contentSize.width / 2, -contentSize.height / 2));
	this->addChild(m_armature);

	auto body= PhysicsBody::createBox(Size(contentSize.width, contentSize.height), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	//body->setPositionOffset(Vec2(contentSize.width / 2, contentSize.height / 2));
	body->setRotationEnable(false);
	if (m_monsterConfig->fly)body->setGravityEnable(false);
	body->setCategoryBitmask(Mask_Enemy);//碰撞检测
	body->setCollisionBitmask(Mask_Enemy);
	body->setContactTestBitmask(Mask_Enemy);
	body->getShape(0)->setTag(tag_shape);
	this->setPhysicsBody(body);
	this->setTag(Tag_Monster);
	physicsBody = this->getPhysicsBody();

	return true;
}
Monster* Monster::create(MonsterConfig* mc)
{
	auto monster = new Monster();
	if (monster&&monster->init(mc))
	{
		monster->autorelease();
	}
	else CC_SAFE_DELETE(monster);
	return monster;
}
void Monster::attack()
{
	/*分为远程攻击和近身攻击*/
	/*区分:有子弹为远程，无子弹为近身*/
	/*播放攻击动画*/
	m_statue = M_Attacking;
	this->m_armature->getAnimation()->play(m_monsterConfig->attakArmature, -1, 0);
	if (m_monsterConfig->bulletArmature !="")//属于远程攻击
	{
		auto seq = Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Monster::createBullet, this)),
			DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Monster::createBullet, this)), 
				DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(Monster::createBullet, this)), NULL);
		runAction(seq);
	}
	else
	{

	}
}
void Monster::move(Vec2 dir)//参数是方向
{
	if (getStatu() == M_Died)return;
	/*单位化*/
	auto len = dir.x*dir.x + dir.y*dir.y;
	len = std::sqrt(len);//斜边长度
	auto sp = len / m_monsterConfig->step;//倍数
	dir.x /= sp; dir.y /= sp;

	auto moveBy = MoveBy::create(0.5f, Vec3(dir.x, dir.y, 0));
	dir.x >= 0 ? turnTo(M_face_right) : turnTo(M_face_left);
	this->runAction(moveBy);
}
void Monster::logic()
{
	if (m_statue == M_Died)return;
	if (!this)return;
	if (!this->getParent())return;
	/*AI，完全不知道怎么写*/
	m_actionRef++;
	auto tollgateScene = (Node*) this->getParent();//获取TollgateScene
	auto player = tollgateScene->getChildByTag(Tag_Player);//获取玩家对象
	auto positionPlayer = player->getPosition();//玩家位置
	auto dir = positionPlayer - this->getPosition();//要移动的方向
	actionJudger(dir);
}
void Monster::addToWorld(Node* tollgateScene)
{
	tollgateScene->addChild(this);
}
void Monster::die()
{
	stopAllActions();
	/*播放死亡动画*/
	m_armature->getAnimation()->play(m_monsterConfig->die, -1, 0);
	/*处理掉落*/
}
void Monster::removeFromWorld()
{
	/*从TollgateScene移除*/
	((Node*)this->getParent())->removeChild(this);
}
void Monster::animationEnd(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	switch (m_statue)
	{
	case M_Died:
		if (movementType == COMPLETE)
		{
			auto seq = Sequence::create(DelayTime::create(0.01f), CallFunc::create(CC_CALLBACK_0(Monster::removeFromWorld, this)), nullptr);
			this->runAction(seq);
		}
		break;
	case M_Attacking:
		if (movementType == COMPLETE)
		{
			auto seq = Sequence::create(DelayTime::create(0.1f), CallFunc::create(CC_CALLBACK_0(Monster::attackEnd, this)), NULL);
			this->runAction(seq);
		}
		break;
	}	
}
void Monster::hurt(int value)
{
	m_monsterConfig->health -= value;
	if (m_monsterConfig->health <= 0)
	{
		m_statue = M_Died;
		die();//死亡
	}
	else//如果没有死亡，则击退
	{
		auto jumpBy = JumpBy::create(0.5f, Vec2(m_face == M_face_right ? -50 : 50, 0), 30, 1);
		this->runAction(jumpBy);
	}
}
void Monster::actionJudger(Vec2 dir)
{
	if (getStatu() == M_Attacking)return;
	if (m_actionRef < 5)
	{
		move(dir);
	}
	else
	{
		//m_actionRef = 0;
		attack();
	}
}
void Monster::turnTo(int newFace)
{
	if (m_face == newFace)return;
	if (newFace == M_face_left) 
	{
		this->setScaleX(-1);
		m_face = M_face_left;
	}
	else 
	{
		this->setScaleX(1);
		m_face = M_face_right;
	}
}
void Monster::createBullet()
{
	auto playerPosition = this->getParent()->getChildByTag(Tag_Player)->getPosition();
	auto dir = playerPosition - this->getPosition();
	auto bullet = Bullet::create(dir);
	auto armature = Armature::create(m_monsterConfig->model);
	armature->getAnimation()->play(m_monsterConfig->bulletArmature);
	armature->setAnchorPoint(Vec2(0, 0));
	bullet->setArmature(armature);
	bullet->setTag(Tag_MonsterFire);//设置子弹Tag
	bullet->addChild(armature);
	auto contentSize = armature->getContentSize();
	auto body = PhysicsBody::createBox(Size(10, 10), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	body->setPositionOffset(Vec2(10, 20));
	body->setGravityEnable(false);
	body->setCategoryBitmask(Mask_Bullet);//碰撞检测
	body->setCollisionBitmask(Mask_Bullet);
	body->setContactTestBitmask(Mask_Bullet);
	bullet->setPhysicsBody(body);
	bullet->setAnchorPoint(Vec2(0, 0));
	bullet->setPosition(Vec2(this->getPosition().x-m_armature->getContentSize().width/2,this->getPosition().y));
	bullet->setHurt(m_monsterConfig->attack);
	bullet->setEXAnimation(m_monsterConfig->bulletEXArmature);
	this->getParent()->addChild(bullet);
}
void Monster::attackEnd()
{
	m_statue = M_Idle;
	m_actionRef = 0;//判断变量重置
	m_armature->getAnimation()->play(m_monsterConfig->idleArmature);
}