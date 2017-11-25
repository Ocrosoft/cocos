#pragma  once
#include "cocos2d.h"
//#include "TollgateScene.h"
#include "MonsterConfig.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

#define  M_face_right 0
#define  M_face_left 1

#define  M_Idle 0
#define  M_Moving 1
#define  M_Attacking 2
#define  M_Died 3

class Monster : public Node
{
public:
	Monster();
	~Monster();
	static Monster* create(MonsterConfig* mc);//创建type类型的敌人
	virtual bool init(MonsterConfig* mc);//初始化
	int getType() { return m_monsterConfig->type; }
	int getHealth() { return m_monsterConfig->health; }
	int getAttack() { return m_monsterConfig->attack; }
	void logic();//AI
	void hurt(int value);//受伤
	void addToWorld(Node* tollgateScene);//添加到世界，从TollgateScene调用
	int getFace() { return m_face; }//获取朝向
	int getStatu() { return m_statue; }//状态
private:
	void attack();//攻击
	void move(Vec2 die);//往dir方向移动1步长
	void removeFromWorld();//从世界移除，需要播放完死亡动画再移除
	void animationEnd(Armature *armature, MovementEventType movementType, const std::string& movementID);//动画播放完毕
	void die();//死亡(播放死亡动画，处理掉落等)
	void actionJudger(Vec2 dir);//判断应该移动还是攻击
	void turnTo(int newFace);//转向
	void createBullet();//生成子弹
	void attackEnd();//攻击结束
public:
	MonsterConfig* m_monsterConfig;
private:
	Armature* m_armature;
	PhysicsBody* physicsBody;
	int m_face = M_face_right;
	int m_statue = M_Idle;
	int m_actionRef = 0;//辅助判断应该移动还是攻击的变量
};