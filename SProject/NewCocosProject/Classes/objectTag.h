#pragma  once

/*用于识别Node的Tag*/
#define  Tag_Border 0							/*墙(其他建筑部分)*/
#define  Tag_Player 1							/*玩家*/
#define  Tag_Monster 2						/*敌人*/
#define  Tag_PlayerSword 3				/*玩家攻击范围上方*/
#define  Tag_MonsterFire 4				/*敌人的子弹*/
#define  Tag_PlayerSwordPart2 5		/*玩家的剑前方*/
#define  Tag_Items 6							/*地图装饰(可攻击)*/

/*
逻辑要求:
当前对象：玩家、剑、敌人、子弹、墙(其他建筑部分)、敌人的剑(敌人其他近身武器)、地图装饰(可攻击)
玩家：
	碰撞：子弹、敌人、墙、敌人的剑
	不碰撞：剑、地图装饰
剑：
	碰撞：敌人、地图装饰
	不碰撞：玩家、墙、子弹、敌人的剑
敌人：
	碰撞：玩家、剑、墙
	不碰撞：子弹、敌人的剑、地图装饰
子弹：
	碰撞：玩家、墙
	不碰撞：敌人、剑、敌人的剑、地图装饰
墙：
	碰撞：子弹、敌人、玩家、地图装饰
	不碰撞：剑、敌人的剑
敌人的剑：
	碰撞：玩家
	不碰撞：子弹、敌人、剑、墙、地图装饰
地图装饰：(不需要和墙碰撞，设置为静态实体(有吊灯))
	碰撞：剑
	不碰撞：玩家、敌人、子弹、墙、敌人的剑
*/
#define  Mask_Player		0x10101		/*玩家*/
#define  Mask_Sword		0x01010		/*剑*/
#define  Mask_Enemy		0x00011		/*敌人*/
#define  Mask_Bullet		0x10000		/*子弹*/
#define  Mask_Ground	0x10001		/*墙*/
#define  Mask_ESword	0x00100		/*敌人的剑*/
#define  Mask_Items		0x01000		/*地图装饰*/