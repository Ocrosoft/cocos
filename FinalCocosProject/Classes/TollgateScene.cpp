#include "TollgateScene.h"

Scene* TollgateScene::scene()
{
	/*重力场景*/
	auto scene = Scene::createWithPhysics();
	/*重力大小*/
	Vect gravity(0, -9.8f);
    //开启测试模式
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	/*设置世界重力*/
	scene->getPhysicsWorld()->setGravity(gravity);
	/*可视区域大小*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*创建可视区域大小的空心实体(刚体)作为边界*/
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setRestitution(0);
	/*创建实体承载节点，设置各属性*/
	auto node = Node::create();
	node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	/*添加到场景*/
	scene->addChild(node);
	/*创建层，添加到场景*/
	auto layer = TollgateScene::create();
	scene->addChild(layer, 10);
	return scene;
}
bool TollgateScene::init()
{
	/*预加载文件*/
	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("monster.plist");
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("titleScreen3Spritesheet.plist");
	if (!Layer::init())return false;
	//添加主角
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_player, 5);
	return true;
}