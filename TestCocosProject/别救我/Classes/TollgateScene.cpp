#include "TollgateScene.h"
#include "Player.h"
#include "objectTag.h"
#include "Monster.h"

TollgateScene::~TollgateScene() {}
Scene* TollgateScene::scene()
{
	auto scene = Scene::createWithPhysics();
	//创建微重力世界
	Vect gravity(0, -0.5f);
	scene->getPhysicsWorld()->setGravity(gravity);
	//测试模式
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建空心刚体，作为边界
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height),
		PHYSICSBODY_MATERIAL_DEFAULT, 3);//参数：大小，材质，边线厚度
	//刚体需要节点承载才能加入世界
	//结构：scene->layer->node->sprite
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);

	auto BackgroundLayer = BackgroundLayer::create();//背景层
	scene->addChild(BackgroundLayer, 0); //后一参数为z - index
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	auto monsterLayer = MonsterLayer::create();//怪物层
	scene->addChild(monsterLayer);
	//保存引用，也可以getChildByTag，需要先setTag
	layer->m_backgroundLayer = BackgroundLayer;
	layer->m_monsterLayer = monsterLayer;
	return scene;
}
bool TollgateScene::init()
{
	if (!Layer::init())return false;
	//设置定时器
	//添加主角
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.5f));
	this->addChild(m_player, 5);
	
	//创建UI
	createOprUI();
	//碰撞监听
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//注册键盘捕捉监听
	m_moveType = dontMove;
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(TollgateScene::onKeyReleased, this);
	listenerkeyPad->onKeyPressed = CC_CALLBACK_2(TollgateScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	this->schedule(schedule_selector(TollgateScene::logic));//背景滚动
	this->schedule(schedule_selector(TollgateScene::keepMove),0.5f);//按住移动
	return true;
}
void TollgateScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		if (m_moveType == dontMove)
		{
			m_player->moveToLeft();
			m_moveType = leftMove;
		}
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if(m_moveType== dontMove)
		{
			m_player->moveToRight();
			m_moveType = rightMove;
		}
		break;
	default:
		break;
	}
}
void TollgateScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)//捕捉监听
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		//m_player->moveToLeft();
		if(m_moveType==leftMove)
			m_moveType = dontMove;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		//m_player->moveToRight();
		if(m_moveType==rightMove)
			m_moveType = dontMove;
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		m_player->quickMove();
		break;
	default:
		break;
	}
}
void TollgateScene::keepMove(float dt)
{
	if (m_moveType == leftMove)
		m_player->moveToLeft();
	else if (m_moveType == rightMove)
		m_player->moveToRight();
	else if (m_moveType == dontMove);
}
void TollgateScene::onExit()
{
	Layer::onExit();

	//移除监听
	_eventDispatcher->removeEventListenersForTarget(this);
}
void TollgateScene::logic(float dt)
{
	//用这个函数调用其他层的logic函数，可以达到统一控制的效果
	m_backgroundLayer->logic(dt);
	m_monsterLayer->logic(dt);
}
void TollgateScene::createOprUI()
{
	auto UI = GUIReader::getInstance()->widgetFromJsonFile("OprUI_1.ExportJson");
	this->addChild(UI);

	//获取三个按钮对象
	Button* rightBtn = (Button*)Helper::seekWidgetByName(UI, "rightBtn");
	Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
	Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

	//绑定回调
	leftBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToLeft));
	rightBtn->addTouchEventListener(this, toucheventselector(TollgateScene::moveToRight));
	quickMoveBtn->addTouchEventListener(this, toucheventselector(TollgateScene::quickMove));
}
void TollgateScene::moveToLeft(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		m_player->moveToLeft();
		break;
	}
}
void TollgateScene::moveToRight(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		m_player->moveToRight();
		break;
	}
}
void TollgateScene::quickMove(Ref* sender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		m_player->quickMove();
		break;
	}
}
bool TollgateScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (nodeA == NULL || nodeB == NULL)return true;
	Node* playerNode = NULL;//玩家
	Node* other = NULL;//怪物或墙

	if (nodeA->getTag() == ObjectTag_Player)
	{
		playerNode = nodeA;
		other = nodeB;
	}
	else if (nodeB->getTag() == ObjectTag_Player)
	{
		playerNode = nodeB;
		other = nodeA;
	}
	else return true;//不是玩家造成的碰撞

	Player* player = (Player*)playerNode;
	//处理
	if (other->getTag() == ObjectTag_Border)
	{
		player->beAtked(-1);
	}
	else if (other->getTag() == ObjectTag_Monster)
	{
		Monster* monster = (Monster*)other;
		player->beAtked(monster->getiAtk());
		monster->removeFromParent();//怪物消失
	}
	log("player cur HP:%d", player->getIHP());
	return true;
}