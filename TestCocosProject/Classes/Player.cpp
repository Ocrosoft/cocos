#include "Player.h"
#include <cmath>
bool Player::init()
{
	return true;
}
Player* Player::createWithTiledMap(TMXTiledMap* map)
{
	auto m_player = new Player();
	if (m_player&&m_player->initWithTiledMap(map));
	else
	{
		CC_SAFE_DELETE(m_player);
	}
	return m_player;
}
bool Player::initWithTiledMap(TMXTiledMap* map)
{
	if (this->map == nullptr)this->map = map;
	/*��ȡ���ڴ�С*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*�������Sprite*/
	auto playerSprite = Sprite::create("sprite/player1.png");
	/*���ض����*/
	auto objGrooup = map->getObjectGroup("objects");
	/*����meta��*/
	meta = map->getLayer("meta");
	/*����meta�㲻�ɼ�*/
	meta->setVisible(false);
	/*����barrier��*/
	barrier = map->getLayer("barrier");
	/*����win��*/
	win = map->getLayer("win");
	/*�����������*/
	auto playerPointDic = objGrooup->getObject("PlayerPoint");
	float playerX = playerPointDic["x"].asFloat();
	float playerY = playerPointDic["y"].asFloat();
	/*�������Spriteλ��*/
	playerSprite->setPosition(Vec2(playerX, playerY));
	/*Sprite��ӵ���ͼ*/
	map->addChild(playerSprite, 99);
	/*�������Node(��Ϊ��ʵ�壬��Ҫ��Node����Sprite)*/
	auto m_player = Player::create();
	/*Sprite�󶨵�Node*/
	setSprite(playerSprite);
	return true;
}
void Player::run()
{
	/*��������֡����*/
	Vector<SpriteFrame*> framesList;
	/*��Ӷ���֡������*/
	framesList.pushBack(SpriteFrame::create("sprite/player1.png", Rect(0, 0, 77, 134)));
	framesList.pushBack(SpriteFrame::create("sprite/player2.png", Rect(0, 0, 66, 129)));
	framesList.pushBack(SpriteFrame::create("sprite/player3.png", Rect(0, 0, 99, 132)));
	framesList.pushBack(SpriteFrame::create("sprite/player4.png", Rect(0, 0, 111, 135)));
	framesList.pushBack(SpriteFrame::create("sprite/player5.png", Rect(0, 0, 94, 132)));
	framesList.pushBack(SpriteFrame::create("sprite/player6.png", Rect(0, 0, 64, 128)));
	framesList.pushBack(SpriteFrame::create("sprite/player7.png", Rect(0, 0, 96, 133)));
	framesList.pushBack(SpriteFrame::create("sprite/player8.png", Rect(0, 0, 103, 138)));
	/*�Ӷ���֡��������*/
	Animation* animation = Animation::createWithSpriteFrames(framesList, 0.2f);
	/*һֱѭ��*/
	animation->setLoops(-1);
	/*ʹSpriteִ�ж���*/
	m_sprite->runAction(Animate::create(animation));
}
void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)return;
	auto parent = (Layer*)m_sprite->getParent();
	/*��ͼ��������*/
	auto mapTiledNum = map->getMapSize();
	/*��ͼ�������Ӵ�С*/
	auto tiledSize = map->getTileSize();
	/* ��ͼ��С */
	auto mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	/* ��Ļ��С */
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/* ��������� */
	auto spritePos = m_sprite->getPosition();
	/* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ��������� */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);
	/* ���x��y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩ */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);
	auto destPos = Point(x, y);
	auto centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	/* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
	Point viewPos = centerPos - destPos;
	parent->setPosition(viewPos);
}
void Player::setSimplePosition(int x,int xi, int y,int yi)
{
	if (checkCollidable(x + xi, y + yi));
	else if (checkCollidable(x, y + yi)) { xi = 0; }
	else if (checkCollidable(x + xi, y)) { yi = 0; }
	Entity::setSimplePosition(x, xi, y, yi);
	/* ������Ϊ�����ƶ���ͼ */
	setViewPointByPlayer();
}
bool Player::checkCollidable(int x, int y)
{
	/* -----------------�ж��Ƿ񲻿�ͨ��---------------- */
	/* �������Ҫ�ƶ�����λ���ڵ�ͼ�еĸ���λ�� */
	Point tiledPos = tileCoordForPosition(Vec2(x, y));
	/* ��ȡ��ͼ���ӵ�Ψһ��ʶ */
	int tiledGid = meta->getTileGIDAt(tiledPos);
	/* ��Ϊ0���������������� */
	if (tiledGid != 0)
	{
		/*
		��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����,
		����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������ʱ��
		ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ�á�
		*/
		auto propertiesDict = map->getPropertiesForGID(tiledGid).asValueMap();
		/*ȡ�ø��ӵ�winn����ֵ*/
		auto prop = propertiesDict["winn"].asString();
		/*������յ㣬ֹͣ�ƶ�*/
		if (prop.length() > 0 && prop.compare("true") == 0)return false;
		/*ȡ�ø��ӵ�star����ֵ*/
		prop = propertiesDict["star"].asString();
		/*��������ǣ��Ƴ����ҷ���true��ʾ���ƶ�*/
		if (prop.length()>0&&prop.compare("true") == 0)
		{
			//map->removeChild(barrier->getTileAt(tiledPos));
			//barrier->removeChild(barrier->getTileAt(tiledPos), true);
			//map->removeAllChildren();
			return true;
		}
		/* ȡ�ø��ӵ�Collidable����ֵ */
		prop = propertiesDict["Collidable"].asString();
		/* �ж�Collidable�����Ƿ�Ϊtrue,�ǵĻ�������false��������ƶ� */
		if (prop.compare("true") == 0) return false;
		return true;
	}
	return true;
}