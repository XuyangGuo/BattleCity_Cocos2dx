#pragma once
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;

class DataM;
class TankData :public Ref
{
public:
	TankData();
	static TankData *getInstance();
	int getHP();
	float getSPE();							//绝对坐标/秒
	int	getATK();
	int getBulletNumMAX();
	float getBulletSPE();					//绝对坐标/秒
	float getBulletDistance();				//绝对坐标
	bool isAOE();
	float getAvoidProbability();			//0到1,速度型回避
	int getDamageDiscount();				//int 减少绝对伤害
	float getReadyInterval();				//冷却时间
	bool isFireUp();						//是否灼烧
	bool isRebirth();						//是否死后回血 
	float getShieldTime();					//无敌时间 /秒
	int getJumpAbility();					//闪烁距离，单位 格数
	int getAtkInterval();					//攻击间隔 单位 帧数	
private:
	DataM *dataM;
};
