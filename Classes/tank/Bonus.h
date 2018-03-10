#pragma once
#include "cocos2d.h"
/*该类为子弹类，主要的函数有创建子弹的函数，还有子弹移动过程中的碰撞检测，
有与地图边界、地图障碍物、子弹、坦克这四种判断检测*/
USING_NS_CC;
// 奖励道具类型
enum BonusType		 
{
	hpUp = 1,		// hp+5，即生命值+5 
	powerUp,		// power+1，子弹力量+5
	miss,			// miss
	statusUp		//红色buff,可以加攻击力和速度
};

/* 奖励道具类 */
class Bonus : public Sprite
{
public:
	Bonus();
	~Bonus();
	static Bonus* create(BonusType type, Vec2 pos);//创建道具（类型，坐标）
	bool init(BonusType type,Vec2 pos);
	bool isCollidePlayer();//对与道具碰撞的坦克进行碰撞检测，判断是否是玩家坦克

private:
	void update(float dt);
	/* 是否与玩家坦克接触 */

	BonusType _type;	// 奖励道具类型 
};