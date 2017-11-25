#pragma  once
#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class MonsterConfig
{
public:
	int health;
	int attack;
	int type;//900����Ϊ��Ʒ
	bool fly;//�Ƿ�������Ӱ��
	Size itemSize;
	int gold;//��ҵ��䣬-1Ϊ���(0-10)�����ﲻ������
	int item;//��Ʒ���䣬-1Ϊ���(����ҩˮ)�����ﲻ������Ʒ��0Ϊ�����䣬1��2Ϊ����ҩˮ����������������
	string model;//ʹ�õ�ģ��/����
	string idleArmature;//�˶�����ֹ�Ķ�������
	string attakArmature;//�����Ķ�������
	string bulletArmature;//�ӵ�������(û����Ϊ��)
	string bulletEXArmature;//�ӵ�����Ŀ��(��ǽ�ڵ����)ʱ�Ķ���(������ᵯ��)
	string die;//������������
	int step;//ÿ��λʱ���ƶ��ľ���(��λʱ��δ��)
	MonsterConfig()
	{
		health = 0;
		attack = 0;
		type = 0;
		model = "";
		fly = false;
		idleArmature = "";
		attakArmature = "";
		bulletEXArmature = "";
		bulletEXArmature = "";
		die = "";
		gold = 0;
		item = 0;
		itemSize = Size(0, 0);
	}
	/*У�������Ƿ�����*/
	bool checkValid()
	{
		/*�˼���ڶ�ȡ�����ļ�ʱ��飬�����������������ڶ�ȡmapʱ�Ż��ȡ�����Բ����*/
		if (gold < -1)return false;
		if (item < -1 || item>2)return false;
		if (model == "")return false;
		if (die == "")return false;
		if (type >= 900)return true;//��Ʒ��������й�����������
		if (health <= 0)return false;
		if (attack <= 0)return false;
		if (type < 0)return false;
		if (idleArmature == "")return false;
		if (attakArmature == "")return false;
		return true;
	}
};