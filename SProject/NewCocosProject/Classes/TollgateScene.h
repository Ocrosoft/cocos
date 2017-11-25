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
	void mapRoller();//地图跟随，暂时取消
	void logicControl(float dt);//逻辑控制
	void removeFromVector(Monster* mon);
private:
	Player* m_player;
	cocos2d::TMXTiledMap* map;
	int m_keepMove = face_idle;
	std::map<int,MonsterConfig*> enemyConfig;//保存怪物信息，用怪物类型查找到怪物信息
	std::vector<Monster*> m_enemys;//保存地图中的所有怪物
	std::vector<Monster*> m_items;//保存地图场景、掉落物
};