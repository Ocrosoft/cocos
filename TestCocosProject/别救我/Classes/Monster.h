#pragma  once
#include "cocos2d.h"
USING_NS_CC;

class Monster :public Node
{
public:
	Monster();
	~Monster();
	static Monster* create(int ID);
	bool init(int ID);

	void joinToWorld(Node* parent);

	CC_SYNTHESIZE(int, m_ID, ID);
	CC_SYNTHESIZE(float, m_fShowTime, fShowTime);//����ʱ��
	CC_SYNTHESIZE(int, m_iPosX, iPosX);
	CC_SYNTHESIZE(int, m_iPosY, iPosY);
	CC_SYNTHESIZE(int, m_iAtk, iAtk);//������
	CC_SYNTHESIZE(Value, m_sModelPath, sModelPath);//ͼƬ��Դ����
};