#include "TollgateScene.h"

Scene* TollgateScene::scene()
{
	/*��������*/
	auto scene = Scene::createWithPhysics();
	/*������С*/
	Vect gravity(0, -9.8f);
    //��������ģʽ
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	/*������������*/
	scene->getPhysicsWorld()->setGravity(gravity);
	/*���������С*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*�������������С�Ŀ���ʵ��(����)��Ϊ�߽�*/
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(0);
	/*����ʵ����ؽڵ㣬���ø�����*/
	auto node = Node::create();
	node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	/*��ӵ�����*/
	scene->addChild(node);
	/*�����㣬��ӵ�����*/
	auto layer = TollgateScene::create();
	scene->addChild(layer, 10);
	return scene;
}
bool TollgateScene::init()
{
	/*Ԥ�����ļ�*/
	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monster.plist");
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("titleScreen3Spritesheet.plist");
	if (!Layer::init())return false;
	//�������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_player, 5);
	return true;
}