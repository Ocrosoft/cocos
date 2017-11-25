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
	static Monster* create(MonsterConfig* mc);//����type���͵ĵ���
	virtual bool init(MonsterConfig* mc);//��ʼ��
	int getType() { return m_monsterConfig->type; }
	int getHealth() { return m_monsterConfig->health; }
	int getAttack() { return m_monsterConfig->attack; }
	void logic();//AI
	void hurt(int value);//����
	void addToWorld(Node* tollgateScene);//��ӵ����磬��TollgateScene����
	int getFace() { return m_face; }//��ȡ����
	int getStatu() { return m_statue; }//״̬
private:
	void attack();//����
	void move(Vec2 die);//��dir�����ƶ�1����
	void removeFromWorld();//�������Ƴ�����Ҫ�����������������Ƴ�
	void animationEnd(Armature *armature, MovementEventType movementType, const std::string& movementID);//�����������
	void die();//����(����������������������)
	void actionJudger(Vec2 dir);//�ж�Ӧ���ƶ����ǹ���
	void turnTo(int newFace);//ת��
	void createBullet();//�����ӵ�
	void attackEnd();//��������
public:
	MonsterConfig* m_monsterConfig;
private:
	Armature* m_armature;
	PhysicsBody* physicsBody;
	int m_face = M_face_right;
	int m_statue = M_Idle;
	int m_actionRef = 0;//�����ж�Ӧ���ƶ����ǹ����ı���
};