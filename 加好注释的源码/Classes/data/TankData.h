/***********************************************

这里管理了游戏运行中坦克的基本数据，包括坦克的速、HP、攻击力等等，
此外，还通过SP矩阵计算当前坦克的属性

***********************************************/

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
	int getHP();//得到HP
	float getSPE();							//绝对坐标/秒
	int	getATK();							//攻击力
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
