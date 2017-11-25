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
#define  face_idle 2 /*用于持续移动，这个表示不移动*/

class Player :public Node
{
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	void jump();//跳
	int getFace();//获取面向方向
	bool turnTo(int newFace);//转向
	int getStatu();//获取当前状态(动作)
	void moveToLeft();//往左走
	void moveToRight();//往右走
	void setIdle();//设置为停止状态
	void changeArmature(int type);//更换为type型
	void attack();//攻击
	void fall();//下落
	void hurt(int value);//受伤
	double getHeight();//Node的高度
	int getAttack() { return m_attack; }//获取攻击力
	void setAttack(int atk) { m_attack = atk; }//设置攻击力
	int getHealth() { return m_health; }
	void setHealth(int value) { m_health = value; }//设置初始生命
	void heal(int value) { m_health += value; }//治疗
	void recMagic(int value) { m_magic += value; }//回复魔法
	void setMagic(int value) { m_magic = value; }//设置初始魔法值
	void magicAttack();//魔法攻击
	void die();
private:
	//void checkFallen();//检查下落
	void attackEnd(Armature *armature, MovementEventType movementType, const std::string& movementID);//攻击完成
	void removeAttackShape();
	void addAttackNode();//添加攻击节点
	void addAttackNode2();
private:
	Armature *m_armature;
	int m_face = face_right;//面朝方向
	int m_action = Idle;//当前动作
	PhysicsBody *physicsBody;
	double m_height;
	int m_attack;//攻击
	int m_health;//血量
	int m_magic;//魔法
};