#pragma  once

#include "cocos2d.h"
USING_NS_CC;

class Monster;//����Monster
class MonsterLayer :public Layer
{
public:
	MonsterLayer();
	~MonsterLayer();
	CREATE_FUNC(MonsterLayer);
	virtual bool init();
	void logic(float dt);
private:
	//�������ļ��м��ع�������
	void loadMonstersFromTmxConf();

	//������м���Ҫ�����Ĺ������
	Vector<Monster*> m_monsterVec;

	//��ʱ��
	float m_fTimeCounter;
};