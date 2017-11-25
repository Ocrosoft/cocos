#include "TollgateScene.h"
#include "Player.h"
#include "ThreeDirectionController.h"

Scene* TollgateScene::scene()
{
	/*创建Scene*/
	auto scene = Scene::create();
	/*创建本层Layer*/
	auto layer = TollgateScene::create();
	/*添加Layer到Scene*/
	scene->addChild(layer);
	/*返回Scene*/
	return scene;
}
bool TollgateScene::init()
{
	/*初始化Layer*/
	Layer::init();
	/*从TMX文件加载关卡信息*/
	TMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
	/*添加关卡信息到Layer*/
	this->addChild(map);
	/*创建玩家*/
	auto m_player = Player::createWithTiledMap(map);
	/*使玩家执行动作*/
	m_player->run();
	/*创建玩家移动控制器*/
	ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
	mSMoveControll->setiXSpeed(2);
	mSMoveControll->setiYSpeed(0);
	/* 控制器要添加到场景中才能获得update事件 */
	this->addChild(mSMoveControll);
	m_player->setController(mSMoveControll);
	/*返回真*/
	return true;
}