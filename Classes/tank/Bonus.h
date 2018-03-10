#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum BonusType		// 奖励道具类型 
{
	hpUp = 1,		// hp+5  
	powerUp,		// power+1
	miss,			// miss
	statusUp		
};

/* 奖励道具 */
class Bonus : public Sprite
{
public:
	Bonus();
	~Bonus();
	static Bonus* create(BonusType type, Vec2 pos);
	bool init(BonusType type,Vec2 pos);
	bool isCollidePlayer();

private:
	void update(float dt);
	/* 是否与玩家坦克接触 */

	BonusType _type;	// 奖励道具类型 
};