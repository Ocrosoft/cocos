#include "BackgroundLayer.h"
#include "objectTag.h"
BackgroundLayer::BackgroundLayer() {}
BackgroundLayer::~BackgroundLayer() {}
bool BackgroundLayer::init()
{
	if (!Layer::init())return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��������ӱ���
	m_bg1 = Sprite::create("background.jpg");
	m_bg1->setPosition(Point(visibleSize.width*0.5f, visibleSize.height*0.5f));
	this->addChild(m_bg1);
	m_bg2 = Sprite::create("background.jpg");
	m_bg2->setPosition(Point(visibleSize.width*0.5f, -visibleSize.height*0.5f));
	this->addChild(m_bg2);
	//�����
	auto border = Sprite::create("border.png");
	Size borderSize = border->getContentSize();
	auto border1 = createBorder(Point(borderSize.width*0.5f, borderSize.height*0.5f));
	this->addChild(border1);
	//�Ҳ���
	auto border2 = createBorder(Point(visibleSize.width - borderSize.width * 0.5f, borderSize.height * 0.5f));
	border2->setFlippedX(true);//ˮƽ��ת
	this->addChild(border2);
	//�·����
	auto border3 = createBorder(Point(visibleSize.width * 0.5f, visibleSize.height * 0.15f));
	borderSize = border3->getContentSize();
	border3->setRotation(-90.0f);//˳ʱ����ת
	this->addChild(border3);
	return true;
}
Sprite* BackgroundLayer::createBorder(Point pos)
{
	auto border = Sprite::create("border.png");
	Size borderSize = border->getContentSize();
	auto body = PhysicsBody::createBox(borderSize);
	body->setDynamic(false);//����Ϊ��̬����(ǽ)
	body->setCategoryBitmask(1);//������������ײ���
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	border->setPhysicsBody(body);//����Ϊ����
	border->setPosition(pos);//����λ��
	//����Tag
	border->setTag(ObjectTag_Border);
	return border;
}
void BackgroundLayer::logic(float dt)
{
	int posY1 = m_bg1->getPositionY();//��ȡ����1��Y����
	int posY2 = m_bg2->getPositionY();//��ȡ����2��Y����
	int iSpeed = 3;//�����ٶ�
	posY1 += iSpeed;
	posY2 += iSpeed;
	//��ȡ��Ļ�߶�
	int iVisibleHeight = Director::getInstance()->getVisibleSize().height;
	if (posY1 > iVisibleHeight*1.5f)//������1��ȫ�뿪��������ʱ
	{//(Ĭ��ê�����м䣬��ȫ�뿪����ê�����1.5����height)
		posY2 = iVisibleHeight*0.5f;//ʹ����2��ȫ��ʾ
		posY1 = -iVisibleHeight*0.5f;//�ƶ�����1���·�
	}
	if (posY2 > iVisibleHeight * 1.5f)
	{
		posY1 = iVisibleHeight * 0.5f;
		posY2 = -iVisibleHeight * 0.5f;
	}
	m_bg1->setPositionY(posY1);
	m_bg2->setPositionY(posY2);
}