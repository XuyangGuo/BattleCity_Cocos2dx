/***********************************************

该类用来创建爆炸动画

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
enum BombType			// 爆炸类型 
{

	kTankBomb,			// 坦克爆炸 
	//kStrongholdBomb,	// 大本营爆炸 
	kBulletBomb			// 子弹爆炸 
};

/* 爆炸类 */
class Bomb : public Sprite
{
public:
	Bomb();
	~Bomb();
	/**
	* 创建爆炸
	* type 爆炸类型
	*/
	static Bomb* create(BombType type);
	virtual bool init(BombType type);
private:
	BombType _type;
};