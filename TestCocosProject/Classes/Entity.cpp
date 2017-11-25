#include "Entity.h"

void Entity::setSprite(Sprite* sprite)
{
	this->m_sprite = sprite;
}
void Entity::setController(Controller* controller)
{
	this->m_Controller = controller;
	controller->setControllerListener(this);
}
void Entity::setSimplePosition(int x,int xi, int y,int yi)
{
	if (m_sprite)
	{
		m_sprite->setPosition(Vec2(x + xi, y + yi));
	}
}
cocos2d::Point Entity::getCurPosition()
{
	if (m_sprite)
	{
		return m_sprite->getPosition();
	}
	return Point(Point(0, 0));
}
Point Entity::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = map->getMapSize();
	Size tiledSize = map->getTileSize();
	float x = pos.x / tiledSize.width;
	float y = pos.y / tiledSize.height;
	/* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
	y = mapTiledNum.height - y;
	return Vec2(x, y);
}