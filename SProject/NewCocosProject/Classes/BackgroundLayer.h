#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BackgroundLayer :public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
	CREATE_FUNC(BackgroundLayer);
	void startUpdate(float dt);
	void update(float dt);
	virtual bool init();
private:
};