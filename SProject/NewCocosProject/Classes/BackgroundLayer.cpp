#include "BackgroundLayer.h"
#include "objectTag.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;

BackgroundLayer::BackgroundLayer() {}
BackgroundLayer::~BackgroundLayer() {}
bool BackgroundLayer::init()
{
	if (!Layer::init())return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	TMXTiledMap* map = TMXTiledMap::create("map\\map01.tmx");
	//this->addChild(map);

	/* 加载怪物对象层的所有对象 */
	TMXObjectGroup* objGroup = map->getObjectGroup("ground");
	ValueVector objects = objGroup->getObjects();

	/* 遍历所有对象 */
	for (const auto v : objects)
	{
		const ValueMap dict = v.asValueMap();

		int iPosX = dict.at("x").asInt();
		int iPosY = dict.at("y").asInt();
		double iWidth = dict.at("width").asDouble();
		double iHeight = dict.at("height").asDouble();

		auto body = PhysicsBody::createBox(Size(iWidth, iHeight), PhysicsMaterial(1.0f, 0.0f, 0.5f));
		//auto body = PhysicsBody::createBox(Size(iWidth,iHeight), PHYSICSBODY_MATERIAL_DEFAULT);
		body->setDynamic(false);//静态物体
		//body->getShape(0)->setRestitution(-1);
		body->setCategoryBitmask(Mask_Ground);//碰撞检测
		body->setCollisionBitmask(Mask_Ground);
		body->setContactTestBitmask(Mask_Ground);
		auto node = Node::create();
		node->setPosition(Vec2(iPosX + iWidth / 2, iPosY + iHeight / 2));
		node->setPhysicsBody(body);
		node->setTag(Tag_Border);
		this->addChild(node);
	}
	return true;
}
void BackgroundLayer::update(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		this->getScene()->getPhysicsWorld()->step(1 / 180.0f);
	}
}
void BackgroundLayer::startUpdate(float dt)
{
	this->getScene()->getPhysicsWorld()->setAutoStep(false);
	scheduleUpdate();
}