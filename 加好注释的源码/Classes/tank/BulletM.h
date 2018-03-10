#pragma once
#include "cocos2d.h"
#include "Bullet.h"
/*该类为子弹管理类，主要的函数是提供一个创建子弹的接口，并统计子弹的数目*/
class Bullet;

USING_NS_CC;

/* 子弹管理类 */
class BulletM : public Layer
{
public:
	BulletM();
	~BulletM();
	CREATE_FUNC(BulletM);
	bool init();
	/* 获取该坦克发射的子弹数目 */
	int getBulletNum(void* owner);
	/**
	* 创建子弹
	* owner 子弹所属的坦克
	* speed 子弹速度
	* power 子弹力量 0不可打破铁，可打破半块砖；1可打破铁，可打破整块砖
	* pos 子弹位置
	* direction 子弹方向
	* distance 子弹距离
	*/
	void createBullet(void* owner, float speed, int power, Vec2 pos, Direction direction,int distance);
	/* 暂停游戏 */
	void pauseGame();
	/* 恢复游戏 */
	void resumeGame();
};
