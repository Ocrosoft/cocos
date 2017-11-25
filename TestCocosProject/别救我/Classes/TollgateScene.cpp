#include "TollgateScene.h"
#include "Player.h"
#include "objectTag.h"
#include "Monster.h"

TollgateScene::~TollgateScene() {}
Scene* TollgateScene::scene()
{
	auto scene = Scene::createWithPhysics();
	//����΢��������
	Vect gravity(0, -0.5f);
	scene->getPhysicsWorld()->setGravity(gravity);
	//����ģʽ
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//�������ĸ��壬��Ϊ�߽�
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height),
		PHYSICSBODY_MATERIAL_DEFAULT, 3);//��������С�����ʣ����ߺ��
	//������Ҫ�ڵ���ز��ܼ�������
	//�ṹ��scene->layer->node->sprite
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);

	auto BackgroundLayer = BackgroundLayer::create();//������
	scene->addChild(BackgroundLayer, 0); //��һ����Ϊz - index
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	auto monsterLayer = MonsterLayer::create();//�����
	scene->addChild(monsterLayer);
	//�������ã�Ҳ����getChildByTag����Ҫ��setTag
	layer->m_backgroundLayer = BackgroundLayer;
	layer->m_monsterLayer = monsterLayer;
	return scene;
}
bool TollgateScene::init()
{
	if (!Layer::init())return false;
	//���ö�ʱ��
	//�������
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.5f));
	this->addChild(m_player, 5);
	
	//����UI
	createOprUI();
	//��ײ����
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//ע����̲�׽����
	m_moveType = dontMove;
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(TollgateScene::onKeyReleased, this);
	listenerkeyPad->onKeyPressed = CC_CALLBACK_2(TollgateScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	this->schedule(schedule_selector(TollgateScene::logic));//��������
	this->schedule(schedule_selector(TollgateScene::keepMove),0.5f);//��ס�ƶ�
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
void TollgateScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)//��׽����
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

	//�Ƴ�����
	_eventDispatcher->removeEventListenersForTarget(this);
}
void TollgateScene::logic(float dt)
{
	//��������������������logic���������Դﵽͳһ���Ƶ�Ч��
	m_backgroundLayer->logic(dt);
	m_monsterLayer->logic(dt);
}
void TollgateScene::createOprUI()
{
	auto UI = GUIReader::getInstance()->widgetFromJsonFile("OprUI_1.ExportJson");
	this->addChild(UI);

	//��ȡ������ť����
	Button* rightBtn = (Button*)Helper::seekWidgetByName(UI, "rightBtn");
	Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
	Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

	//�󶨻ص�
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
	Node* playerNode = NULL;//���
	Node* other = NULL;//�����ǽ

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
	else return true;//���������ɵ���ײ

	Player* player = (Player*)playerNode;
	//����
	if (other->getTag() == ObjectTag_Border)
	{
		player->beAtked(-1);
	}
	else if (other->getTag() == ObjectTag_Monster)
	{
		Monster* monster = (Monster*)other;
		player->beAtked(monster->getiAtk());
		monster->removeFromParent();//������ʧ
	}
	log("player cur HP:%d", player->getIHP());
	return true;
}