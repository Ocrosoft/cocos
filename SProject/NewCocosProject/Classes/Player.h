#pragma  once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

USING_NS_CC;

#define  Idle 0
#define  Walking 1
#define  Jumping 2
#define  Falling 3
#define  Attacking 4
#define  Dead 5

#define  face_right 0
#define  face_left 1
#define  face_idle 2 /*���ڳ����ƶ��������ʾ���ƶ�*/

class Player :public Node
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	void jump();//��
	int getFace();//��ȡ������
	bool turnTo(int newFace);//ת��
	int getStatu();//��ȡ��ǰ״̬(����)
	void moveToLeft();//������
	void moveToRight();//������
	void setIdle();//����Ϊֹͣ״̬
	void changeArmature(int type);//����Ϊtype��
	void attack();//����
	void fall();//����
	void hurt(int value);//����
	double getHeight();//Node�ĸ߶�
	int getAttack() { return m_attack; }//��ȡ������
	void setAttack(int atk) { m_attack = atk; }//���ù�����
	int getHealth() { return m_health; }
	void setHealth(int value) { m_health = value; }//���ó�ʼ����
	void heal(int value) { m_health += value; }//����
	void recMagic(int value) { m_magic += value; }//�ظ�ħ��
	void setMagic(int value) { m_magic = value; }//���ó�ʼħ��ֵ
	void magicAttack();//ħ������
	void die();
private:
	//void checkFallen();//�������
	void attackEnd(Armature *armature, MovementEventType movementType, const std::string& movementID);//�������
	void removeAttackShape();
	void addAttackNode();//��ӹ����ڵ�
	void addAttackNode2();
private:
	Armature *m_armature;
	int m_face = face_right;//�泯����
	int m_action = Idle;//��ǰ����
	PhysicsBody *physicsBody;
	double m_height;
	int m_attack;//����
	int m_health;//Ѫ��
	int m_magic;//ħ��
};