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
	int type;//900以上为物品
	bool fly;//是否受重力影响
	Size itemSize;
	int gold;//金币掉落，-1为随机(0-10)，怪物不掉落金币
	int item;//物品掉落，-1为随机(红蓝药水)，怪物不掉落物品；0为不掉落，1、2为红蓝药水，不允许其他掉落
	string model;//使用的模组/动画
	string idleArmature;//运动及静止的动画名称
	string attakArmature;//攻击的动画名称
	string bulletArmature;//子弹的名称(没有则为空)
	string bulletEXArmature;//子弹击中目标(或墙壁地面等)时的动画(如果不会弹跳)
	string die;//死亡动画名称
	int step;//每单位时间移动的距离(单位时间未定)
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
	/*校验数据是否正常*/
	bool checkValid()
	{
		/*此检查在读取配置文件时检查，而下面这条的属性在读取map时才会读取，所以不检查*/
		if (gold < -1)return false;
		if (item < -1 || item>2)return false;
		if (model == "")return false;
		if (die == "")return false;
		if (type >= 900)return true;//物品不检查下列怪物特有属性
		if (health <= 0)return false;
		if (attack <= 0)return false;
		if (type < 0)return false;
		if (idleArmature == "")return false;
		if (attakArmature == "")return false;
		return true;
	}
};