#include "TollgateScene.h"
#include "SimpleAudioEngine.h"
#include "json\writer.h"
#include "json\reader.h"
#include "Monster.h"
#include "BackgroundLayer.h"
#include "objectTag.h"
#include "cocostudio/CocoStudio.h"
#include "Bullet.h"
#include <algorithm>

using namespace cocostudio;
using namespace CocosDenshion;

Scene* TollgateScene::scene()
{
	/*重力场景*/
	auto scene = Scene::createWithPhysics();
	/*重力大小*/
	Vect gravity(0, -200);
	//开启测试模式
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	/*设置世界重力*/
	scene->getPhysicsWorld()->setGravity(gravity);
	/*可视区域大小*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*创建可视区域大小的空心实体(刚体)作为边界*/
	//auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PhysicsMaterial(0.0f, 0.0f, 0.0f), 3);
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width + 10, visibleSize.height + 10), PHYSICSBODY_MATERIAL_DEFAULT, 10);
	/*创建实体承载节点，设置各属性*/
	auto node = Node::create();
	node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	/*添加到场景*/
	scene->addChild(node);
	/*创建层，添加到场景*/
	auto layer = TollgateScene::create();
	scene->addChild(layer, 10);
	auto BackgroundLayer = BackgroundLayer::create();//背景层
	scene->addChild(BackgroundLayer, 0); //后一参数为z - index
	return scene;
}
bool TollgateScene::init()
{
	if (!Layer::init())return false;
	/*预加载文件*/
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Player\\playerPartsSpritesheet1.png","Player\\playerPartsSpritesheet1.plist","Player\\FinalAnimation.ExportJson");//玩家
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Player\\playerSpritesheet.png", "Player\\playerSpritesheet.plist", "Player\\FinalAnimation.ExportJson");//玩家
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Player\\miscSpritesheet.png", "Player\\miscSpritesheet.plist", "Player\\FinalAnimation.ExportJson");//玩家
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Enemy\\enemyFinal1Spritesheet.png","Enemy\\enemyFinal1Spritesheet.plist","Enemy\\FinalAnimation_enemy1.ExportJson");//1号敌人
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Enemy\\FinalAnimation_enemy10.png", "Enemy\\FinalAnimation_enemy10.plist", "Enemy\\FinalAnimation_enemy1.ExportJson");//1号敌人
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Enemy\\castleTerrainSpritesheet.png","Enemy\\castleTerrainSpritesheet.plist","Enemy\\FinalAnimation_item999.ExportJson");
	map = CCTMXTiledMap::create("Map\\map01.tmx");//1号地图
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Audio\\00000000.mp3");//背景音乐
	SimpleAudioEngine::getInstance()->preloadEffect("Audio\\00000100.mp3");//死亡
	SimpleAudioEngine::getInstance()->preloadEffect("Audio\\00000103.mp3");//被攻击
	SimpleAudioEngine::getInstance()->preloadEffect("Audio\\00000107.mp3");//攻击
#pragma region .   加载配置文件
	/*从配置文件获取怪物数据*/
	std::string sData = FileUtils::getInstance()->getStringFromFile("Enemy\\EnemyConfig.plist");
	/*解析json*/
	Json::Reader reader;
	Json::Value root;//根节点
	if (!reader.parse(sData, root, false))
	{
		return false;
	}
	int size = root.size();
	for (int i = 0; i < size; i++)
	{
		auto monsterConfig = new MonsterConfig();
		monsterConfig->type = root[i]["type"].asInt();
		monsterConfig->health = root[i]["health"].asInt();//共有属性
		monsterConfig->idleArmature = root[i]["Idle"].asString();
		monsterConfig->model = root[i]["model"].asString();
		monsterConfig->die = root[i]["Die"].asString();
		if (monsterConfig->type < 900)
		{
			monsterConfig->attack = root[i]["attack"].asInt();
			monsterConfig->bulletArmature = root[i]["Bullet"].asString();
			monsterConfig->attakArmature = root[i]["Attack"].asString();
			monsterConfig->bulletEXArmature = root[i]["BulletEX"].asString();
			monsterConfig->fly = root[i]["fly"].asInt();
			monsterConfig->step = root[i]["Step"].asInt();
		}
		else
		{
			monsterConfig->gold = root[i]["Gold"].asInt();
			monsterConfig->item = root[i]["item"].asInt();
		}
		if(monsterConfig->checkValid())
			enemyConfig[monsterConfig->type] = monsterConfig;
		else
		{
			MessageBox("读取配置文件错误", "错误");
		}
	}
#pragma endregion
	/*键盘监听*/
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(TollgateScene::onKeyReleased, this);
	listenerkeyPad->onKeyPressed = CC_CALLBACK_2(TollgateScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
	this->schedule(schedule_selector(TollgateScene::keepMove), 0.1f);//按住移动
	/*碰撞检测*/
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TollgateScene::onContactBegin, this);
	/*开启监听器*/
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	/*加载地图*/
	this->addChild(map);
	/*添加主角*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setHealth(20);
	m_player->setAttack(10);
	auto objGrooup = map->getObjectGroup("pos");
	auto playerPointDic = objGrooup->getObject("pos01");
	float playerX = playerPointDic["x"].asFloat();
	float playerY = playerPointDic["y"].asFloat();
	//m_player->setAnchorPoint(Vec2(0, 0));
	m_player->setPosition(Vec2(playerX,playerY));
	this->addChild(m_player, 5);
	/*添加这张地图的敌人*/
	TMXObjectGroup* objGroup = map->getObjectGroup("enemy");
	ValueVector objects = objGroup->getObjects();
	for (const auto v : objects)
	{
		const ValueMap dict = v.asValueMap();
		int iPosX = dict.at("x").asInt();
		int iPosY = dict.at("y").asInt();
		int monsterType = dict.at("type").asInt();
		if (monsterType >= 900)
		{
			double iWidth = dict.at("width").asDouble();
			double iHeight = dict.at("height").asDouble();
			enemyConfig[monsterType]->itemSize = Size(iWidth, iHeight);
		}
		auto monster = Monster::create(enemyConfig[monsterType]);
		monster->setPosition(Vec2(iPosX, iPosY));//设置位置
		monster->addToWorld(this);//添加到世界
		if(monsterType<900)
			m_enemys.push_back(monster);//添加到怪物数组中
		else 
			m_items.push_back(monster);//添加到物品数组中
	}
	this->schedule(schedule_selector(TollgateScene::logicControl), 0.5f);//怪物AI
	/*碰撞检测优化，穿透问题*/
	scheduleOnce(schedule_selector(TollgateScene::startUpdate), 2);
	/*速度检测，改变下落状态；移动攻击时改变同步移动攻击节点的位置*/
	this->schedule(schedule_selector(TollgateScene::judgeFall), 0.1f);
	/*背景音乐*/
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio\\00000000.mp3", true);
	return true;
}
void TollgateScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_J:
		m_player->attack();
		break;
	case EventKeyboard::KeyCode::KEY_K:
		m_player->jump();
		break;
	case EventKeyboard::KeyCode::KEY_A:
		if (m_keepMove != face_idle)break;
		m_keepMove = face_left;
		m_player->moveToLeft();
		this->schedule(schedule_selector(TollgateScene::keepMove), 0.1f);//按住移动
		mapRoller();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if (m_keepMove != face_idle)break;
		m_keepMove = face_right;
		m_player->moveToRight();
		this->schedule(schedule_selector(TollgateScene::keepMove), 0.1f);//按住移动
		mapRoller();
		break;
	}
}
void TollgateScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)//捕捉监听
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_K:
		break;
	case EventKeyboard::KeyCode::KEY_A:
		if (m_keepMove == face_left)
		{
			m_keepMove = face_idle;
			if(m_player->getStatu()==Walking)m_player->setIdle();
		}
		break;
	case EventKeyboard::KeyCode::KEY_D:
		if (m_keepMove==face_right)
		{
			m_keepMove = face_idle;
			if (m_player->getStatu() == Walking)m_player->setIdle();
		}
		break;
	}
}
void TollgateScene::keepMove(float dt)
{
	if (m_keepMove!=face_idle)
	{
		if (m_player->getFace() == face_right)
			m_player->moveToRight();
		else m_player->moveToLeft();
	}
	else 
	{
		unschedule(schedule_selector(TollgateScene::keepMove));
		if(m_player->getStatu()==Walking)
			m_player->setIdle();
	}
	mapRoller();
}
bool TollgateScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (nodeA == NULL || nodeB == NULL)return true;
	//if (nodeA->getTag() != Tag_Player&&nodeB->getTag() != Tag_Player)return true;
	/*玩家参与的碰撞*/
	if (nodeA->getTag() == Tag_Player || nodeB->getTag() == Tag_Player)
	{
		if (nodeB->getTag() == Tag_Player)std::swap(nodeA, nodeB);
		auto playerNode = (Player*)nodeA;
		switch (nodeB->getTag())
		{
		case Tag_Border:
		{
			if (playerNode->getStatu() != Falling)return true;
			playerNode->stopAllActions();//停止动作
			if ((nodeB->getPositionY()) > (nodeA->getPositionY() + playerNode->getHeight() / 2))return true;//避免撞墙变回Idle
			auto delayTime = DelayTime::create(0.1f);
			auto delayCall = CallFunc::create(CC_CALLBACK_0(TollgateScene::delayFunc, this));
			auto seq = Sequence::create(delayTime, delayCall, nullptr);//延迟变成Idle状态
			this->runAction(seq);
			break;
		}
		case Tag_MonsterFire:
		{
			auto bullet = (Bullet*)nodeB;
			playerNode->hurt(bullet->getAttack());
			if(playerNode->getStatu()!=Dead)bullet->Explor();
			break;
		}
		case Tag_Monster:
		{
			auto monster = (Monster*)nodeB;
			playerNode->hurt(monster->getAttack());
			break;
		}
		}
		return true;
	}
	/*玩家的剑参与的碰撞*/
	if ((nodeA->getTag() == Tag_PlayerSword || nodeA->getTag() == Tag_PlayerSwordPart2) || (nodeB->getTag() == Tag_PlayerSword || nodeB->getTag() == Tag_PlayerSwordPart2))
	{
		if (nodeB->getTag() == Tag_PlayerSword || nodeB->getTag() == Tag_PlayerSwordPart2)std::swap(nodeA, nodeB);
		auto swordNode = nodeA;
		auto monster = (Monster*)nodeB;
		switch (nodeB->getTag())
		{
		case Tag_Items:
			monster->hurt(m_player->getAttack());
			break;
		case Tag_Monster:
			monster->hurt(m_player->getAttack());
			if (monster->getStatu() == M_Died)
				removeFromVector(monster);
			break;
		}
		return true;
	}
	/*子弹参与的碰撞*/
	if (nodeA->getTag() == Tag_MonsterFire || nodeB->getTag() == Tag_MonsterFire)
	{
		if (nodeB->getTag() == Tag_MonsterFire)std::swap(nodeA, nodeB);
		if (nodeB->getTag() == Tag_MonsterFire)return true;//两子弹碰撞
		//除了两子弹碰撞，其他子弹碰撞均移除子弹(与玩家的碰撞在玩家段中处理)
		((Bullet*)nodeA)->Explor();
		//this->removeChild(nodeA);//移除子弹
		return true;
	}
	return true;
}
void TollgateScene::delayFunc()
{
	m_player->setIdle();
}
void TollgateScene::update(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		this->getScene()->getPhysicsWorld()->step(1 / 180.0f);
	}
}
void TollgateScene::startUpdate(float dt)
{
	this->getScene()->getPhysicsWorld()->setAutoStep(false);
	scheduleUpdate();
}
void TollgateScene::judgeFall(float dt)
{
	/*判断是否需要改变下落动画*/
	if (m_player->getStatu() == Falling)return;
	if (m_player->getStatu() == Jumping)return;
	auto vy = m_player->getPhysicsBody()->getVelocity().y;
	if (vy != 0)
	{
		m_player->fall();
	}
	/*攻击并且正在移动时同步移动攻击节点*/
	if (m_player->getStatu() == Attacking)
	{
		auto attackNode = this->getChildByTag(Tag_PlayerSword);
		auto attackNode2 = this->getChildByTag(Tag_PlayerSwordPart2);
		auto position=m_player->getPosition();
		if(attackNode)attackNode->setPosition(position.x, position.y + 30);
		if (attackNode2)attackNode2->setPosition(position.x + (m_player->getFace() == face_right ? 40 : -40), position.y);
	}
	//CCLOG("%f", m_player->getPhysicsBody()->getVelocity().y);
}
void TollgateScene::mapRoller()
{
	return;//比较卡，暂时弃用
	if (m_player==NULL)return;
	auto mapTiledNum = map->getMapSize();
	auto tiledSize = map->getTileSize();
	auto mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto playerPos = m_player->getPosition();
	float x = std::max(playerPos.x, visibleSize.width / 2);
	float y = std::max(playerPos.y, visibleSize.height / 2);
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);
	auto destPos = Point(x, y);
	auto centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPos = centerPos - destPos;
	this->setPosition(viewPos);
}
void TollgateScene::logicControl(float dt)
{
	for (auto monster : m_enemys)
	{
		if (monster->getStatu() == M_Died)continue;//已经死的跳过，多图不能这么做
		monster->logic();//调用怪物的logic函数
	}
	auto children = this->getChildren();//获取所有孩子
	for (auto node : children)
	{
		if (node->getTag() == Tag_MonsterFire)//如果Tag是子弹
		{
			auto bullet = (Bullet*)node;
			bullet->move();
		}
	}
}
void TollgateScene::removeFromVector(Monster* mon)
{
	std::vector<Monster*>::iterator it = std::find(m_enemys.begin(), m_enemys.end(), mon);
	if (it != m_enemys.end())
	{
		m_enemys.erase(it);
	}
}
void TollgateScene::gameOver()
{
	m_enemys.clear();
	unschedule(schedule_selector(TollgateScene::judgeFall));//下落判断函数
	unschedule(schedule_selector(TollgateScene::logicControl));//怪物AI
	unschedule(schedule_selector(TollgateScene::keepMove));//按住移动
	this->getScene()->getPhysicsWorld()->setGravity(Vec2(0, 0));//设置零重力
	auto child = this->getChildren();
	for (auto node : child)
	{
		if (node->getTag() != Tag_Player)
			removeChild(node);//除了玩家全部移除
	}
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio\\00000013.mp3");
	//m_player->die();
}