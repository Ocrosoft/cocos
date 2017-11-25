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
	/*获取窗口大小*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*创建玩家Sprite*/
	auto playerSprite = Sprite::create("sprite/player1.png");
	/*加载对象层*/
	auto objGrooup = map->getObjectGroup("objects");
	/*加载meta层*/
	meta = map->getLayer("meta");
	/*设置meta层不可见*/
	meta->setVisible(false);
	/*加载barrier层*/
	barrier = map->getLayer("barrier");
	/*加载win层*/
	win = map->getLayer("win");
	/*加载玩家坐标*/
	auto playerPointDic = objGrooup->getObject("PlayerPoint");
	float playerX = playerPointDic["x"].asFloat();
	float playerY = playerPointDic["y"].asFloat();
	/*设置玩家Sprite位置*/
	playerSprite->setPosition(Vec2(playerX, playerY));
	/*Sprite添加到地图*/
	map->addChild(playerSprite, 99);
	/*创建玩家Node(因为是实体，需要用Node承载Sprite)*/
	auto m_player = Player::create();
	/*Sprite绑定到Node*/
	setSprite(playerSprite);
	return true;
}
void Player::run()
{
	/*创建动作帧数组*/
	Vector<SpriteFrame*> framesList;
	/*添加动作帧到数组*/
	framesList.pushBack(SpriteFrame::create("sprite/player1.png", Rect(0, 0, 77, 134)));
	framesList.pushBack(SpriteFrame::create("sprite/player2.png", Rect(0, 0, 66, 129)));
	framesList.pushBack(SpriteFrame::create("sprite/player3.png", Rect(0, 0, 99, 132)));
	framesList.pushBack(SpriteFrame::create("sprite/player4.png", Rect(0, 0, 111, 135)));
	framesList.pushBack(SpriteFrame::create("sprite/player5.png", Rect(0, 0, 94, 132)));
	framesList.pushBack(SpriteFrame::create("sprite/player6.png", Rect(0, 0, 64, 128)));
	framesList.pushBack(SpriteFrame::create("sprite/player7.png", Rect(0, 0, 96, 133)));
	framesList.pushBack(SpriteFrame::create("sprite/player8.png", Rect(0, 0, 103, 138)));
	/*从动画帧创建动画*/
	Animation* animation = Animation::createWithSpriteFrames(framesList, 0.2f);
	/*一直循环*/
	animation->setLoops(-1);
	/*使Sprite执行动作*/
	m_sprite->runAction(Animate::create(animation));
}
void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)return;
	auto parent = (Layer*)m_sprite->getParent();
	/*地图方块数量*/
	auto mapTiledNum = map->getMapSize();
	/*地图单个格子大小*/
	auto tiledSize = map->getTileSize();
	/* 地图大小 */
	auto mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	/* 屏幕大小 */
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/* 精灵的坐标 */
	auto spritePos = m_sprite->getPosition();
	/* 如果精灵坐标小于屏幕的一半，则取屏幕中点坐标，否则取精灵的坐标 */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);
	/* 如果x、y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标） */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);
	auto destPos = Point(x, y);
	auto centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	Point viewPos = centerPos - destPos;
	parent->setPosition(viewPos);
}
void Player::setSimplePosition(int x,int xi, int y,int yi)
{
	if (checkCollidable(x + xi, y + yi));
	else if (checkCollidable(x, y + yi)) { xi = 0; }
	else if (checkCollidable(x + xi, y)) { yi = 0; }
	Entity::setSimplePosition(x, xi, y, yi);
	/* 以主角为中心移动地图 */
	setViewPointByPlayer();
}
bool Player::checkCollidable(int x, int y)
{
	/* -----------------判断是否不可通行---------------- */
	/* 获得主角要移动到的位置在地图中的格子位置 */
	Point tiledPos = tileCoordForPosition(Vec2(x, y));
	/* 获取地图格子的唯一标识 */
	int tiledGid = meta->getTileGIDAt(tiledPos);
	/* 不为0，代表存在这个格子 */
	if (tiledGid != 0)
	{
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性,
		格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性时，
		通过格子唯一标识在地图中取得。
		*/
		auto propertiesDict = map->getPropertiesForGID(tiledGid).asValueMap();
		/*取得格子的winn属性值*/
		auto prop = propertiesDict["winn"].asString();
		/*如果是终点，停止移动*/
		if (prop.length() > 0 && prop.compare("true") == 0)return false;
		/*取得格子的star属性值*/
		prop = propertiesDict["star"].asString();
		/*如果是星星，移除并且返回true表示能移动*/
		if (prop.length()>0&&prop.compare("true") == 0)
		{
			//map->removeChild(barrier->getTileAt(tiledPos));
			//barrier->removeChild(barrier->getTileAt(tiledPos), true);
			//map->removeAllChildren();
			return true;
		}
		/* 取得格子的Collidable属性值 */
		prop = propertiesDict["Collidable"].asString();
		/* 判断Collidable属性是否为true,是的话，返回false不让玩家移动 */
		if (prop.compare("true") == 0) return false;
		return true;
	}
	return true;
}