#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class TollgateScene : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
};

