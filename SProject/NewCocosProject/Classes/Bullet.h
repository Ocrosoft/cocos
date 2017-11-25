#pragma  once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

class Bullet : public Node
{
public:
	Bullet();
	~Bullet();
	void move();
	static Bullet* create(Vec2 dir);
	virtual bool init(Vec2 dir);
	void setEXAnimation(std::string EXA);
	void setHurt(int value);
	void EXEnd(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void Explor();//±¬Õ¨
	void setArmature(Armature* arm);
	void removeFromWolrd() { this->getParent()->removeChild(this); }
	int getAttack() { return m_hurt; }
private:
	Vec2 m_dir;
	std::string m_EXAnimation = "";
	int m_hurt;
	Armature* m_armature;
	int m_statu = 0;
};