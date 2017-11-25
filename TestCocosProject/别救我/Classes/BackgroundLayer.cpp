#include "BackgroundLayer.h"
#include "objectTag.h"
BackgroundLayer::BackgroundLayer() {}
BackgroundLayer::~BackgroundLayer() {}
bool BackgroundLayer::init()
{
	if (!Layer::init())return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建并添加背景
	m_bg1 = Sprite::create("background.jpg");
	m_bg1->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.5f));
	this->addChild(m_bg1);
	m_bg2 = Sprite::create("background.jpg");
	m_bg2->setPosition(Point(visibleSize.width*0.5f, -visibleSize.height*0.5f));
	this->addChild(m_bg2);
	//左侧锯齿
	auto border = Sprite::create("border.png");
	Size borderSize = border->getContentSize();
	auto border1 = createBorder(Point(borderSize.width*0.5f, borderSize.height*0.5f));
	this->addChild(border1);
	//右侧锯齿
	auto border2 = createBorder(Point(visibleSize.width - borderSize.width * 0.5f, borderSize.height * 0.5f));
	border2->setFlippedX(true);//水平翻转
	this->addChild(border2);
	//下方锯齿
	auto border3 = createBorder(Point(visibleSize.width * 0.5f, visibleSize.height * 0.15f));
	borderSize = border3->getContentSize();
	border3->setRotation(-90.0f);//顺时针旋转
	this->addChild(border3);
	return true;
}
Sprite* BackgroundLayer::createBorder(Point pos)
{
	auto border = Sprite::create("border.png");
	Size borderSize = border->getContentSize();
	auto body = PhysicsBody::createBox(borderSize);
	body->setDynamic(false);//设置为静态物体(墙)
	body->setCategoryBitmask(1);//以下三个是碰撞检测
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	border->setPhysicsBody(body);//设置为刚体
	border->setPosition(pos);//设置位置
	//设置Tag
	border->setTag(ObjectTag_Border);
	return border;
}
void BackgroundLayer::logic(float dt)
{
	int posY1 = m_bg1->getPositionY();//获取背景1的Y坐标
	int posY2 = m_bg2->getPositionY();//获取背景2的Y坐标
	int iSpeed = 3;//滚动速度
	posY1 += iSpeed;
	posY2 += iSpeed;
	//获取屏幕高度
	int iVisibleHeight = Director::getInstance()->getVisibleSize().height;
	if (posY1 > iVisibleHeight*1.5f)//当背景1完全离开可视区域时
	{//(默认锚点是中间，完全离开就是锚点高于1.5倍的height)
		posY2 = iVisibleHeight*0.5f;//使背景2完全显示
		posY1 = -iVisibleHeight*0.5f;//移动背景1到下方
	}
	if (posY2 > iVisibleHeight * 1.5f)
	{
		posY1 = iVisibleHeight * 0.5f;
		posY2 = -iVisibleHeight * 0.5f;
	}
	m_bg1->setPositionY(posY1);
	m_bg2->setPositionY(posY2);
}