#pragma  once
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;
class TollgateScene :public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();

private:
	Player* m_player;
};