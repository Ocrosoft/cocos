#include "TollgateScene.h"
#include "Player.h"
#include "ThreeDirectionController.h"

Scene* TollgateScene::scene()
{
	/*����Scene*/
	auto scene = Scene::create();
	/*��������Layer*/
	auto layer = TollgateScene::create();
	/*���Layer��Scene*/
	scene->addChild(layer);
	/*����Scene*/
	return scene;
}
bool TollgateScene::init()
{
	/*��ʼ��Layer*/
	Layer::init();
	/*��TMX�ļ����عؿ���Ϣ*/
	TMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
	/*��ӹؿ���Ϣ��Layer*/
	this->addChild(map);
	/*�������*/
	auto m_player = Player::createWithTiledMap(map);
	/*ʹ���ִ�ж���*/
	m_player->run();
	/*��������ƶ�������*/
	ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
	mSMoveControll->setiXSpeed(2);
	mSMoveControll->setiYSpeed(0);
	/* ������Ҫ��ӵ������в��ܻ��update�¼� */
	this->addChild(mSMoveControll);
	m_player->setController(mSMoveControll);
	/*������*/
	return true;
}