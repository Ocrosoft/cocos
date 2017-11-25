#pragma once

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "MonsterLayer.h"
using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;
class TollgateScene :public Layer
{
public:
	~TollgateScene();
	static Scene* scene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	virtual void onExit() override;
private:
	void logic(float dt);
	void createOprUI();
	void moveToLeft(Ref* sender, TouchEventType type);
	void moveToRight(Ref* sender, TouchEventType type);
	void quickMove(Ref* sender, TouchEventType type);
	bool onContactBegin(PhysicsContact& contact);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void keepMove(float dt);
	enum MoveType//“∆∂Ø¿‡–Õ
	{
		dontMove,leftMove,rightMove
	};
	MoveType m_moveType;
	Player* m_player;
	BackgroundLayer* m_backgroundLayer;
	MonsterLayer* m_monsterLayer;
};