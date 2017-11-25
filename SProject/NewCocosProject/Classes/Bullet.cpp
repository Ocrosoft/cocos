#include "Bullet.h"

Bullet::Bullet() {}
Bullet::~Bullet() {}

void Bullet::move()
{
	if (m_statu)return;
	auto moveBy = MoveBy::create(1.0f, Vec3(m_dir.x, m_dir.y, 0));
	runAction(moveBy);
	//this->setPosition(this->getPosition() + m_dir);
}

bool Bullet::init(Vec2 dir)
{
	m_dir = dir;
	/*��λ��*/
	auto len = m_dir.x*m_dir.x + m_dir.y*m_dir.y;
	len = std::sqrt(len);//б�߳���
	auto sp = len / 80;//����
	m_dir.x /= sp; m_dir.y /= sp;
	return true;
}

Bullet* Bullet::create(Vec2 dir)
{
	auto bullet = new Bullet();
	if (bullet&&bullet->init(dir))
	{
		bullet->autorelease();
	}
	else CC_SAFE_DELETE(bullet);
	return bullet;
}
void Bullet::setEXAnimation(std::string EXA)
{
	m_EXAnimation = EXA;
}
void Bullet::EXEnd(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (!m_statu)return;
	if (movementType == COMPLETE)
	{
		auto seq = Sequence::create(DelayTime::create(0.1f), CallFunc::create(CC_CALLBACK_0(Bullet::removeFromWolrd, this)), NULL);
		runAction(seq);
	}
}
void Bullet::setHurt(int value)
{
	m_hurt = value;
}
void Bullet::Explor()
{
	stopAllActions();
	this->getPhysicsBody()->removeFromWorld();//���Ƴ��������磬��ֹ�ٴ���ײ
	m_statu = 1;
	m_armature->getAnimation()->play(m_EXAnimation, -1, 0);
}
void Bullet::setArmature(Armature* arm)
{
	m_armature = arm;
	m_armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Bullet::EXEnd));
}