#pragma  once
#include "cocos2d.h"
#include "Monster.h"
#include "MonsterConfig.h"
#include "Player.h"

USING_NS_CC;

class TollgateScene :public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void gameOver();
private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void keepMove(float dt);
	bool onContactBegin(PhysicsContact& contact);
	void delayFunc();
	void startUpdate(float dt);
	void update(float dt);
	void judgeFall(float dt);
	void mapRoller();//��ͼ���棬��ʱȡ��
	void logicControl(float dt);//�߼�����
	void removeFromVector(Monster* mon);
private:
	Player* m_player;
	cocos2d::TMXTiledMap* map;
	int m_keepMove = face_idle;
	std::map<int,MonsterConfig*> enemyConfig;//���������Ϣ���ù������Ͳ��ҵ�������Ϣ
	std::vector<Monster*> m_enemys;//�����ͼ�е����й���
	std::vector<Monster*> m_items;//�����ͼ������������
};